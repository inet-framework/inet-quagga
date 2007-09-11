/*
 * Address linked list routine.
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

#include "prefix.h"
#include "linklist.h"
#include "if.h"
#include "table.h"
#include "rib.h"
#include "table.h"
#include "log.h"

#include "zebra/zserv.h"
#include "zebra/redistribute.h"

/* If same interface address is already exist... */
struct connected *
connected_check_ipv4 (struct interface_FOO *ifp, struct prefix *p)
{
  struct connected *ifc;
  struct listnode *node;

  for (node = listhead (ifp->connected); node; node = nextnode (node))
    {
      ifc = getdata (node);

      if (prefix_same (ifc->address, p))
	return ifc;
    }
  return NULL;
}

/* Called from if_up(). */
void
connected_up_ipv4 (struct interface_FOO *ifp, struct connected *ifc)
{
  struct prefix_ipv4 p;
  struct prefix_ipv4 *addr;
  struct prefix_ipv4 *dest;

  if (! CHECK_FLAG (ifc->conf, ZEBRA_IFC_REAL))
    return;

  addr = (struct prefix_ipv4 *) ifc->address;
  dest = (struct prefix_ipv4 *) ifc->destination;

  memset (&p, 0, sizeof (struct prefix_ipv4));
  p.family = AF_INET;
  p.prefixlen = addr->prefixlen;

  /* Point-to-point check. */
  if (CONNECTED_POINTOPOINT_HOST(ifc))
    p.prefix = dest->prefix;
  else
    p.prefix = addr->prefix;

  /* Apply mask to the network. */
  apply_mask_ipv4 (&p);

  /* In case of connected address is 0.0.0.0/0 we treat it tunnel
     address. */
  if (prefix_ipv4_any (&p))
    return;

  rib_add_ipv4 (ZEBRA_ROUTE_CONNECT, 0, &p, NULL, ifp->ifindex, 0, 0, 0);

  rib_update ();
}

/* Add connected IPv4 route to the interface. */
void
connected_add_ipv4 (struct interface_FOO *ifp, int flags, struct in_addr *addr, 
		    int prefixlen, struct in_addr *broad, char *label)
{
  struct prefix_ipv4 *p;
  struct connected *ifc;
  struct connected *current;

  /* Make connected structure. */
  ifc = connected_new ();
  ifc->ifp = ifp;
  ifc->flags = flags;

  /* Allocate new connected address. */
  p = prefix_ipv4_new ();
  p->family = AF_INET;
  p->prefix = *addr;
  p->prefixlen = prefixlen;
  ifc->address = (struct prefix *) p;

  /* If there is broadcast or pointopoint address. */
  if (broad)
    {
      p = prefix_ipv4_new ();
      p->family = AF_INET;
      p->prefix = *broad;
      ifc->destination = (struct prefix *) p;

      /* validate the destination address */
      if (ifp->flags & IFF_POINTOPOINT)
        {
	  if (IPV4_ADDR_SAME(addr,broad))
	    zlog_warn("warning: PtP interface %s has same local and peer "
		      "address %s, routing protocols may malfunction",
		      ifp->name,inet_ntoa(*addr));
	  else if ((prefixlen != IPV4_MAX_PREFIXLEN) &&
	   	   (ipv4_network_addr(addr->s_addr,prefixlen) !=
	   	    ipv4_network_addr(broad->s_addr,prefixlen)))
	    {
	      char buf[2][INET_ADDRSTRLEN];
	      zlog_warn("warning: PtP interface %s network mismatch: local "
	      		"%s/%d vs. peer %s, routing protocols may malfunction",
	    		ifp->name,
			inet_ntop (AF_INET, addr, buf[0], sizeof(buf[0])),
			prefixlen,
			inet_ntop (AF_INET, broad, buf[1], sizeof(buf[1])));
	    }
        }
      else
        {
	  if (broad->s_addr != ipv4_broadcast_addr(addr->s_addr,prefixlen))
	    {
	      char buf[2][INET_ADDRSTRLEN];
	      struct in_addr bcalc;
	      bcalc.s_addr = ipv4_broadcast_addr(addr->s_addr,prefixlen);
	      zlog_warn("warning: interface %s broadcast addr %s/%d != "
	       		"calculated %s, routing protocols may malfunction",
	    		ifp->name,
			inet_ntop (AF_INET, broad, buf[0], sizeof(buf[0])),
			prefixlen,
			inet_ntop (AF_INET, &bcalc, buf[1], sizeof(buf[1])));
	    }
        }

    }
  else
    /* no broadcast or destination address was supplied */
    if ((prefixlen == IPV4_MAX_PREFIXLEN) && if_is_pointopoint(ifp))
      zlog_warn("warning: PtP interface %s with addr %s/%d needs a "
      		"peer address",ifp->name,inet_ntoa(*addr),prefixlen);

  /* Label of this address. */
  if (label)
    ifc->label = strdup (label);

  /* Check same connected route. */
  current = connected_check_ipv4 (ifp, (struct prefix *) ifc->address);
  if (current)
    {
      connected_free (ifc);
      ifc = current;
    }
  else
    {
      listnode_add (ifp->connected, ifc);
    }

  /* Update interface address information to protocol daemon. */
  if (! CHECK_FLAG (ifc->conf, ZEBRA_IFC_REAL))
    {
      SET_FLAG (ifc->conf, ZEBRA_IFC_REAL);

      zebra_interface_address_add_update (ifp, ifc);

      if (if_is_up(ifp))
	connected_up_ipv4 (ifp, ifc);
    }
}

