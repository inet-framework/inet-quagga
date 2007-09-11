/*
 * Interface function.
 * Copyright (C) 1997, 1999 Kunihiro Ishiguro
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

#include "if.h"
#include "vty.h"
#include "sockunion.h"
#include "prefix.h"
#include "command.h"
#include "memory.h"
#include "ioctl.h"
#include "connected.h"
#include "log.h"
#include "zclient.h"

#include "zebra/interface.h"
#include "zebra/rtadv.h"
#include "zebra/rib.h"
#include "zebra/zserv.h"
#include "zebra/redistribute.h"
#include "zebra/debug.h"
#include "zebra/irdp.h"

/* Allocate a new internal interface index 
 * This works done from the top so that %d macros
 * print a - sign! 
 */
static unsigned int
if_new_intern_ifindex (void)
{
  /* Start here so that first one assigned is 0xFFFFFFFF */
  static unsigned int ifindex = IFINDEX_INTERNBASE + 1;

  for (;;) 
    {
      ifindex--;
      if ( ifindex <= IFINDEX_INTERNBASE )
       ifindex = 0xFFFFFFFF;

      if (if_lookup_by_index(ifindex) == NULL)
       return ifindex;
    }
}

/* Called when new interface is added. */
int
if_zebra_new_hook (struct interface_FOO *ifp)
{
  struct zebra_if *zebra_if;

  zebra_if = XMALLOC (MTYPE_TMP, sizeof (struct zebra_if));
  memset (zebra_if, 0, sizeof (struct zebra_if));

  zebra_if->multicast = IF_ZEBRA_MULTICAST_UNSPEC;
  zebra_if->shutdown = IF_ZEBRA_SHUTDOWN_UNSPEC;

#ifdef RTADV
  {
    /* Set default router advertise values. */
    struct rtadvconf *rtadv;

    rtadv = &zebra_if->rtadv;

    rtadv->AdvSendAdvertisements = 0;
    rtadv->MaxRtrAdvInterval = RTADV_MAX_RTR_ADV_INTERVAL;
    rtadv->MinRtrAdvInterval = RTADV_MIN_RTR_ADV_INTERVAL;
    rtadv->AdvIntervalTimer = 0;
    rtadv->AdvManagedFlag = 0;
    rtadv->AdvOtherConfigFlag = 0;
    rtadv->AdvLinkMTU = 0;
    rtadv->AdvReachableTime = 0;
    rtadv->AdvRetransTimer = 0;
    rtadv->AdvCurHopLimit = 0;
    rtadv->AdvDefaultLifetime = RTADV_ADV_DEFAULT_LIFETIME;

    rtadv->AdvPrefixList = list_new ();
  }    
#endif /* RTADV */

  ifp->info = zebra_if;
  return 0;
}

/* Called when interface is deleted. */
int
if_zebra_delete_hook (struct interface_FOO *ifp)
{
  if (ifp->info)
    XFREE (MTYPE_TMP, ifp->info);
  return 0;
}

/* Wake up configured address if it is not in current kernel
   address. */
void
if_addr_wakeup (struct interface_FOO *ifp)
{
  struct listnode *node;
  struct connected *ifc;
  struct prefix *p;
  int ret;

  for (node = listhead (ifp->connected); node; nextnode (node))
    {
      ifc = getdata (node);
      p = ifc->address;
	
      if (CHECK_FLAG (ifc->conf, ZEBRA_IFC_CONFIGURED)
	  && ! CHECK_FLAG (ifc->conf, ZEBRA_IFC_REAL))
	{
	  /* Address check. */
	  if (p->family == AF_INET)
	    {
	      if (! if_is_up (ifp))
		{
		  if_set_flags (ifp, IFF_UP | IFF_RUNNING);
		  if_refresh (ifp);
		}

	      ret = if_set_prefix (ifp, ifc);
	      if (ret < 0)
		{
		  zlog_warn ("Can't set interface's address: %s", 
			     safe_strerror(errno));
		  continue;
		}
	      SET_FLAG (ifc->conf, ZEBRA_IFC_REAL);

	      zebra_interface_address_add_update (ifp, ifc);

	      if (if_is_operative(ifp))
		connected_up_ipv4 (ifp, ifc);
	    }
#ifdef HAVE_IPV6
	  if (p->family == AF_INET6)
	    {
	      if (! if_is_up (ifp))
		{
		  if_set_flags (ifp, IFF_UP | IFF_RUNNING);
		  if_refresh (ifp);
		}

	      ret = if_prefix_add_ipv6 (ifp, ifc);
	      if (ret < 0)
		{
		  zlog_warn ("Can't set interface's address: %s", 
			     safe_strerror(errno));
		  continue;
		}
	      SET_FLAG (ifc->conf, ZEBRA_IFC_REAL);

	      zebra_interface_address_add_update (ifp, ifc);

	      if (if_is_operative(ifp))
		connected_up_ipv6 (ifp, ifc);
	    }
#endif /* HAVE_IPV6 */
	}
    }
}

/* Handle interface addition */
void
if_add_update (struct interface_FOO *ifp)
{
  struct zebra_if *if_data;

  if_data = ifp->info;
  if (if_data->multicast == IF_ZEBRA_MULTICAST_ON)
    if_set_flags (ifp, IFF_MULTICAST);
  else if (if_data->multicast == IF_ZEBRA_MULTICAST_OFF)
    if_unset_flags (ifp, IFF_MULTICAST);

  zebra_interface_add_update (ifp);

  if (! CHECK_FLAG (ifp->status, ZEBRA_INTERFACE_ACTIVE))
    {
      SET_FLAG (ifp->status, ZEBRA_INTERFACE_ACTIVE);

      if_addr_wakeup (ifp);

      if (IS_ZEBRA_DEBUG_KERNEL)
	zlog_debug ("interface %s index %d becomes active.", 
		    ifp->name, ifp->ifindex);
    }
  else
    {
      if (IS_ZEBRA_DEBUG_KERNEL)
	zlog_debug ("interface %s index %d is added.", ifp->name, ifp->ifindex);
    }
}


