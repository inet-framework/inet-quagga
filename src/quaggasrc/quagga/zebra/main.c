/* zebra daemon main routine.
 * Copyright (C) 1997, 98 Kunihiro Ishiguro
 *
 * This file is part of GNU Zebra.
 *
 * GNU Zebra is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2, or (at your option) any
 * later version.
 *
 * GNU Zebra is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Zebra; see the file COPYING.  If not, write to the Free
 * Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.  
 */

#include <zebra.h>

#include <lib/version.h>
#include "getopt.h"
#include "command.h"
#include "thread.h"
#include "filter.h"
#include "memory.h"
#include "prefix.h"
#include "log.h"
#include "privs.h"
#include "sigevent.h"

#include "zebra/rib.h"
#include "zebra/zserv.h"
#include "zebra/debug.h"
#include "zebra/router-id.h"
#include "zebra/irdp.h"

/* Zebra instance */
struct zebra_t zebrad_zebra =
{
  NULL,
  NULL,
  0
};

/* process id. */
pid_t old_pid_zebra;
pid_t pid_zebra;

/* Pacify zclient.o in libzebra, which expects this variable. */
struct thread_master *master_zebra;

/* Route retain mode flag. */
int retain_mode_zebra ;

/* Don't delete kernel route. */
int keep_kernel_mode_zebra ;

#ifdef HAVE_NETLINK
/* Receive buffer size for netlink socket */
u_int32_t nl_rcvbufsize_zebra ;
#endif /* HAVE_NETLINK */

/* Command line options. */
static struct option longopts[] = 
{
  { "batch",       no_argument,       NULL, 'b'},
  { "daemon",      no_argument,       NULL, 'd'},
  { "keep_kernel", no_argument,       NULL, 'k'},
  { "log_mode",    no_argument,       NULL, 'l'},
  { "config_file", required_argument, NULL, 'f'},
  { "pid_file",    required_argument, NULL, 'i'},
  { "help",        no_argument,       NULL, 'h'},
  { "vty_addr",    required_argument, NULL, 'A'},
  { "vty_port",    required_argument, NULL, 'P'},
  { "retain",      no_argument,       NULL, 'r'},
#ifdef HAVE_NETLINK
  { "nl-bufsize",  required_argument, NULL, 's'},
#endif /* HAVE_NETLINK */
  { "user",        required_argument, NULL, 'u'},
  { "group",       required_argument, NULL, 'g'},
  { "version",     no_argument,       NULL, 'v'},
  { 0 }
};

static zebra_capabilities_t _caps_p [] = 
{
  ZCAP_ADMIN,
  ZCAP_SYS_ADMIN,
  ZCAP_RAW,
};

/* zebra privileges to run with */
struct zebra_privs_t zserv_privs =
{
  _caps_p,
  NULL,
  sizeof(_caps_p)/sizeof(_caps_p[0]),
  0,
#if defined(QUAGGA_USER) && defined(QUAGGA_GROUP)
  QUAGGA_USER,
  QUAGGA_GROUP,
#else
  NULL,
  NULL,
#endif
#ifdef VTY_GROUP
  VTY_GROUP,
#else
  NULL,
#endif
  NULL,
  NULL
};

/* Default configuration file path. */
static char config_default[] = SYSCONFDIR DEFAULT_CONFIG_FILE;

/* Process ID saved for use by init system */
const char *pid_file_zebra ;

/* Help information display. */
static void
usage (char *progname, int status)
{
  if (status != 0)
    fprintf (stderr, "Try `%s --help' for more information.\n", progname);
  else
    {    
      printf ("Usage : %s [OPTION...]\n\n"\
	      "Daemon which manages kernel routing table management and "\
	      "redistribution between different routing protocols.\n\n"\
	      "-b, --batch        Runs in batch mode\n"\
	      "-d, --daemon       Runs in daemon mode\n"\
	      "-f, --config_file  Set configuration file name\n"\
	      "-i, --pid_file     Set process identifier file name\n"\
	      "-k, --keep_kernel  Don't delete old routes which installed by "\
				  "zebra.\n"\
	      "-l, --log_mode     Set verbose log mode flag\n"\
	      "-A, --vty_addr     Set vty's bind address\n"\
	      "-P, --vty_port     Set vty's port number\n"\
	      "-r, --retain       When program terminates, retain added route "\
				  "by zebra.\n"\
	      "-u, --user         User to run as\n"\
	      "-g, --group	  Group to run as\n", progname);
#ifdef HAVE_NETLINK
      printf ("-s, --nl-bufsize   Set netlink receive buffer size\n");
#endif /* HAVE_NETLINK */
      printf ("-v, --version      Print program version\n"\
	      "-h, --help         Display this help and exit\n"\
	      "\n"\
	      "Report bugs to %s\n", ZEBRA_BUG_ADDRESS);
    }

  exit (status);
}

/* SIGHUP handler. */
static void 
sighup (void)
{
  zlog_info ("SIGHUP received");

  /* Reload of config file. */
  ;
}

/* SIGINT handler. */
static void
sigint (void)
{
  /* Decrared in rib.c */
  void rib_close ();

  zlog_notice ("Terminating on signal");

  if (!retain_mode)
    rib_close ();
#ifdef HAVE_IRDP
  irdp_finish();
#endif

  exit (0);
}