void
connected_down_ipv4 (struct interface_FOO *ifp, struct connected *ifc)
{
  struct prefix_ipv4 p;
  struct prefix_ipv4 *addr;
  struct prefix_ipv4 *dest;

  if (! CHECK_FLAG (ifc->conf, ZEBRA_IFC_REAL))
    return;

  addr = (struct prefix_ipv4 *)ifc->address;
  dest = (struct prefix_ipv4 *)ifc->destination;

  memset (&p, 0, sizeof (struct prefix_ipv4));
  p.family = AF_INET;
  p.prefixlen = addr->prefixlen;

  /* Point-to-point check. */
  if (CONNECTED_POINTOPOINT_HOST(ifc))
    p.prefix = dest->prefix;
  else
    p.prefix = addr->prefix;

  /* Apply mask to the network. */
  apply_mask_ipv4 (&p);

  /* In case of connected address is 0.0.0.0/0 we treat it tunnel
     address. */
  if (prefix_ipv4_any (&p))
    return;

  rib_delete_ipv4 (ZEBRA_ROUTE_CONNECT, 0, &p, NULL, ifp->ifindex, 0);

  rib_update ();
}

/* Delete connected IPv4 route to the interface. */
void
connected_delete_ipv4 (struct interface_FOO *ifp, int flags, struct in_addr *addr,
		       int prefixlen, struct in_addr *broad, char *label)
{
  struct prefix_ipv4 p;
  struct connected *ifc;

  memset (&p, 0, sizeof (struct prefix_ipv4));
  p.family = AF_INET;
  p.prefix = *addr;
  p.prefixlen = prefixlen;

  ifc = connected_check_ipv4 (ifp, (struct prefix *) &p);
  if (! ifc)
    return;

  /* Update interface address information to protocol daemon. */
  if (CHECK_FLAG (ifc->conf, ZEBRA_IFC_REAL))
    {
      zebra_interface_address_delete_update (ifp, ifc);

      connected_down_ipv4 (ifp, ifc);

      UNSET_FLAG (ifc->conf, ZEBRA_IFC_REAL);
    }

  if (! CHECK_FLAG (ifc->conf, ZEBRA_IFC_CONFIGURED))
    {
      listnode_delete (ifp->connected, ifc);
      connected_free (ifc);
    }
}

#ifdef HAVE_IPV6
/* If same interface address is already exist... */
struct connected *
connected_check_ipv6 (struct interface_FOO *ifp, struct prefix *p)
{
  struct connected *ifc;
  struct listnode *node;

  for (node = listhead (ifp->connected); node; node = nextnode (node))
    {
      ifc = getdata (node);

      if (prefix_same (ifc->address, p))
	return ifc;
    }
  return 0;
}

void
connected_up_ipv6 (struct interface_FOO *ifp, struct connected *ifc)
{
  struct prefix_ipv6 p;
  struct prefix_ipv6 *addr;
  struct prefix_ipv6 *dest;

  if (! CHECK_FLAG (ifc->conf, ZEBRA_IFC_REAL))
    return;

  addr = (struct prefix_ipv6 *) ifc->address;
  dest = (struct prefix_ipv6 *) ifc->destination;

  memset (&p, 0, sizeof (struct prefix_ipv6));
  p.family = AF_INET6;
  p.prefixlen = addr->prefixlen;

  if (if_is_pointopoint (ifp) && dest)
    {
      if (IN6_IS_ADDR_UNSPECIFIED (&dest->prefix))
	p.prefix = addr->prefix;
      else
	p.prefix = dest->prefix;
    }
  else
    p.prefix = addr->prefix;

  /* Apply mask to the network. */
  apply_mask_ipv6 (&p);

#if ! defined (MUSICA) && ! defined (LINUX)
  /* XXX: It is already done by rib_bogus_ipv6 within rib_add_ipv6 */
  if (IN6_IS_ADDR_UNSPECIFIED (&p.prefix))
    return;
#endif

  rib_add_ipv6 (ZEBRA_ROUTE_CONNECT, 0, &p, NULL, ifp->ifindex, 0, 0, 0);

  rib_update ();
}