/* Handle an interface delete event
 * 
 * This function is only called  when support for
 * RTM_IFANNOUNCE or AF_NETLINK sockets (RTM_DELLINK message)
 * is available. It is not called on, eg, Solaris.
 */
#if (defined(RTM_IFANNOUNCE) || defined(HAVE_NETLINK))
void 
if_delete_update (struct interface_FOO *ifp)
{
  struct listnode *node;
  struct listnode *next;
  struct connected *ifc;
  struct prefix *p;

  if (if_is_up(ifp))
    {
      zlog_err ("interface %s index %d is still up while being deleted.",
	    ifp->name, ifp->ifindex);
      return;
    }

  /* Mark interface as inactive */
  UNSET_FLAG (ifp->status, ZEBRA_INTERFACE_ACTIVE);
  
  if (IS_ZEBRA_DEBUG_KERNEL)
    zlog_debug ("interface %s index %d is now inactive.",
	       ifp->name, ifp->ifindex);

  /* Delete connected routes from the kernel. */
  if (ifp->connected)
    {
      for (node = listhead (ifp->connected); node; node = next)
	{
	  next = node->next;
	  ifc = getdata (node);
	  p = ifc->address;

	  if (p->family == AF_INET)
	    connected_down_ipv4 (ifp, ifc);
#ifdef HAVE_IPV6
	  else if (p->family == AF_INET6)
	    connected_down_ipv6 (ifp, ifc);
#endif /* HAVE_IPV6 */

	  zebra_interface_address_delete_update (ifp, ifc);

	  UNSET_FLAG (ifc->conf, ZEBRA_IFC_REAL);
	  
	  if (! CHECK_FLAG (ifc->conf, ZEBRA_IFC_CONFIGURED))
	    {      
	      listnode_delete (ifp->connected, ifc);
	      connected_free (ifc);
	    }
	}
    }
  zebra_interface_delete_update (ifp);
}
#endif /* (defined(RTM_IFANNOUNCE) || defined(HAVE_NETLINK) */

/* Interface is up. */
void
if_up (struct interface_FOO *ifp)
{
  struct listnode *node;
  struct listnode *next;
  struct connected *ifc;
  struct prefix *p;

  /* Notify the protocol daemons. */
  zebra_interface_up_update (ifp);

  /* Install connected routes to the kernel. */
  if (ifp->connected)
    {
      for (node = listhead (ifp->connected); node; node = next)
	{
	  next = node->next;
	  ifc = getdata (node);
	  p = ifc->address;

	  if (p->family == AF_INET)
	    connected_up_ipv4 (ifp, ifc);
#ifdef HAVE_IPV6
	  else if (p->family == AF_INET6)
	    connected_up_ipv6 (ifp, ifc);
#endif /* HAVE_IPV6 */
	}
    }

  /* Examine all static routes. */
  rib_update ();
}

/* Interface goes down.  We have to manage different behavior of based
   OS. */
void
if_down (struct interface_FOO *ifp)
{
  struct listnode *node;
  struct listnode *next;
  struct connected *ifc;
  struct prefix *p;

  /* Notify to the protocol daemons. */
  zebra_interface_down_update (ifp);

  /* Delete connected routes from the kernel. */
  if (ifp->connected)
    {
      for (node = listhead (ifp->connected); node; node = next)
	{
	  next = node->next;
	  ifc = getdata (node);
	  p = ifc->address;

	  if (p->family == AF_INET)
	    connected_down_ipv4 (ifp, ifc);
#ifdef HAVE_IPV6
	  else if (p->family == AF_INET6)
	    connected_down_ipv6 (ifp, ifc);
#endif /* HAVE_IPV6 */
	}
    }

  /* Examine all static routes which direct to the interface. */
  rib_update ();
}

void
if_refresh (struct interface_FOO *ifp)
{
  if (if_is_operative (ifp))
    {
      if_get_flags (ifp);
      if (! if_is_operative (ifp))
	if_down (ifp);
    }
  else
    {
      if_get_flags (ifp);
      if (if_is_operative (ifp))
	if_up (ifp);
    }
}

/* Printout flag information into vty */
void
if_flag_dump_vty (struct vty *vty, unsigned long flag)
{
  int separator = 0;

#define IFF_OUT_VTY(X, Y) \
  if ((X) && (flag & (X))) \
    { \
      if (separator) \
	vty_out (vty, ","); \
      else \
	separator = 1; \
      vty_out (vty, Y); \
    }

  vty_out (vty, "<");
  IFF_OUT_VTY (IFF_UP, "UP");
  IFF_OUT_VTY (IFF_BROADCAST, "BROADCAST");
  IFF_OUT_VTY (IFF_DEBUG, "DEBUG");
  IFF_OUT_VTY (IFF_LOOPBACK, "LOOPBACK");
  IFF_OUT_VTY (IFF_POINTOPOINT, "POINTOPOINT");
  IFF_OUT_VTY (IFF_NOTRAILERS, "NOTRAILERS");
  IFF_OUT_VTY (IFF_RUNNING, "RUNNING");
  IFF_OUT_VTY (IFF_NOARP, "NOARP");
  IFF_OUT_VTY (IFF_PROMISC, "PROMISC");
  IFF_OUT_VTY (IFF_ALLMULTI, "ALLMULTI");
  IFF_OUT_VTY (IFF_OACTIVE, "OACTIVE");
  IFF_OUT_VTY (IFF_SIMPLEX, "SIMPLEX");
  IFF_OUT_VTY (IFF_LINK0, "LINK0");
  IFF_OUT_VTY (IFF_LINK1, "LINK1");
  IFF_OUT_VTY (IFF_LINK2, "LINK2");
  IFF_OUT_VTY (IFF_MULTICAST, "MULTICAST");
#ifdef SOLARIS_IPV6
  IFF_OUT_VTY (IFF_IPV4, "IFF_IPv4");
  IFF_OUT_VTY (IFF_IPV6, "IFF_IPv6");
#endif /* SOLARIS_IPV6 */
  vty_out (vty, ">");
}

