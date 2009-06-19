/*
 * OSPFd main routine.
 *   Copyright (C) 1998, 99 Kunihiro Ishiguro, Toshiaki Takada
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
#include "thread.h"
#include "prefix.h"
#include "linklist.h"
#include "if.h"
#include "vector.h"
#include "vty.h"
#include "command.h"
#include "filter.h"
#include "plist.h"
#include "stream.h"
#include "log.h"
#include "memory.h"
#include "privs.h"
#include "sigevent.h"

#include "ospfd/ospfd.h"
#include "ospfd/ospf_interface.h"
#include "ospfd/ospf_asbr.h"
#include "ospfd/ospf_lsa.h"
#include "ospfd/ospf_lsdb.h"
#include "ospfd/ospf_neighbor.h"
#include "ospfd/ospf_dump.h"
#include "ospfd/ospf_zebra.h"
#include "ospfd/ospf_vty.h"

/* ospfd privileges */
static zebra_capabilities_t _caps_p [] = 
{
  ZCAP_NET_RAW,
  ZCAP_BIND,
  ZCAP_NET_ADMIN,
};

struct zebra_privs_t ospfd_privs =
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
#if defined(VTY_GROUP)
  VTY_GROUP,
#else
  NULL,
#endif
  NULL,
  NULL
};

/* Configuration filename and directory. */
static char config_default[] = SYSCONFDIR OSPF_DEFAULT_CONFIG;

/* OSPFd options. */
static struct option longopts[] = 
{
  { "daemon",      no_argument,       NULL, 'd'},
  { "config_file", required_argument, NULL, 'f'},
  { "pid_file",    required_argument, NULL, 'i'},
  { "log_mode",    no_argument,       NULL, 'l'},
  { "dryrun",      no_argument,       NULL, 'C'},
  { "help",        no_argument,       NULL, 'h'},
  { "vty_addr",    required_argument, NULL, 'A'},
  { "vty_port",    required_argument, NULL, 'P'},
  { "user",        required_argument, NULL, 'u'},
  { "group",       required_argument, NULL, 'g'},
  { "apiserver",   no_argument,       NULL, 'a'},
  { "version",     no_argument,       NULL, 'v'},
  { 0 }
};

/* OSPFd program name */

/* Master of threads. */
struct thread_master *master_ospfd;

/* Process ID saved for use by init system */
const char *pid_file_ospfd ;

#ifdef SUPPORT_OSPF_API
extern int ospf_apiserver_enable;
#endif /* SUPPORT_OSPF_API */

/* Help information display. */
static void __attribute__ ((noreturn))
usage (char *progname, int status)
{
  if (status != 0)
    fprintf (stderr, "Try `%s --help' for more information.\n", progname);
  else
    {    
      printf ("Usage : %s [OPTION...]\n\
Daemon which manages OSPF.\n\n\
-d, --daemon       Runs in daemon mode\n\
-f, --config_file  Set configuration file name\n\
-i, --pid_file     Set process identifier file name\n\
-A, --vty_addr     Set vty's bind address\n\
-P, --vty_port     Set vty's port number\n\
-u, --user         User to run as\n\
-g, --group        Group to run as\n\
-a. --apiserver    Enable OSPF apiserver\n\
-v, --version      Print program version\n\
-C, --dryrun       Check configuration for validity and exit\n\
-h, --help         Display this help and exit\n\
\n\
Report bugs to %s\n", progname, ZEBRA_BUG_ADDRESS);
    }
  exit (status);
}

/* SIGHUP handler. */
static void 
sighup (void)
{
  zlog (NULL, LOG_INFO, "SIGHUP received");
}

/* SIGINT / SIGTERM handler. */
static void
sigint (void)
{
  zlog_notice ("Terminating on signal");
  ospf_terminate ();
}

/* SIGUSR1 handler. */
static void
sigusr1 (void)
{
  zlog_rotate (NULL);
}

struct quagga_signal_t ospf_signals[] =
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