/* Add connected IPv6 route to the interface. */
void
connected_add_ipv6 (struct interface_FOO *ifp, struct in6_addr *addr,
		    u_char prefixlen, struct in6_addr *broad)
{
  struct prefix_ipv6 *p;
  struct connected *ifc;
  struct connected *current;

  /* Make connected structure. */
  ifc = connected_new ();
  ifc->ifp = ifp;

  /* Allocate new connected address. */
  p = prefix_ipv6_new ();
  p->family = AF_INET6;
  IPV6_ADDR_COPY (&p->prefix, addr);
  p->prefixlen = prefixlen;
  ifc->address = (struct prefix *) p;

  /* If there is broadcast or pointopoint address. */
  if (broad)
    {
      p = prefix_ipv6_new ();
      p->family = AF_INET6;
      IPV6_ADDR_COPY (&p->prefix, broad);
      ifc->destination = (struct prefix *) p;
    }

  current = connected_check_ipv6 (ifp, (struct prefix *) ifc->address);
  if (current)
    {
      connected_free (ifc);
      ifc = current;
    }
  else
    {
      listnode_add (ifp->connected, ifc);
    }

  /* Update interface address information to protocol daemon. */
  if (! CHECK_FLAG (ifc->conf, ZEBRA_IFC_REAL))
    {
      SET_FLAG (ifc->conf, ZEBRA_IFC_REAL);

      zebra_interface_address_add_update (ifp, ifc);

      if (if_is_up(ifp))
	connected_up_ipv6 (ifp, ifc);
    }
}

void
connected_down_ipv6 (struct interface_FOO *ifp, struct connected *ifc)
{
  struct prefix_ipv6 p;
  struct prefix_ipv6 *addr;
  struct prefix_ipv6 *dest;

  if (! CHECK_FLAG (ifc->conf, ZEBRA_IFC_REAL))
    return;

  addr = (struct prefix_ipv6 *) ifc->address;
  dest = (struct prefix_ipv6 *) ifc->destination;

  memset (&p, 0, sizeof (struct prefix_ipv6));
  p.family = AF_INET6;
  p.prefixlen = addr->prefixlen;

  if (if_is_pointopoint (ifp) && dest)
    {
      if (IN6_IS_ADDR_UNSPECIFIED (&dest->prefix))
	p.prefix = addr->prefix;
      else
	p.prefix = dest->prefix;
    }
  else
    p.prefix = addr->prefix;

  apply_mask_ipv6 (&p);

  if (IN6_IS_ADDR_UNSPECIFIED (&p.prefix))
    return;

  rib_delete_ipv6 (ZEBRA_ROUTE_CONNECT, 0, &p, NULL, ifp->ifindex, 0);

  rib_update ();
}

void
connected_delete_ipv6 (struct interface_FOO *ifp, struct in6_addr *address,
		       u_char prefixlen, struct in6_addr *broad)
{
  struct prefix_ipv6 p;
  struct connected *ifc;
  
  memset (&p, 0, sizeof (struct prefix_ipv6));
  p.family = AF_INET6;
  memcpy (&p.prefix, address, sizeof (struct in6_addr));
  p.prefixlen = prefixlen;

  ifc = connected_check_ipv6 (ifp, (struct prefix *) &p);
  if (! ifc)
    return;

  /* Update interface address information to protocol daemon. */
  if (CHECK_FLAG (ifc->conf, ZEBRA_IFC_REAL))
    {
      zebra_interface_address_delete_update (ifp, ifc);

      connected_down_ipv6 (ifp, ifc);

      UNSET_FLAG (ifc->conf, ZEBRA_IFC_REAL);
    }

  if (! CHECK_FLAG (ifc->conf, ZEBRA_IFC_CONFIGURED))
    {
      listnode_delete (ifp->connected, ifc);
      connected_free (ifc);
    }
}
#endif /* HAVE_IPV6 */