/* Output prefix string to vty. */
int
prefix_vty_out (struct vty *vty, struct prefix *p)
{
  char str[INET6_ADDRSTRLEN];

  inet_ntop (p->family, &p->u.prefix, str, sizeof (str));
  vty_out (vty, "%s", str);
  return strlen (str);
}

/* Dump if address information to vty. */
void
connected_dump_vty (struct vty *vty, struct connected *connected)
{
  struct prefix *p;
  struct interface_FOO *ifp;

  /* Set interface pointer. */
  ifp = connected->ifp;

  /* Print interface address. */
  p = connected->address;
  vty_out (vty, "  %s ", prefix_family_str (p));
  prefix_vty_out (vty, p);
  vty_out (vty, "/%d", p->prefixlen);

  /* If there is destination address, print it. */
  p = connected->destination;
  if (p)
    {
      if (p->family == AF_INET)
	if (ifp->flags & IFF_BROADCAST)
	  {
	    vty_out (vty, " broadcast ");
	    prefix_vty_out (vty, p);
	  }

      if (ifp->flags & IFF_POINTOPOINT)
	{
	  vty_out (vty, " pointopoint ");
	  prefix_vty_out (vty, p);
	}
    }

  if (CHECK_FLAG (connected->flags, ZEBRA_IFA_SECONDARY))
    vty_out (vty, " secondary");

  if (connected->label)
    vty_out (vty, " %s", connected->label);

  vty_out (vty, "%s", VTY_NEWLINE);
}

#ifdef RTADV
/* Dump interface ND information to vty. */
void
nd_dump_vty (struct vty *vty, struct interface_FOO *ifp)
{
  struct zebra_if *zif;
  struct rtadvconf *rtadv;

  zif = (struct zebra_if *) ifp->info;
  rtadv = &zif->rtadv;

  if (rtadv->AdvSendAdvertisements)
    {
      vty_out (vty, "  ND advertised reachable time is %d milliseconds%s",
	       rtadv->AdvReachableTime, VTY_NEWLINE);
      vty_out (vty, "  ND advertised retransmit interval is %d milliseconds%s",
	       rtadv->AdvRetransTimer, VTY_NEWLINE);
      vty_out (vty, "  ND router advertisements are sent every %d seconds%s",
	       rtadv->MaxRtrAdvInterval, VTY_NEWLINE);
      vty_out (vty, "  ND router advertisements live for %d seconds%s",
	       rtadv->AdvDefaultLifetime, VTY_NEWLINE);
      if (rtadv->AdvManagedFlag)
	vty_out (vty, "  Hosts use DHCP to obtain routable addresses.%s",
		 VTY_NEWLINE);
      else
	vty_out (vty, "  Hosts use stateless autoconfig for addresses.%s",
		 VTY_NEWLINE);
    }
}
#endif /* RTADV */

