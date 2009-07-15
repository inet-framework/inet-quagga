/* Interface related header.
   Copyright (C) 1997, 98, 99 Kunihiro Ishiguro

This file is part of GNU Zebra.

GNU Zebra is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published
by the Free Software Foundation; either version 2, or (at your
option) any later version.

GNU Zebra is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU Zebra; see the file COPYING.  If not, write to the
Free Software Foundation, Inc., 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

#ifndef _ZEBRA_IF_H
#define _ZEBRA_IF_H

#include "linklist.h"

/*
  Interface name length.

   Linux define value in /usr/include/linux/if.h.
   #define IFNAMSIZ        16

   FreeBSD define value in /usr/include/net/if.h.
   #define IFNAMSIZ        16
*/

#define INTERFACE_NAMSIZ      20
#define INTERFACE_HWADDR_MAX  20

/* Internal If indexes start at 0xFFFFFFFF and go down to 1 greater
   than this */
#define IFINDEX_INTERNBASE 0x80000000

#ifdef HAVE_PROC_NET_DEV
struct if_stats
{
  unsigned long rx_packets;   /* total packets received       */
  unsigned long tx_packets;   /* total packets transmitted    */
  unsigned long rx_bytes;     /* total bytes received         */
  unsigned long tx_bytes;     /* total bytes transmitted      */
  unsigned long rx_errors;    /* bad packets received         */
  unsigned long tx_errors;    /* packet transmit problems     */
  unsigned long rx_dropped;   /* no space in linux buffers    */
  unsigned long tx_dropped;   /* no space available in linux  */
  unsigned long rx_multicast; /* multicast packets received   */
  unsigned long rx_compressed;
  unsigned long tx_compressed;
  unsigned long collisions;

  /* detailed rx_errors: */
  unsigned long rx_length_errors;
  unsigned long rx_over_errors;       /* receiver ring buff overflow  */
  unsigned long rx_crc_errors;        /* recved pkt with crc error    */
  unsigned long rx_frame_errors;      /* recv'd frame alignment error */
  unsigned long rx_fifo_errors;       /* recv'r fifo overrun          */
  unsigned long rx_missed_errors;     /* receiver missed packet     */
  /* detailed tx_errors */
  unsigned long tx_aborted_errors;
  unsigned long tx_carrier_errors;
  unsigned long tx_fifo_errors;
  unsigned long tx_heartbeat_errors;
  unsigned long tx_window_errors;
};
#endif /* HAVE_PROC_NET_DEV */

/* Interface structure */
struct interface_FOO 
{
  /* Interface name. */
  char name[INTERFACE_NAMSIZ + 1];

  /* Interface index. */
  unsigned int ifindex;

  /* Zebra internal interface status */
  u_char status;
#define ZEBRA_INTERFACE_ACTIVE     (1 << 0)
#define ZEBRA_INTERFACE_SUB        (1 << 1)
#define ZEBRA_INTERFACE_LINKDETECTION (1 << 2)
  
  /* Interface flags. */
  unsigned long flags;

  /* Interface metric */
  int metric;

  /* Interface MTU. */
  unsigned int mtu;    /* IPv4 MTU */
  unsigned int mtu6;   /* IPv6 MTU - probably, but not neccessarily same as mtu */

  /* Hardware address. */
#ifdef HAVE_SOCKADDR_DL
  struct sockaddr_dl sdl;
#else
  unsigned short hw_type;
  u_char hw_addr[INTERFACE_HWADDR_MAX];
  int hw_addr_len;
#endif /* HAVE_SOCKADDR_DL */

  /* interface bandwidth, kbits */
  unsigned int bandwidth;
  
  /* description of the interface. */
  char *desc;			

  /* Distribute list. */
  void *distribute_in;
  void *distribute_out;

  /* Connected address list. */
  struct list *connected;

  /* Daemon specific interface data pointer. */
  void *info;

  /* Statistics fileds. */
#ifdef HAVE_PROC_NET_DEV
  struct if_stats stats;
#endif /* HAVE_PROC_NET_DEV */  
#ifdef HAVE_NET_RT_IFLIST
  struct if_data stats;
#endif /* HAVE_NET_RT_IFLIST */
};

/* Connected address structure. */
struct connected
{
  /* Attached interface. */
  struct interface_FOO *ifp;

  /* Flags for configuration. */
  u_char conf;
#define ZEBRA_IFC_REAL         (1 << 0)
#define ZEBRA_IFC_CONFIGURED   (1 << 1)

  /* Flags for connected address. */
  u_char flags;
#define ZEBRA_IFA_SECONDARY   (1 << 0)

  /* Address of connected network. */
  struct prefix *address;
  struct prefix *destination; /* broadcast or peer address; may be NULL */