/* SIGUSR1 handler. */
static void
sigusr1 (void)
{
  zlog_rotate (NULL);
}

struct quagga_signal_t zebra_signals[] =
{
  { 
    SIGHUP, 
    &sighup,
    0
  },
  {
    SIGUSR1,
    &sigusr1,
    0
  },
  {
    SIGINT,
    &sigint,
    0
  },
  {
    SIGTERM,
    &sigint,
    0
  },
};

/* Main startup routine. */
int
zebra_main_entry (int argc, char **argv)
{
  char *p;
#undef	vty_addr
  char *vty_addr = NULL;
#undef	vty_port
  int vty_port = ZEBRA_VTY_PORT;
  int batch_mode = 0;
  int daemon_mode = 0;
#undef	config_file
  char *config_file = NULL;
  char *progname;
  struct thread thread;
  void rib_weed_tables ();
  void zebra_vty_init ();

  /* Set umask before anything for security */
  umask (0027);

  /* preserve my name */
  progname = ((p = strrchr (argv[0], '/')) ? ++p : argv[0]);

  zlog_default = openzlog (progname, ZLOG_ZEBRA,
			   LOG_CONS|LOG_NDELAY|LOG_PID, LOG_DAEMON);

  while (1) 
    {
      int opt;
  
#ifdef HAVE_NETLINK  
      opt = getopt_long (argc, argv, "bdklf:i:hA:P:ru:g:vs:", longopts, 0);
#else
      opt = getopt_long (argc, argv, "bdklf:i:hA:P:ru:g:v", longopts, 0);
#endif /* HAVE_NETLINK */

      if (opt == EOF)
	break;

      switch (opt) 
	{
	case 0:
	  break;
	case 'b':
	  batch_mode = 1;
	case 'd':
	  daemon_mode = 1;
	  break;
	case 'k':
	  keep_kernel_mode = 1;
	  break;
	case 'l':
	  /* log_mode = 1; */
	  break;
	case 'f':
	  config_file = optarg;
	  break;
	case 'A':
	  vty_addr = optarg;
	  break;
        case 'i':
          pid_file = optarg;
          break;
	case 'P':
	  /* Deal with atoi() returning 0 on failure, and zebra not
	     listening on zebra port... */
	  if (strcmp(optarg, "0") == 0) 
	    {
	      vty_port = 0;
	      break;
	    } 
	  vty_port = atoi (optarg);
	  vty_port = (vty_port ? vty_port : ZEBRA_VTY_PORT);
	  break;
	case 'r':
	  retain_mode = 1;
	  break;
#ifdef HAVE_NETLINK
	case 's':
	  nl_rcvbufsize = atoi (optarg);
	  break;
#endif /* HAVE_NETLINK */
	case 'u':
	  zserv_privs.user = optarg;
	  break;
	case 'g':
	  zserv_privs.group = optarg;
	  break;
	case 'v':
	  print_version (progname);
	  exit (0);
	  break;
	case 'h':
	  usage (progname, 0);
	  break;
	default:
	  usage (progname, 1);
	  break;
	}
    }

  /* Make master thread emulator. */
  zebrad.master__item = thread_master_create ();

  /* privs initialise */
  zprivs_init (&zserv_privs);

  /* Vty related initialize. */
  signal_init (zebrad.master__item, Q_SIGC(zebra_signals), zebra_signals);
  cmd_init (1);
  vty_init (zebrad.master__item);
  memory_init ();

  /* Zebra related initialize. */
  zebra_init ();
  rib_init ();
  zebra_if_init ();
  zebra_debug_init ();
  router_id_init();
  zebra_vty_init ();
  access_list_init ();
  rtadv_init ();
#ifdef HAVE_IRDP
  irdp_init();
#endif

  /* For debug purpose. */
  /* SET_FLAG (zebra_debug_event, ZEBRA_DEBUG_EVENT); */

  /* Make kernel routing socket. */
  kernel_init ();
  interface_list ();
  route_read ();

  /* Sort VTY commands. */
  sort_node ();

#ifdef HAVE_SNMP
  zebra_snmp_init ();
#endif /* HAVE_SNMP */

  /* Clean up self inserted route. */
  if (! keep_kernel_mode)
    rib_sweep_route ();

  /* Configuration file read*/
  vty_read_config (config_file, config_default);

  /* Clean up rib. */
  rib_weed_tables ();

  /* Exit when zebra is working in batch mode. */
  if (batch_mode)
    exit (0);

  /* Needed for BSD routing socket. */
  old_pid = getpid ();

  /* Daemonize. */
  if (daemon_mode)
    daemon (0, 0);

  /* Output pid of zebra. */
  pid_output (pid_file);

  /* Needed for BSD routing socket. */
  pid = getpid ();

  /* Make vty server socket. */
  vty_serv_sock (vty_addr, vty_port, ZEBRA_VTYSH_PATH);

  /* Print banner. */
  zlog_notice ("Zebra %s starting: vty@%d", QUAGGA_VERSION, vty_port);

  while (thread_fetch (zebrad.master__item, &thread))
    thread_call (&thread);

  /* Not reached... */
  exit (0);
}
#define	config_file	config_file__VAR
#define	vty_addr	vty_addr__VAR
#define	vty_port	vty_port__VAR