/* Interface's information print out to vty interface. */
void
if_dump_vty (struct vty *vty, struct interface_FOO *ifp)
{
#ifdef HAVE_SOCKADDR_DL
  struct sockaddr_dl *sdl;
#endif /* HAVE_SOCKADDR_DL */
  struct connected *connected;
  struct listnode *node;

  vty_out (vty, "Interface %s is ", ifp->name);
  if (if_is_up(ifp)) {
    vty_out (vty, "up, line protocol ");
    
    if (CHECK_FLAG(ifp->status, ZEBRA_INTERFACE_LINKDETECTION)) {
      if (if_is_running(ifp))
       vty_out (vty, "is up%s", VTY_NEWLINE);
      else
	vty_out (vty, "is down%s", VTY_NEWLINE);
    } else {
      vty_out (vty, "detection is disabled%s", VTY_NEWLINE);
    }
  } else {
    vty_out (vty, "down%s", VTY_NEWLINE);
  }

  if (ifp->desc)
    vty_out (vty, "  Description: %s%s", ifp->desc,
	     VTY_NEWLINE);
  if (ifp->ifindex <= 0)
    {
      vty_out(vty, "  index %d pseudo interface%s", ifp->ifindex, VTY_NEWLINE);
      return;
    }
  else if (! CHECK_FLAG (ifp->status, ZEBRA_INTERFACE_ACTIVE))
    {
      vty_out(vty, "  index %d inactive interface%s", 
	      ifp->ifindex, 
	      VTY_NEWLINE);
      return;
    }

  vty_out (vty, "  index %d metric %d mtu %d ",
	   ifp->ifindex, ifp->metric, ifp->mtu);
  if_flag_dump_vty (vty, ifp->flags);
#ifdef HAVE_IPV6
  if (ifp->mtu6 != ifp->mtu)
    vty_out (vty, "mtu6 %d ", ifp->mtu6);
#endif 

  vty_out (vty, "%s", VTY_NEWLINE);

  /* Hardware address. */
#ifdef HAVE_SOCKADDR_DL
  sdl = &ifp->sdl;
  if (sdl != NULL && sdl->sdl_alen != 0)
    {
      int i;
      u_char *ptr;

      vty_out (vty, "  HWaddr: ");
      for (i = 0, ptr = (u_char *)LLADDR (sdl); i < sdl->sdl_alen; i++, ptr++)
        vty_out (vty, "%s%02x", i == 0 ? "" : ":", *ptr);
      vty_out (vty, "%s", VTY_NEWLINE);
    }
#else
  if (ifp->hw_addr_len != 0)
    {
      int i;

      vty_out (vty, "  HWaddr: ");
      for (i = 0; i < ifp->hw_addr_len; i++)
	vty_out (vty, "%s%02x", i == 0 ? "" : ":", ifp->hw_addr[i]);
      vty_out (vty, "%s", VTY_NEWLINE);
    }
#endif /* HAVE_SOCKADDR_DL */
  
  /* Bandwidth in kbps */
  if (ifp->bandwidth != 0)
    {
      vty_out(vty, "  bandwidth %u kbps", ifp->bandwidth);
      vty_out(vty, "%s", VTY_NEWLINE);
    }

  for (node = listhead (ifp->connected); node; nextnode (node))
    {
      connected = getdata (node);
      if (CHECK_FLAG (connected->conf, ZEBRA_IFC_REAL))
	connected_dump_vty (vty, connected);
    }

#ifdef RTADV
  nd_dump_vty (vty, ifp);
#endif /* RTADV */

#ifdef HAVE_PROC_NET_DEV
  /* Statistics print out using proc file system. */
  vty_out (vty, "    input packets %lu, bytes %lu, dropped %lu,"
	   " multicast packets %lu%s",
	   ifp->stats.rx_packets, ifp->stats.rx_bytes, 
	   ifp->stats.rx_dropped, ifp->stats.rx_multicast, VTY_NEWLINE);

  vty_out (vty, "    input errors %lu, length %lu, overrun %lu,"
	   " CRC %lu, frame %lu, fifo %lu, missed %lu%s",
	   ifp->stats.rx_errors, ifp->stats.rx_length_errors,
	   ifp->stats.rx_over_errors, ifp->stats.rx_crc_errors,
	   ifp->stats.rx_frame_errors, ifp->stats.rx_fifo_errors,
	   ifp->stats.rx_missed_errors, VTY_NEWLINE);

  vty_out (vty, "    output packets %lu, bytes %lu, dropped %lu%s",
	   ifp->stats.tx_packets, ifp->stats.tx_bytes,
	   ifp->stats.tx_dropped, VTY_NEWLINE);

  vty_out (vty, "    output errors %lu, aborted %lu, carrier %lu,"
	   " fifo %lu, heartbeat %lu, window %lu%s",
	   ifp->stats.tx_errors, ifp->stats.tx_aborted_errors,
	   ifp->stats.tx_carrier_errors, ifp->stats.tx_fifo_errors,
	   ifp->stats.tx_heartbeat_errors, ifp->stats.tx_window_errors,
	   VTY_NEWLINE);

  vty_out (vty, "    collisions %lu%s", ifp->stats.collisions, VTY_NEWLINE);
#endif /* HAVE_PROC_NET_DEV */

#ifdef HAVE_NET_RT_IFLIST
#if defined (__bsdi__) || defined (__NetBSD__)
  /* Statistics print out using sysctl (). */
  vty_out (vty, "    input packets %qu, bytes %qu, dropped %qu,"
	   " multicast packets %qu%s",
	   ifp->stats.ifi_ipackets, ifp->stats.ifi_ibytes,
	   ifp->stats.ifi_iqdrops, ifp->stats.ifi_imcasts,
	   VTY_NEWLINE);

  vty_out (vty, "    input errors %qu%s",
	   ifp->stats.ifi_ierrors, VTY_NEWLINE);

  vty_out (vty, "    output packets %qu, bytes %qu, multicast packets %qu%s",
	   ifp->stats.ifi_opackets, ifp->stats.ifi_obytes,
	   ifp->stats.ifi_omcasts, VTY_NEWLINE);

  vty_out (vty, "    output errors %qu%s",
	   ifp->stats.ifi_oerrors, VTY_NEWLINE);

  vty_out (vty, "    collisions %qu%s",
	   ifp->stats.ifi_collisions, VTY_NEWLINE);
#else
  /* Statistics print out using sysctl (). */
  vty_out (vty, "    input packets %lu, bytes %lu, dropped %lu,"
	   " multicast packets %lu%s",
	   ifp->stats.ifi_ipackets, ifp->stats.ifi_ibytes,
	   ifp->stats.ifi_iqdrops, ifp->stats.ifi_imcasts,
	   VTY_NEWLINE);

  vty_out (vty, "    input errors %lu%s",
	   ifp->stats.ifi_ierrors, VTY_NEWLINE);

  vty_out (vty, "    output packets %lu, bytes %lu, multicast packets %lu%s",
	   ifp->stats.ifi_opackets, ifp->stats.ifi_obytes,
	   ifp->stats.ifi_omcasts, VTY_NEWLINE);

  vty_out (vty, "    output errors %lu%s",
	   ifp->stats.ifi_oerrors, VTY_NEWLINE);

  vty_out (vty, "    collisions %lu%s",
	   ifp->stats.ifi_collisions, VTY_NEWLINE);
#endif /* __bsdi__ || __NetBSD__ */
#endif /* HAVE_NET_RT_IFLIST */
}

/* Check supported address family. */
int
if_supported_family (int family)
{
  if (family == AF_INET)
    return 1;
#ifdef HAVE_IPV6
  if (family == AF_INET6)
    return 1;
#endif /* HAVE_IPV6 */
  return 0;
}

/* Wrapper hook point for zebra daemon so that ifindex can be set 
 * DEFUN macro not used as extract.pl HAS to ignore this
 * See also interface_cmd in lib/if.c
 */ 
#undef	zebra_interface_cmd
DEFUN_NOSH (zebra_interface,
	    zebra_interface_cmd,
	    "interface IFNAME",
	    "Select an interface to configure\n"
	    "Interface's name\n")
{
  int ret;
  struct interface_FOO * ifp;
  
  /* Call lib interface() */
  ret = interface_cmd.func (self, vty, argc, argv);

  ifp = vty->index;  

  /* Set ifindex 
     this only happens if interface is NOT in kernel */
  if (ifp->ifindex == 0)
    {
      ifp->ifindex = if_new_intern_ifindex ();
      UNSET_FLAG (ifp->status, ZEBRA_INTERFACE_ACTIVE);
    }

  return ret;
}
#define	zebra_interface_cmd	zebra_interface_cmd__VAR

struct cmd_node interface_node_zebra =
{
  INTERFACE_NODE,
  "%s(config-if)# ",
  1
};