  /* Label for Linux 2.2.X and upper. */
  char *label;
};

/* Given an IPV4 struct connected, this macro determines whether a /32
   peer address has been supplied (i.e. there is no subnet assigned) */
#define CONNECTED_DEST_HOST(C) \
	((C)->destination && ((C)->address->prefixlen == IPV4_MAX_PREFIXLEN))

/* Given an IPV4 struct connected, this macro determins whether it is
   a point-to-point link with a /32 peer address (i.e. there
   is no dedicated subnet for the PtP link) */
#define CONNECTED_POINTOPOINT_HOST(C) \
	(((C)->ifp->flags & IFF_POINTOPOINT) && CONNECTED_DEST_HOST(C))

/* Interface hook sort. */
#define IF_NEW_HOOK   0
#define IF_DELETE_HOOK 1

/* There are some interface flags which are only supported by some
   operating system. */

#ifndef IFF_NOTRAILERS
#define IFF_NOTRAILERS 0x0
#endif /* IFF_NOTRAILERS */
#ifndef IFF_OACTIVE
#define IFF_OACTIVE 0x0
#endif /* IFF_OACTIVE */
#ifndef IFF_SIMPLEX
#define IFF_SIMPLEX 0x0
#endif /* IFF_SIMPLEX */
#ifndef IFF_LINK0
#define IFF_LINK0 0x0
#endif /* IFF_LINK0 */
#ifndef IFF_LINK1
#define IFF_LINK1 0x0
#endif /* IFF_LINK1 */
#ifndef IFF_LINK2
#define IFF_LINK2 0x0
#endif /* IFF_LINK2 */
#ifndef IFF_NOXMIT
#define IFF_NOXMIT 0x0
#endif /* IFF_NOXMIT */
#ifndef IFF_NORTEXCH
#define IFF_NORTEXCH 0x0
#endif /* IFF_NORTEXCH */
#ifndef IFF_IPV4
#define IFF_IPV4 0x0
#endif /* IFF_IPV4 */
#ifndef IFF_IPV6
#define IFF_IPV6 0x0
#endif /* IFF_IPV6 */
#ifndef IFF_VIRTUAL
#define IFF_VIRTUAL 0x0
#endif /* IFF_VIRTUAL */

/* Prototypes. */
int if_cmp_func (struct interface_FOO *, struct interface_FOO *);
struct interface_FOO *if_new (void);
struct interface_FOO *if_create (const char *name, int namelen);
struct interface_FOO *if_lookup_by_index (unsigned int);
struct interface_FOO *if_lookup_by_name (const char *);
struct interface_FOO *if_lookup_exact_address (struct in_addr);
struct interface_FOO *if_lookup_address (struct in_addr);
struct interface_FOO *if_get_by_name (const char *);
void if_delete (struct interface_FOO *);
int if_is_up (struct interface_FOO *);
int if_is_running (struct interface_FOO *);
int if_is_operative (struct interface_FOO *);
int if_is_loopback (struct interface_FOO *);
int if_is_broadcast (struct interface_FOO *);
int if_is_pointopoint (struct interface_FOO *);
int if_is_multicast (struct interface_FOO *);
void if_add_hook (int, int (*)(struct interface_FOO *));
void if_init ();
void if_dump_all ();
char *ifindex2ifname (unsigned int);
extern const char *if_flag_dump(unsigned long);

/* Connected address functions. */
struct connected *connected_new ();
void connected_free (struct connected *);
void connected_add (struct interface_FOO *, struct connected *);
struct connected  *connected_add_by_prefix (struct interface_FOO *,
                                            struct prefix *,
                                            struct prefix *);
struct connected  *connected_delete_by_prefix (struct interface_FOO *, 
                                               struct prefix *);
struct connected  *connected_lookup_address (struct interface_FOO *, 
                                             struct in_addr);

#ifndef HAVE_IF_NAMETOINDEX
unsigned int if_nametoindex (const char *);
#endif
#ifndef HAVE_IF_INDEXTONAME
char *if_indextoname (unsigned int, char *);
#endif

/* Exported variables. */
extern struct list *iflist_lib;
extern struct cmd_element interface_desc_cmd_lib;
extern struct cmd_element no_interface_desc_cmd_lib;
extern struct cmd_element interface_cmd_lib;
extern struct cmd_element no_interface_cmd_lib;
// interface_pseudo_cmd not used
// no_interface_pseudo_cmd not used

typedef int (*if_hook_func) (struct interface_FOO *);

struct_if_master
{
  if_hook_func if_new_hook;
  if_hook_func if_delete_hook;
};

#endif /* _ZEBRA_IF_H */