/* OSPFd main routine. */
int
ospfd_main_entry (int argc, char **argv)
{
  char *p;
#undef	vty_addr
  char *vty_addr = NULL;
#undef	vty_port
  int vty_port = OSPF_VTY_PORT;
  int daemon_mode = 0;
#undef	config_file
  char *config_file = NULL;
  char *progname;
  struct thread thread;
  int dryrun = 0;

  /* Set umask before anything for security */
  umask (0027);

  /* get program name */
  progname = ((p = strrchr (argv[0], '/')) ? ++p : argv[0]);

  /* Invoked by a priviledged user? -- endo. */
  if (geteuid () != 0)
    {
      errno = EPERM;
      perror (progname);
      exit (1);
    }

  zlog_default = openzlog (progname, ZLOG_OSPF,
			   LOG_CONS|LOG_NDELAY|LOG_PID, LOG_DAEMON);

  /* OSPF master init. */
  ospf_master_init ();

#ifdef SUPPORT_OSPF_API
  /* OSPF apiserver is disabled by default. */
  ospf_apiserver_enable = 0;
#endif /* SUPPORT_OSPF_API */

  while (1) 
    {
      int opt;

      opt = getopt_long (argc, argv, "dlf:i:hA:P:u:g:avC", longopts, 0);
    
      if (opt == EOF)
	break;

      switch (opt) 
	{
	case 0:
	  break;
	case 'd':
	  daemon_mode = 1;
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
          /* Deal with atoi() returning 0 on failure, and ospfd not
             listening on ospfd port... */
          if (strcmp(optarg, "0") == 0) 
            {
              vty_port = 0;
              break;
            } 
          vty_port = atoi (optarg);
          if (vty_port <= 0 || vty_port > 0xffff)
            vty_port = OSPF_VTY_PORT;
  	  break;
	case 'u':
	  ospfd_privs.user = optarg;
	  break;
	case 'g':
	  ospfd_privs.group = optarg;
	  break;
#ifdef SUPPORT_OSPF_API
	case 'a':
	  ospf_apiserver_enable = 1;
	  break;
#endif /* SUPPORT_OSPF_API */
	case 'v':
	  print_version (progname);
	  exit (0);
	  break;
	case 'C':
	  dryrun = 1;
	  break;
	case 'h':
	  usage (progname, 0);
	  break;
	default:
	  usage (progname, 1);
	  break;
	}
    }

  /* Initializations. */
  master = om->master__item;

  /* Library inits. */
  zprivs_init (&ospfd_privs);
  signal_init (master, Q_SIGC(ospf_signals), ospf_signals);
  cmd_init (1);
  debug_init ();
  vty_init (master);
  memory_init ();

  access_list_init ();
  prefix_list_init ();

  /* OSPFd inits. */
  ospf_if_init ();
  ospf_zebra_init ();

  /* OSPF vty inits. */
  ospf_vty_init ();
  ospf_vty_show_init ();

  ospf_route_map_init ();
#ifdef HAVE_SNMP
  ospf_snmp_init ();
#endif /* HAVE_SNMP */
#ifdef HAVE_OPAQUE_LSA
  ospf_opaque_init ();
#endif /* HAVE_OPAQUE_LSA */
  
  sort_node ();

  /* Get configuration file. */
  vty_read_config (config_file, config_default);

  /* Start execution only if not in dry-run mode */
  if (dryrun)
    return(0);
  
  /* Change to the daemon program. */
  if (daemon_mode)
    daemon (0, 0);

  /* Process id file create. */
  pid_output (pid_file);

  /* Create VTY socket */
  vty_serv_sock (vty_addr, vty_port, OSPF_VTYSH_PATH);

  /* Print banner. */
  zlog_notice ("OSPFd %s starting: vty@%d", QUAGGA_VERSION, vty_port);

  /* Fetch next active thread. */
  while (thread_fetch (master, &thread))
    thread_call (&thread);

  /* Not reached. */
  return (0);
}
#define	config_file	config_file__VAR
#define	vty_addr	vty_addr__VAR
#define	vty_port	vty_port__VAR