/* Show all or specified interface to vty. */
#undef	show_interface_cmd
DEFUN (show_interface, show_interface_cmd,
       "show interface [IFNAME]",  
       SHOW_STR
       "Interface status and configuration\n"
       "Inteface name\n")
{
  struct listnode *node;
  struct interface_FOO *ifp;
  
#ifdef HAVE_PROC_NET_DEV
  /* If system has interface statistics via proc file system, update
     statistics. */
  ifstat_update_proc ();
#endif /* HAVE_PROC_NET_DEV */
#ifdef HAVE_NET_RT_IFLIST
  ifstat_update_sysctl ();
#endif /* HAVE_NET_RT_IFLIST */

  /* Specified interface print. */
  if (argc != 0)
    {
      ifp = if_lookup_by_name (argv[0]);
      if (ifp == NULL) 
	{
	  vty_out (vty, "%% Can't find interface %s%s", argv[0],
		   VTY_NEWLINE);
	  return CMD_WARNING;
	}
      if_dump_vty (vty, ifp);
      return CMD_SUCCESS;
    }

  /* All interface print. */
  for (node = listhead (iflist); node; nextnode (node))
    if_dump_vty (vty, getdata (node));

  return CMD_SUCCESS;
}
#define	show_interface_cmd	show_interface_cmd__VAR

#undef	multicast_cmd
DEFUN (multicast,
       multicast_cmd,
       "multicast",
       "Set multicast flag to interface\n")
{
  int ret;
  struct interface_FOO *ifp;
  struct zebra_if *if_data;

  ifp = (struct interface_FOO *) vty->index;
  if (CHECK_FLAG (ifp->status, ZEBRA_INTERFACE_ACTIVE))
    {
      ret = if_set_flags (ifp, IFF_MULTICAST);
      if (ret < 0)
	{
	  vty_out (vty, "Can't set multicast flag%s", VTY_NEWLINE);
	  return CMD_WARNING;
	}
      if_refresh (ifp);
    }
  if_data = ifp->info;
  if_data->multicast = IF_ZEBRA_MULTICAST_ON;

  return CMD_SUCCESS;
}
#define	multicast_cmd	multicast_cmd__VAR

#undef	no_multicast_cmd
DEFUN (no_multicast,
       no_multicast_cmd,
       "no multicast",
       NO_STR
       "Unset multicast flag to interface\n")
{
  int ret;
  struct interface_FOO *ifp;
  struct zebra_if *if_data;

  ifp = (struct interface_FOO *) vty->index;
  if (CHECK_FLAG (ifp->status, ZEBRA_INTERFACE_ACTIVE))
    {
      ret = if_unset_flags (ifp, IFF_MULTICAST);
      if (ret < 0)
	{
	  vty_out (vty, "Can't unset multicast flag%s", VTY_NEWLINE);
	  return CMD_WARNING;
	}
      if_refresh (ifp);
    }
  if_data = ifp->info;
  if_data->multicast = IF_ZEBRA_MULTICAST_OFF;

  return CMD_SUCCESS;
}
#define	no_multicast_cmd	no_multicast_cmd__VAR

#undef	linkdetect_cmd
DEFUN (linkdetect,
       linkdetect_cmd,
       "link-detect",
       "Enable link detection on interface\n")
{
  struct interface_FOO *ifp;
  int if_was_operative;
  
  ifp = (struct interface_FOO *) vty->index;
  if_was_operative = if_is_operative(ifp);
  SET_FLAG(ifp->status, ZEBRA_INTERFACE_LINKDETECTION);

  /* When linkdetection is enabled, if might come down */
  if (!if_is_operative(ifp) && if_was_operative) if_down(ifp);

  /* FIXME: Will defer status change forwarding if interface
     does not come down! */

  return CMD_SUCCESS;
}
#define	linkdetect_cmd	linkdetect_cmd__VAR


#undef	no_linkdetect_cmd
DEFUN (no_linkdetect,
       no_linkdetect_cmd,
       "no link-detect",
       NO_STR
       "Disable link detection on interface\n")
{
  struct interface_FOO *ifp;
  int if_was_operative;

  ifp = (struct interface_FOO *) vty->index;
  if_was_operative = if_is_operative(ifp);
  UNSET_FLAG(ifp->status, ZEBRA_INTERFACE_LINKDETECTION);
  
  /* Interface may come up after disabling link detection */
  if (if_is_operative(ifp) && !if_was_operative) if_up(ifp);

  /* FIXME: see linkdetect_cmd */

  return CMD_SUCCESS;
}
#define	no_linkdetect_cmd	no_linkdetect_cmd__VAR

#undef	shutdown_if_cmd
DEFUN (shutdown_if,
       shutdown_if_cmd,
       "shutdown",
       "Shutdown the selected interface\n")
{
  int ret;
  struct interface_FOO *ifp;
  struct zebra_if *if_data;

  ifp = (struct interface_FOO *) vty->index;
  ret = if_unset_flags (ifp, IFF_UP);
  if (ret < 0)
    {
      vty_out (vty, "Can't shutdown interface%s", VTY_NEWLINE);
      return CMD_WARNING;
    }
  if_refresh (ifp);
  if_data = ifp->info;
  if_data->shutdown = IF_ZEBRA_SHUTDOWN_ON;

  return CMD_SUCCESS;
}
#define	shutdown_if_cmd	shutdown_if_cmd__VAR

#undef	no_shutdown_if_cmd
DEFUN (no_shutdown_if,
       no_shutdown_if_cmd,
       "no shutdown",
       NO_STR
       "Shutdown the selected interface\n")
{
  int ret;
  struct interface_FOO *ifp;
  struct zebra_if *if_data;

  ifp = (struct interface_FOO *) vty->index;
  ret = if_set_flags (ifp, IFF_UP | IFF_RUNNING);
  if (ret < 0)
    {
      vty_out (vty, "Can't up interface%s", VTY_NEWLINE);
      return CMD_WARNING;
    }
  if_refresh (ifp);
  if_data = ifp->info;
  if_data->shutdown = IF_ZEBRA_SHUTDOWN_OFF;

  return CMD_SUCCESS;
}
#define	no_shutdown_if_cmd	no_shutdown_if_cmd__VAR

#undef	bandwidth_if_cmd
DEFUN (bandwidth_if,
       bandwidth_if_cmd,
       "bandwidth <1-10000000>",
       "Set bandwidth informational parameter\n"
       "Bandwidth in kilobits\n")
{
  struct interface_FOO *ifp;   
  unsigned int bandwidth;
  
  ifp = (struct interface_FOO *) vty->index;
  bandwidth = strtol(argv[0], NULL, 10);

  /* bandwidth range is <1-10000000> */
  if (bandwidth < 1 || bandwidth > 10000000)
    {
      vty_out (vty, "Bandwidth is invalid%s", VTY_NEWLINE);
      return CMD_WARNING;
    }
  
  ifp->bandwidth = bandwidth;

  /* force protocols to recalculate routes due to cost change */
  if (if_is_operative (ifp))
    zebra_interface_up_update (ifp);
  
  return CMD_SUCCESS;
}
#define	bandwidth_if_cmd	bandwidth_if_cmd__VAR

#undef	no_bandwidth_if_cmd
DEFUN (no_bandwidth_if,
       no_bandwidth_if_cmd,
       "no bandwidth",
       NO_STR
       "Set bandwidth informational parameter\n")
{
  struct interface_FOO *ifp;   
  
  ifp = (struct interface_FOO *) vty->index;

  ifp->bandwidth = 0;
  
  /* force protocols to recalculate routes due to cost change */
  if (if_is_operative (ifp))
    zebra_interface_up_update (ifp);

  return CMD_SUCCESS;
}
#define	no_bandwidth_if_cmd	no_bandwidth_if_cmd__VAR

#undef	no_bandwidth_if_val_cmd
ALIAS (no_bandwidth_if,
       no_bandwidth_if_val_cmd,
       "no bandwidth <1-10000000>",
       NO_STR
       "Set bandwidth informational parameter\n"
       "Bandwidth in kilobits\n");
#define	no_bandwidth_if_val_cmd	no_bandwidth_if_val_cmd__VAR

int
ip_address_install (struct vty *vty, struct interface_FOO *ifp,
		    const char *addr_str, const char *peer_str,
		    const char *label)
{
  struct prefix_ipv4 cp;
  struct connected *ifc;
  struct prefix_ipv4 *p;
  int ret;

  ret = str2prefix_ipv4 (addr_str, &cp);
  if (ret <= 0)
    {
      vty_out (vty, "%% Malformed address %s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  ifc = connected_check_ipv4 (ifp, (struct prefix *) &cp);
  if (! ifc)
    {
      ifc = connected_new ();
      ifc->ifp = ifp;

      /* Address. */
      p = prefix_ipv4_new ();
      *p = cp;
      ifc->address = (struct prefix *) p;

      /* Broadcast. */
      if (p->prefixlen <= IPV4_MAX_PREFIXLEN-2)
	{
	  p = prefix_ipv4_new ();
	  *p = cp;
	  p->prefix.s_addr = ipv4_broadcast_addr(p->prefix.s_addr,p->prefixlen);
	  ifc->destination = (struct prefix *) p;
	}

      /* Label. */
      if (label)
	ifc->label = strdup (label);

      /* Add to linked list. */
      listnode_add (ifp->connected, ifc);
    }

  /* This address is configured from zebra. */
  if (! CHECK_FLAG (ifc->conf, ZEBRA_IFC_CONFIGURED))
    SET_FLAG (ifc->conf, ZEBRA_IFC_CONFIGURED);

  /* In case of this route need to install kernel. */
  if (! CHECK_FLAG (ifc->conf, ZEBRA_IFC_REAL)
      && CHECK_FLAG (ifp->status, ZEBRA_INTERFACE_ACTIVE))
    {
      /* Some system need to up the interface to set IP address. */
      if (! if_is_up (ifp))
	{
	  if_set_flags (ifp, IFF_UP | IFF_RUNNING);
	  if_refresh (ifp);
	}

      ret = if_set_prefix (ifp, ifc);
      if (ret < 0)
	{
	  vty_out (vty, "%% Can't set interface IP address: %s.%s", 
		   safe_strerror(errno), VTY_NEWLINE);
	  return CMD_WARNING;
	}

      /* IP address propery set. */
      SET_FLAG (ifc->conf, ZEBRA_IFC_REAL);

      /* Update interface address information to protocol daemon. */
      zebra_interface_address_add_update (ifp, ifc);

      /* If interface is up register connected route. */
      if (if_is_operative(ifp))
	connected_up_ipv4 (ifp, ifc);
    }

  return CMD_SUCCESS;
}

int
ip_address_uninstall (struct vty *vty, struct interface_FOO *ifp,
		      const char *addr_str, const char *peer_str,
		      const char *label)
{
  struct prefix_ipv4 cp;
  struct connected *ifc;
  int ret;

  /* Convert to prefix structure. */
  ret = str2prefix_ipv4 (addr_str, &cp);
  if (ret <= 0)
    {
      vty_out (vty, "%% Malformed address %s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  /* Check current interface address. */
  ifc = connected_check_ipv4 (ifp, (struct prefix *) &cp);
  if (! ifc)
    {
      vty_out (vty, "%% Can't find address%s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  /* This is not configured address. */
  if (! CHECK_FLAG (ifc->conf, ZEBRA_IFC_CONFIGURED))
    return CMD_WARNING;

  /* This is not real address or interface is not active. */
  if (! CHECK_FLAG (ifc->conf, ZEBRA_IFC_REAL)
      || ! CHECK_FLAG (ifp->status, ZEBRA_INTERFACE_ACTIVE))
    {
      listnode_delete (ifp->connected, ifc);
      connected_free (ifc);
      return CMD_WARNING;
    }

  /* This is real route. */
  ret = if_unset_prefix (ifp, ifc);
  if (ret < 0)
    {
      vty_out (vty, "%% Can't unset interface IP address: %s.%s", 
	       safe_strerror(errno), VTY_NEWLINE);
      return CMD_WARNING;
    }

  /* Redistribute this information. */
  zebra_interface_address_delete_update (ifp, ifc);

  /* Remove connected route. */
  connected_down_ipv4 (ifp, ifc);

  /* Free address information. */
  listnode_delete (ifp->connected, ifc);
  connected_free (ifc);

  return CMD_SUCCESS;
}

#undef	ip_address_cmd
DEFUN (ip_address,
       ip_address_cmd,
       "ip address A.B.C.D/M",
       "Interface Internet Protocol config commands\n"
       "Set the IP address of an interface\n"
       "IP address (e.g. 10.0.0.1/8)\n")
{
  return ip_address_install (vty, vty->index, argv[0], NULL, NULL);
}
#define	ip_address_cmd	ip_address_cmd__VAR

#undef	no_ip_address_cmd
DEFUN (no_ip_address,
       no_ip_address_cmd,
       "no ip address A.B.C.D/M",
       NO_STR
       "Interface Internet Protocol config commands\n"
       "Set the IP address of an interface\n"
       "IP Address (e.g. 10.0.0.1/8)")
{
  return ip_address_uninstall (vty, vty->index, argv[0], NULL, NULL);
}
#define	no_ip_address_cmd	no_ip_address_cmd__VAR

#ifdef HAVE_NETLINK
#undef	ip_address_label_cmd
DEFUN (ip_address_label,
       ip_address_label_cmd,
       "ip address A.B.C.D/M label LINE",
       "Interface Internet Protocol config commands\n"
       "Set the IP address of an interface\n"
       "IP address (e.g. 10.0.0.1/8)\n"
       "Label of this address\n"
       "Label\n")
{
  return ip_address_install (vty, vty->index, argv[0], NULL, argv[1]);
}
#define	ip_address_label_cmd	ip_address_label_cmd__VAR

#undef	no_ip_address_label_cmd
DEFUN (no_ip_address_label,
       no_ip_address_label_cmd,
       "no ip address A.B.C.D/M label LINE",
       NO_STR
       "Interface Internet Protocol config commands\n"
       "Set the IP address of an interface\n"
       "IP address (e.g. 10.0.0.1/8)\n"
       "Label of this address\n"
       "Label\n")
{
  return ip_address_uninstall (vty, vty->index, argv[0], NULL, argv[1]);
}
#define	no_ip_address_label_cmd	no_ip_address_label_cmd__VAR
#endif /* HAVE_NETLINK */

#ifdef HAVE_IPV6
int
ipv6_address_install (struct vty *vty, struct interface_FOO *ifp,
		      const char *addr_str, const char *peer_str,
		      const char *label, int secondary)
{
  struct prefix_ipv6 cp;
  struct connected *ifc;
  struct prefix_ipv6 *p;
  int ret;

  ret = str2prefix_ipv6 (addr_str, &cp);
  if (ret <= 0)
    {
      vty_out (vty, "%% Malformed address %s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  ifc = connected_check_ipv6 (ifp, (struct prefix *) &cp);
  if (! ifc)
    {
      ifc = connected_new ();
      ifc->ifp = ifp;

      /* Address. */
      p = prefix_ipv6_new ();
      *p = cp;
      ifc->address = (struct prefix *) p;

      /* Secondary. */
      if (secondary)
	SET_FLAG (ifc->flags, ZEBRA_IFA_SECONDARY);

      /* Label. */
      if (label)
	ifc->label = strdup (label);

      /* Add to linked list. */
      listnode_add (ifp->connected, ifc);
    }

  /* This address is configured from zebra. */
  if (! CHECK_FLAG (ifc->conf, ZEBRA_IFC_CONFIGURED))
    SET_FLAG (ifc->conf, ZEBRA_IFC_CONFIGURED);

  /* In case of this route need to install kernel. */
  if (! CHECK_FLAG (ifc->conf, ZEBRA_IFC_REAL)
      && CHECK_FLAG (ifp->status, ZEBRA_INTERFACE_ACTIVE))
    {
      /* Some system need to up the interface to set IP address. */
      if (! if_is_up (ifp))
	{
	  if_set_flags (ifp, IFF_UP | IFF_RUNNING);
	  if_refresh (ifp);
	}

      ret = if_prefix_add_ipv6 (ifp, ifc);

      if (ret < 0)
	{
	  vty_out (vty, "%% Can't set interface IP address: %s.%s", 
		   safe_strerror(errno), VTY_NEWLINE);
	  return CMD_WARNING;
	}

      /* IP address propery set. */
      SET_FLAG (ifc->conf, ZEBRA_IFC_REAL);

      /* Update interface address information to protocol daemon. */
      zebra_interface_address_add_update (ifp, ifc);

      /* If interface is up register connected route. */
      if (if_is_operative(ifp))
	connected_up_ipv6 (ifp, ifc);
    }

  return CMD_SUCCESS;
}

int
ipv6_address_uninstall (struct vty *vty, struct interface_FOO *ifp,
			const char *addr_str, const char *peer_str,
			const char *label, int secondry)
{
  struct prefix_ipv6 cp;
  struct connected *ifc;
  int ret;

  /* Convert to prefix structure. */
  ret = str2prefix_ipv6 (addr_str, &cp);
  if (ret <= 0)
    {
      vty_out (vty, "%% Malformed address %s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  /* Check current interface address. */
  ifc = connected_check_ipv6 (ifp, (struct prefix *) &cp);
  if (! ifc)
    {
      vty_out (vty, "%% Can't find address%s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  /* This is not configured address. */
  if (! CHECK_FLAG (ifc->conf, ZEBRA_IFC_CONFIGURED))
    return CMD_WARNING;

  /* This is not real address or interface is not active. */
  if (! CHECK_FLAG (ifc->conf, ZEBRA_IFC_REAL)
      || ! CHECK_FLAG (ifp->status, ZEBRA_INTERFACE_ACTIVE))
    {
      listnode_delete (ifp->connected, ifc);
      connected_free (ifc);
      return CMD_WARNING;
    }

  /* This is real route. */
  ret = if_prefix_delete_ipv6 (ifp, ifc);
  if (ret < 0)
    {
      vty_out (vty, "%% Can't unset interface IP address: %s.%s", 
	       safe_strerror(errno), VTY_NEWLINE);
      return CMD_WARNING;
    }

  /* Redistribute this information. */
  zebra_interface_address_delete_update (ifp, ifc);

  /* Remove connected route. */
  connected_down_ipv6 (ifp, ifc);

  /* Free address information. */
  listnode_delete (ifp->connected, ifc);
  connected_free (ifc);

  return CMD_SUCCESS;
}

DEFUN (ipv6_address,
       ipv6_address_cmd,
       "ipv6 address X:X::X:X/M",
       "Interface IPv6 config commands\n"
       "Set the IP address of an interface\n"
       "IPv6 address (e.g. 3ffe:506::1/48)\n")
{
  return ipv6_address_install (vty, vty->index, argv[0], NULL, NULL, 0);
}

DEFUN (no_ipv6_address,
       no_ipv6_address_cmd,
       "no ipv6 address X:X::X:X/M",
       NO_STR
       "Interface IPv6 config commands\n"
       "Set the IP address of an interface\n"
       "IPv6 address (e.g. 3ffe:506::1/48)\n")
{
  return ipv6_address_uninstall (vty, vty->index, argv[0], NULL, NULL, 0);
}
#endif /* HAVE_IPV6 */

int
if_config_write (struct vty *vty)
{
  struct listnode *node;
  struct interface_FOO *ifp;
  char buf[BUFSIZ];

  for (node = listhead (iflist); node; nextnode (node))
    {
      struct zebra_if *if_data;
      struct listnode *addrnode;
      struct connected *ifc;
      struct prefix *p;

      ifp = getdata (node);
      if_data = ifp->info;
      
      vty_out (vty, "interface %s%s", ifp->name,
	       VTY_NEWLINE);

      if (ifp->desc)
	vty_out (vty, " description %s%s", ifp->desc,
		 VTY_NEWLINE);

      /* Assign bandwidth here to avoid unnecessary interface flap
	 while processing config script */
      if (ifp->bandwidth != 0)
	vty_out(vty, " bandwidth %u%s", ifp->bandwidth, VTY_NEWLINE); 

      if (CHECK_FLAG(ifp->status, ZEBRA_INTERFACE_LINKDETECTION))
	vty_out(vty, " link-detect%s", VTY_NEWLINE);

      for (addrnode = listhead (ifp->connected); addrnode; nextnode (addrnode))
	  {
	    ifc = getdata (addrnode);
	    if (CHECK_FLAG (ifc->conf, ZEBRA_IFC_CONFIGURED))
	      {
		p = ifc->address;
		vty_out (vty, " ip%s address %s/%d",
			 p->family == AF_INET ? "" : "v6",
			 inet_ntop (p->family, &p->u.prefix, buf, BUFSIZ),
			 p->prefixlen);

		if (ifc->label)
		  vty_out (vty, " label %s", ifc->label);

		vty_out (vty, "%s", VTY_NEWLINE);
	      }
	  }

      if (if_data)
	{
	  if (if_data->shutdown == IF_ZEBRA_SHUTDOWN_ON)
	    vty_out (vty, " shutdown%s", VTY_NEWLINE);

	  if (if_data->multicast != IF_ZEBRA_MULTICAST_UNSPEC)
	    vty_out (vty, " %smulticast%s",
		     if_data->multicast == IF_ZEBRA_MULTICAST_ON ? "" : "no ",
		     VTY_NEWLINE);
	}

#ifdef RTADV
      rtadv_config_write (vty, ifp);
#endif /* RTADV */

#ifdef HAVE_IRDP
      irdp_config_write (vty, ifp);
#endif /* IRDP */

      vty_out (vty, "!%s", VTY_NEWLINE);
    }
  return 0;
}

/* Allocate and initialize interface vector. */
void
zebra_if_init ()
{
  /* Initialize interface and new hook. */
  if_init ();
  if_add_hook (IF_NEW_HOOK, if_zebra_new_hook);
  if_add_hook (IF_DELETE_HOOK, if_zebra_delete_hook);
  
  /* Install configuration write function. */
  install_node (&interface_node, if_config_write);

  install_element (VIEW_NODE, &show_interface_cmd);
  install_element (ENABLE_NODE, &show_interface_cmd);
  install_element (CONFIG_NODE, &zebra_interface_cmd);
  install_element (CONFIG_NODE, &no_interface_cmd);
  install_default (INTERFACE_NODE);
  install_element (INTERFACE_NODE, &interface_desc_cmd);
  install_element (INTERFACE_NODE, &no_interface_desc_cmd);
  install_element (INTERFACE_NODE, &multicast_cmd);
  install_element (INTERFACE_NODE, &no_multicast_cmd);
  install_element (INTERFACE_NODE, &linkdetect_cmd);
  install_element (INTERFACE_NODE, &no_linkdetect_cmd);
  install_element (INTERFACE_NODE, &shutdown_if_cmd);
  install_element (INTERFACE_NODE, &no_shutdown_if_cmd);
  install_element (INTERFACE_NODE, &bandwidth_if_cmd);
  install_element (INTERFACE_NODE, &no_bandwidth_if_cmd);
  install_element (INTERFACE_NODE, &no_bandwidth_if_val_cmd);
  install_element (INTERFACE_NODE, &ip_address_cmd);
  install_element (INTERFACE_NODE, &no_ip_address_cmd);
#ifdef HAVE_IPV6
  install_element (INTERFACE_NODE, &ipv6_address_cmd);
  install_element (INTERFACE_NODE, &no_ipv6_address_cmd);
#endif /* HAVE_IPV6 */
#ifdef HAVE_NETLINK
  install_element (INTERFACE_NODE, &ip_address_label_cmd);
  install_element (INTERFACE_NODE, &no_ip_address_label_cmd);
#endif /* HAVE_NETLINK */
}
