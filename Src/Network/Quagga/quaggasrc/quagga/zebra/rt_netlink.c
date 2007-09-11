/* Kernel routing table updates using netlink over GNU/Linux system.
 * Copyright (C) 1997, 98, 99 Kunihiro Ishiguro
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

/* Hack for GNU libc version 2. */
#ifndef MSG_TRUNC
#define MSG_TRUNC      0x20
#endif /* MSG_TRUNC */

#include "linklist.h"
#include "if.h"
#include "log.h"
#include "prefix.h"
#include "connected.h"
#include "table.h"
#include "rib.h"
#include "thread.h"
#include "privs.h"

#include "rt_netlink.h"

#include "zebra/zserv.h"
#include "zebra/redistribute.h"
#include "zebra/interface.h"
#include "zebra/debug.h"

/* Socket interface to kernel */
// struct definition moved to header
struct nlsock netlink_zebra = { -1, 0, {0}, "n""etlink-listen"}; /* kernel messages, circumvent substitution of the 2nd n-e-t-l-i-n-k string */
struct nlsock netlink_cmd_zebra = { -1, 0, {0}, "netlink-cmd"}; /* command channel */
struct nlsock netlink_addr_zebra = { -1, 0, {0}, "netlink-addr"}; /* address channel */

struct message nlmsg_str[] = {
  {RTM_NEWROUTE, "RTM_NEWROUTE"},
  {RTM_DELROUTE, "RTM_DELROUTE"},
  {RTM_GETROUTE, "RTM_GETROUTE"},
  {RTM_NEWLINK,  "RTM_NEWLINK"},
  {RTM_DELLINK,  "RTM_DELLINK"},
  {RTM_GETLINK,  "RTM_GETLINK"},
  {RTM_NEWADDR,  "RTM_NEWADDR"},
  {RTM_DELADDR,  "RTM_DELADDR"},
  {RTM_GETADDR,  "RTM_GETADDR"},
  {0, NULL}
};

const char *nexthop_types_desc[] =  
{
  "none",
  "Directly connected",
  "Interface route",
  "IPv4 nexthop",
  "IPv4 nexthop with ifindex",
  "IPv4 nexthop with ifname",
  "IPv6 nexthop",
  "IPv6 nexthop with ifindex",
  "IPv6 nexthop with ifname",
  "Null0 nexthop",
};


extern struct zebra_t zebrad_zebra;

extern struct zebra_privs_t zserv_privs;

extern u_int32_t nl_rcvbufsize_zebra;

/* Make socket for Linux netlink interface. */
static int
netlink_socket (struct nlsock *nl, unsigned long groups)
{
  int ret;
  struct sockaddr_nl snl;
  int sock;
  int namelen;
  int save_errno;

  sock = socket (AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
  if (sock < 0)
    {
      zlog (NULL, LOG_ERR, "Can't open %s socket: %s", nl->name,
            safe_strerror (errno));
      return -1;
    }

  ret = fcntl (sock, F_SETFL, O_NONBLOCK);
  if (ret < 0)
    {
      zlog (NULL, LOG_ERR, "Can't set %s socket flags: %s", nl->name,
            safe_strerror (errno));
      close (sock);
      return -1;
    }

  /* Set receive buffer size if it's set from command line */
  if (nl_rcvbufsize)
    {
      u_int32_t oldsize, oldlen;
      u_int32_t newsize, newlen;

      oldlen = sizeof(oldsize);
      newlen = sizeof(newsize);

      ret = getsockopt(sock, SOL_SOCKET, SO_RCVBUF, &oldsize, &oldlen);
      if (ret < 0)
	{
	  zlog (NULL, LOG_ERR, "Can't get %s receive buffer size: %s", nl->name,
		safe_strerror (errno));
	  close (sock);
	  return -1;
	}

      ret = setsockopt(sock, SOL_SOCKET, SO_RCVBUF, &nl_rcvbufsize,
		       sizeof(nl_rcvbufsize));
      if (ret < 0)
	{
	  zlog (NULL, LOG_ERR, "Can't set %s receive buffer size: %s", nl->name,
		safe_strerror (errno));
	  close (sock);
	  return -1;
	}

      ret = getsockopt(sock, SOL_SOCKET, SO_RCVBUF, &newsize, &newlen);
      if (ret < 0)
	{
	  zlog (NULL, LOG_ERR, "Can't get %s receive buffer size: %s", nl->name,
		safe_strerror (errno));
	  close (sock);
	  return -1;
	}

      zlog (NULL, LOG_INFO,
	    "Setting netlink socket receive buffer size: %u -> %u",
	    oldsize, newsize);
    }

  memset (&snl, 0, sizeof snl);
  snl.nl_family = AF_NETLINK;
  snl.nl_groups = groups;

  /* Bind the socket to the netlink structure for anything. */
  if (zserv_privs.change (ZPRIVS_RAISE))
    {
      zlog (NULL, LOG_ERR, "Can't raise privileges");
      return -1;
    }

  ret = bind (sock, (struct sockaddr *) &snl, sizeof snl);
  save_errno = errno;
  if (zserv_privs.change (ZPRIVS_LOWER))
    zlog (NULL, LOG_ERR, "Can't lower privileges");

  if (ret < 0)
    {
      zlog (NULL, LOG_ERR, "Can't bind %s socket to group 0x%x: %s",
            nl->name, snl.nl_groups, safe_strerror (save_errno));
      close (sock);
      return -1;
    }

  /* multiple netlink sockets will have different nl_pid */
  namelen = sizeof snl;
  ret = getsockname (sock, (struct sockaddr *) &snl, (socklen_t *) &namelen);
  if (ret < 0 || namelen != sizeof snl)
    {
      zlog (NULL, LOG_ERR, "Can't get %s socket name: %s", nl->name,
            safe_strerror (errno));
      close (sock);
      return -1;
    }

  nl->snl = snl;
  nl->sock = sock;
  return ret;
}

int
set_netlink_blocking (struct nlsock *nl, int *flags)
{

  /* Change socket flags for blocking I/O.  */
  if ((*flags = fcntl (nl->sock, F_GETFL, 0)) < 0)
    {
      zlog (NULL, LOG_ERR, "%s:%i F_GETFL error: %s",
            __FUNCTION__, __LINE__, safe_strerror (errno));
      return -1;
    }
  *flags &= ~O_NONBLOCK;
  if (fcntl (nl->sock, F_SETFL, *flags) < 0)
    {
      zlog (NULL, LOG_ERR, "%s:%i F_SETFL error: %s",
            __FUNCTION__, __LINE__, safe_strerror (errno));
      return -1;
    }
  return 0;
}

int
set_netlink_nonblocking (struct nlsock *nl, int *flags)
{
  /* Restore socket flags for nonblocking I/O */
  *flags |= O_NONBLOCK;
  if (fcntl (nl->sock, F_SETFL, *flags) < 0)
    {
      zlog (NULL, LOG_ERR, "%s:%i F_SETFL error: %s",
            __FUNCTION__, __LINE__, safe_strerror (errno));
      return -1;
    }
  return 0;
}

/* Get type specified information from netlink. */
static int
netlink_request (int family, int type, struct nlsock *nl)
{
  int ret;
  struct sockaddr_nl snl;
  int save_errno;

  struct
  {
    struct nlmsghdr nlh;
    struct rtgenmsg g;
  } req;


  /* Check netlink socket. */
  if (nl->sock < 0)
    {
      zlog (NULL, LOG_ERR, "%s socket isn't active.", nl->name);
      return -1;
    }

  memset (&snl, 0, sizeof snl);
  snl.nl_family = AF_NETLINK;

  req.nlh.nlmsg_len = sizeof req;
  req.nlh.nlmsg_type = type;
  req.nlh.nlmsg_flags = NLM_F_ROOT | NLM_F_MATCH | NLM_F_REQUEST;
  req.nlh.nlmsg_pid = 0;
  req.nlh.nlmsg_seq = ++nl->seq;
  req.g.rtgen_family = family;

  /* linux appears to check capabilities on every message 
   * have to raise caps for every message sent
   */
  if (zserv_privs.change (ZPRIVS_RAISE))
    {
      zlog (NULL, LOG_ERR, "Can't raise privileges");
      return -1;
    }

  ret = sendto (nl->sock, (void *) &req, sizeof req, 0,
                (struct sockaddr *) &snl, sizeof snl);
  save_errno = errno;

  if (zserv_privs.change (ZPRIVS_LOWER))
    zlog (NULL, LOG_ERR, "Can't lower privileges");

  if (ret < 0)
    {
      zlog (NULL, LOG_ERR, "%s sendto failed: %s", nl->name,
            safe_strerror (save_errno));
      return -1;
    }

  return 0;
}

/* Receive message from netlink interface and pass those information
   to the given function. */
static int
netlink_parse_info (int (*filter) (struct sockaddr_nl *, struct nlmsghdr *),
                    struct nlsock *nl)
{
  int status;
  int ret = 0;
  int error;

  while (1)
    {
      char buf[4096];
      struct iovec iov = { buf, sizeof buf };
      struct sockaddr_nl snl;
      struct msghdr msg = { (void *) &snl, sizeof snl, &iov, 1, NULL, 0, 0 };
      struct nlmsghdr *h;
      int save_errno;

      if (zserv_privs.change (ZPRIVS_RAISE))
        zlog (NULL, LOG_ERR, "Can't raise privileges");

      status = recvmsg (nl->sock, &msg, 0);
      save_errno = errno;

      if (zserv_privs.change (ZPRIVS_LOWER))
        zlog (NULL, LOG_ERR, "Can't lower privileges");

      if (status < 0)
        {
          if (save_errno == EINTR)
            continue;
          if (save_errno == EWOULDBLOCK || save_errno == EAGAIN)
            break;
          zlog (NULL, LOG_ERR, "%s recvmsg overrun: %s",
	  	nl->name, safe_strerror(save_errno));
          continue;
        }

      if (status == 0)
        {
          zlog (NULL, LOG_ERR, "%s EOF", nl->name);
          return -1;
        }

      if (msg.msg_namelen != sizeof snl)
        {
          zlog (NULL, LOG_ERR, "%s sender address length error: length %d",
                nl->name, msg.msg_namelen);
          return -1;
        }
      
      /* JF: Ignore messages that aren't from the kernel */
      if ( snl.nl_pid != 0 )
        {
          zlog ( NULL, LOG_ERR, "Ignoring message from pid %u", snl.nl_pid );
          continue;
        }

      for (h = (struct nlmsghdr *) buf; NLMSG_OK (h, status);
           h = NLMSG_NEXT (h, status))
        {
          /* Finish of reading. */
          if (h->nlmsg_type == NLMSG_DONE)
            return ret;

          /* Error handling. */
          if (h->nlmsg_type == NLMSG_ERROR)
            {
              struct nlmsgerr *err = (struct nlmsgerr *) NLMSG_DATA (h);

              /* If the error field is zero, then this is an ACK */
              if (err->error == 0)
                {
                  if (IS_ZEBRA_DEBUG_KERNEL)
                    {
                      zlog_debug ("%s: %s ACK: type=%s(%u), seq=%u, pid=%u",
                                 __FUNCTION__, nl->name,
                                 lookup (nlmsg_str, err->msg.nlmsg_type),
                                 err->msg.nlmsg_type, err->msg.nlmsg_seq,
                                 err->msg.nlmsg_pid);
                    }

                  /* return if not a multipart message, otherwise continue */
                  if (!(h->nlmsg_flags & NLM_F_MULTI))
                    {
                      return 0;
                    }
                  continue;
                }

              if (h->nlmsg_len < NLMSG_LENGTH (sizeof (struct nlmsgerr)))
                {
                  zlog (NULL, LOG_ERR, "%s error: message truncated",
                        nl->name);
                  return -1;
                }

              /* Deal with Error Noise  - MAG */
              {
                int loglvl = LOG_ERR;
                int errnum = err->error;
                int msg_type = err->msg.nlmsg_type;

                if (nl == &netlink_cmd
                    && (-errnum == ENODEV || -errnum == ESRCH)
                    && (msg_type == RTM_NEWROUTE || msg_type == RTM_DELROUTE))
                  loglvl = LOG_DEBUG;

                zlog (NULL, loglvl, "%s error: %s, type=%s(%u), "
                      "seq=%u, pid=%u",
                      nl->name, safe_strerror (-errnum),
                      lookup (nlmsg_str, msg_type),
                      msg_type, err->msg.nlmsg_seq, err->msg.nlmsg_pid);
              }
              /*
                 ret = -1;
                 continue;
               */
              return -1;
            }

          /* OK we got netlink message. */
          if (IS_ZEBRA_DEBUG_KERNEL)
            zlog_debug ("netlink_parse_info: %s type %s(%u), seq=%u, pid=%u",
                       nl->name,
                       lookup (nlmsg_str, h->nlmsg_type), h->nlmsg_type,
                       h->nlmsg_seq, h->nlmsg_pid);

          /* skip unsolicited messages originating from command socket */
          if (nl != &netlink_cmd && h->nlmsg_pid == netlink_cmd.snl.nl_pid)
            {
              if (IS_ZEBRA_DEBUG_KERNEL)
                zlog_debug ("netlink_parse_info: %s packet comes from %s",
                            netlink_cmd.name, nl->name);
              continue;
            }

          error = (*filter) (&snl, h);
          if (error < 0)
            {
              zlog (NULL, LOG_ERR, "%s filter function error", nl->name);
              ret = error;
            }
        }

      /* After error care. */
      if (msg.msg_flags & MSG_TRUNC)
        {
          zlog (NULL, LOG_ERR, "%s error: message truncated", nl->name);
          continue;
        }
      if (status)
        {
          zlog (NULL, LOG_ERR, "%s error: data remnant size %d", nl->name,
                status);
          return -1;
        }
    }
  return ret;
}

/* Utility function for parse rtattr. */
void
netlink_parse_rtattr (struct rtattr **tb, int max, struct rtattr *rta,
                      int len)
{
  while (RTA_OK (rta, len))
    {
      if (rta->rta_type <= max)
        tb[rta->rta_type] = rta;
      rta = RTA_NEXT (rta, len);
    }
}

/* Called from interface_lookup_netlink().  This function is only used
   during bootstrap. */
int
netlink_interface (struct sockaddr_nl *snl, struct nlmsghdr *h)
{
  int len;
  struct ifinfomsg *ifi;
  struct rtattr *tb[IFLA_MAX + 1];
  struct interface_FOO *ifp;
  char *name;
  int i;

  ifi = NLMSG_DATA (h);

  if (h->nlmsg_type != RTM_NEWLINK)
    return 0;

  len = h->nlmsg_len - NLMSG_LENGTH (sizeof (struct ifinfomsg));
  if (len < 0)
    return -1;

  /* Looking up interface name. */
  memset (tb, 0, sizeof tb);
  netlink_parse_rtattr (tb, IFLA_MAX, IFLA_RTA (ifi), len);
  if (tb[IFLA_IFNAME] == NULL)
    return -1;
  name = (char *) RTA_DATA (tb[IFLA_IFNAME]);

  /* Add interface. */
  ifp = if_get_by_name (name);

  ifp->ifindex = ifi->ifi_index;
  ifp->flags = ifi->ifi_flags & 0x0000fffff;
  ifp->mtu6 = ifp->mtu = *(int *) RTA_DATA (tb[IFLA_MTU]);
  ifp->metric = 1;

  /* Hardware type and address. */
  ifp->hw_type = ifi->ifi_type;

  if (tb[IFLA_ADDRESS])
    {
      int hw_addr_len;

      hw_addr_len = RTA_PAYLOAD (tb[IFLA_ADDRESS]);

      if (hw_addr_len > INTERFACE_HWADDR_MAX)
        zlog_warn ("Hardware address is too large: %d", hw_addr_len);
      else
        {
          ifp->hw_addr_len = hw_addr_len;
          memcpy (ifp->hw_addr, RTA_DATA (tb[IFLA_ADDRESS]), hw_addr_len);

          for (i = 0; i < hw_addr_len; i++)
            if (ifp->hw_addr[i] != 0)
              break;

          if (i == hw_addr_len)
            ifp->hw_addr_len = 0;
          else
            ifp->hw_addr_len = hw_addr_len;
        }
    }

  if_add_update (ifp);

  return 0;
}

/* Lookup interface IPv4/IPv6 address. */
int
netlink_interface_addr (struct sockaddr_nl *snl, struct nlmsghdr *h)
{
  int len;
  struct ifaddrmsg *ifa;
  struct rtattr *tb[IFA_MAX + 1];
  struct interface_FOO *ifp;
  void *addr = NULL;
  void *broad = NULL;
  u_char flags = 0;
  char *label = NULL;

  ifa = NLMSG_DATA (h);

  if (ifa->ifa_family != AF_INET
#ifdef HAVE_IPV6
      && ifa->ifa_family != AF_INET6
#endif /* HAVE_IPV6 */
    )
    return 0;

  if (h->nlmsg_type != RTM_NEWADDR && h->nlmsg_type != RTM_DELADDR)
    return 0;

  len = h->nlmsg_len - NLMSG_LENGTH (sizeof (struct ifaddrmsg));
  if (len < 0)
    return -1;

  memset (tb, 0, sizeof tb);
  netlink_parse_rtattr (tb, IFA_MAX, IFA_RTA (ifa), len);

  ifp = if_lookup_by_index (ifa->ifa_index);
  if (ifp == NULL)
    {
      zlog_err ("netlink_interface_addr can't find interface by index %d",
                ifa->ifa_index);
      return -1;
    }

  if (IS_ZEBRA_DEBUG_KERNEL)    /* remove this line to see initial ifcfg */
    {
      char buf[BUFSIZ];
      zlog_debug ("netlink_interface_addr %s %s:",
                 lookup (nlmsg_str, h->nlmsg_type), ifp->name);
      if (tb[IFA_LOCAL])
        zlog_debug ("  IFA_LOCAL     %s/%d",
		    inet_ntop (ifa->ifa_family, RTA_DATA (tb[IFA_LOCAL]),
			       buf, BUFSIZ), ifa->ifa_prefixlen);
      if (tb[IFA_ADDRESS])
        zlog_debug ("  IFA_ADDRESS   %s/%d",
		    inet_ntop (ifa->ifa_family, RTA_DATA (tb[IFA_ADDRESS]),
                               buf, BUFSIZ), ifa->ifa_prefixlen);
      if (tb[IFA_BROADCAST])
        zlog_debug ("  IFA_BROADCAST %s/%d",
		    inet_ntop (ifa->ifa_family, RTA_DATA (tb[IFA_BROADCAST]),
			       buf, BUFSIZ), ifa->ifa_prefixlen);
      if (tb[IFA_LABEL] && strcmp (ifp->name, RTA_DATA (tb[IFA_LABEL])))
        zlog_debug ("  IFA_LABEL     %s", (char *)RTA_DATA (tb[IFA_LABEL]));
    }
  
  if (tb[IFA_ADDRESS] == NULL)
    tb[IFA_ADDRESS] = tb[IFA_LOCAL];
  
  if (ifp->flags & IFF_POINTOPOINT)
    {
      if (tb[IFA_LOCAL])
        {
          addr = RTA_DATA (tb[IFA_LOCAL]);
          if (tb[IFA_ADDRESS] &&
	      memcmp(RTA_DATA(tb[IFA_ADDRESS]),RTA_DATA(tb[IFA_LOCAL]),4))
	    /* if IFA_ADDRESS != IFA_LOCAL, then it's the peer address */
            broad = RTA_DATA (tb[IFA_ADDRESS]);
          else
            broad = NULL;
        }
      else
        {
          if (tb[IFA_ADDRESS])
            addr = RTA_DATA (tb[IFA_ADDRESS]);
          else
            addr = NULL;
        }
    }
  else
    {
      if (tb[IFA_ADDRESS])
        addr = RTA_DATA (tb[IFA_ADDRESS]);
      else
        addr = NULL;
      
      if (tb[IFA_BROADCAST])
        broad = RTA_DATA(tb[IFA_BROADCAST]);
      else
        broad = NULL;
    }

  /* Flags. */
  if (ifa->ifa_flags & IFA_F_SECONDARY)
    SET_FLAG (flags, ZEBRA_IFA_SECONDARY);

  /* Label */
  if (tb[IFA_LABEL])
    label = (char *) RTA_DATA (tb[IFA_LABEL]);

  if (ifp && label && strcmp (ifp->name, label) == 0)
    label = NULL;

  /* Register interface address to the interface. */
  if (ifa->ifa_family == AF_INET)
    {
      if (h->nlmsg_type == RTM_NEWADDR)
        connected_add_ipv4 (ifp, flags,
                            (struct in_addr *) addr, ifa->ifa_prefixlen,
                            (struct in_addr *) broad, label);
      else
        connected_delete_ipv4 (ifp, flags,
                               (struct in_addr *) addr, ifa->ifa_prefixlen,
                               (struct in_addr *) broad, label);
    }
#ifdef HAVE_IPV6
  if (ifa->ifa_family == AF_INET6)
    {
      if (h->nlmsg_type == RTM_NEWADDR)
        connected_add_ipv6 (ifp,
                            (struct in6_addr *) addr, ifa->ifa_prefixlen,
                            (struct in6_addr *) broad);
      else
        connected_delete_ipv6 (ifp,
                               (struct in6_addr *) addr, ifa->ifa_prefixlen,
                               (struct in6_addr *) broad);
    }
#endif /* HAVE_IPV6 */

  return 0;
}

/* Looking up routing table by netlink interface. */
int
netlink_routing_table (struct sockaddr_nl *snl, struct nlmsghdr *h)
{
  int len;
  struct rtmsg *rtm;
  struct rtattr *tb[RTA_MAX + 1];
  u_char flags = 0;

  char anyaddr[16] = { 0 };

  int index;
  int table;
  int metric;

  void *dest;
  void *gate;

  rtm = NLMSG_DATA (h);

  if (h->nlmsg_type != RTM_NEWROUTE)
    return 0;
  if (rtm->rtm_type != RTN_UNICAST)
    return 0;

  table = rtm->rtm_table;
#if 0                           /* we weed them out later in rib_weed_tables () */
  if (table != RT_TABLE_MAIN && table != zebrad.rtm_table_default)
    return 0;
#endif

  len = h->nlmsg_len - NLMSG_LENGTH (sizeof (struct rtmsg));
  if (len < 0)
    return -1;

  memset (tb, 0, sizeof tb);
  netlink_parse_rtattr (tb, RTA_MAX, RTM_RTA (rtm), len);

  if (rtm->rtm_flags & RTM_F_CLONED)
    return 0;
  if (rtm->rtm_protocol == RTPROT_REDIRECT)
    return 0;
  if (rtm->rtm_protocol == RTPROT_KERNEL)
    return 0;

  if (rtm->rtm_src_len != 0)
    return 0;

  /* Route which inserted by Zebra. */
  if (rtm->rtm_protocol == RTPROT_ZEBRA)
    flags |= ZEBRA_FLAG_SELFROUTE;

  index = 0;
  metric = 0;
  dest = NULL;
  gate = NULL;

  if (tb[RTA_OIF])
    index = *(int *) RTA_DATA (tb[RTA_OIF]);

  if (tb[RTA_DST])
    dest = RTA_DATA (tb[RTA_DST]);
  else
    dest = anyaddr;

  /* Multipath treatment is needed. */
  if (tb[RTA_GATEWAY])
    gate = RTA_DATA (tb[RTA_GATEWAY]);

  if (tb[RTA_PRIORITY])
    metric = *(int *) RTA_DATA(tb[RTA_PRIORITY]);

  if (rtm->rtm_family == AF_INET)
    {
      struct prefix_ipv4 p;
      p.family = AF_INET;
      memcpy (&p.prefix, dest, 4);
      p.prefixlen = rtm->rtm_dst_len;

      rib_add_ipv4 (ZEBRA_ROUTE_KERNEL, flags, &p, gate, index, table, metric, 0);
    }
#ifdef HAVE_IPV6
  if (rtm->rtm_family == AF_INET6)
    {
      struct prefix_ipv6 p;
      p.family = AF_INET6;
      memcpy (&p.prefix, dest, 16);
      p.prefixlen = rtm->rtm_dst_len;

      rib_add_ipv6 (ZEBRA_ROUTE_KERNEL, flags, &p, gate, index, table,
		    metric, 0);
    }
#endif /* HAVE_IPV6 */

  return 0;
}

struct message rtproto_str[] = {
  {RTPROT_REDIRECT, "redirect"},
  {RTPROT_KERNEL,   "kernel"},
  {RTPROT_BOOT,     "boot"},
  {RTPROT_STATIC,   "static"},
  {RTPROT_GATED,    "GateD"},
  {RTPROT_RA,       "router advertisement"},
  {RTPROT_MRT,      "MRT"},
  {RTPROT_ZEBRA,    "Zebra"},
#ifdef RTPROT_BIRD
  {RTPROT_BIRD,     "BIRD"},
#endif /* RTPROT_BIRD */
  {0,               NULL}
};

/* Routing information change from the kernel. */
int
netlink_route_change (struct sockaddr_nl *snl, struct nlmsghdr *h)
{
  int len;
  struct rtmsg *rtm;
  struct rtattr *tb[RTA_MAX + 1];

  char anyaddr[16] = { 0 };

  int index;
  int table;
  void *dest;
  void *gate;

  rtm = NLMSG_DATA (h);

  if (!(h->nlmsg_type == RTM_NEWROUTE || h->nlmsg_type == RTM_DELROUTE))
    {
      /* If this is not route add/delete message print warning. */
      zlog_warn ("Kernel message: %d\n", h->nlmsg_type);
      return 0;
    }

  /* Connected route. */
  if (IS_ZEBRA_DEBUG_KERNEL)
    zlog_debug ("%s %s %s proto %s",
               h->nlmsg_type ==
               RTM_NEWROUTE ? "RTM_NEWROUTE" : "RTM_DELROUTE",
               rtm->rtm_family == AF_INET ? "ipv4" : "ipv6",
               rtm->rtm_type == RTN_UNICAST ? "unicast" : "multicast",
               lookup (rtproto_str, rtm->rtm_protocol));

  if (rtm->rtm_type != RTN_UNICAST)
    {
      return 0;
    }

  table = rtm->rtm_table;
  if (table != RT_TABLE_MAIN && table != zebrad.rtm_table_default)
    {
      return 0;
    }

  len = h->nlmsg_len - NLMSG_LENGTH (sizeof (struct rtmsg));
  if (len < 0)
    return -1;

  memset (tb, 0, sizeof tb);
  netlink_parse_rtattr (tb, RTA_MAX, RTM_RTA (rtm), len);

  if (rtm->rtm_flags & RTM_F_CLONED)
    return 0;
  if (rtm->rtm_protocol == RTPROT_REDIRECT)
    return 0;
  if (rtm->rtm_protocol == RTPROT_KERNEL)
    return 0;

  if (rtm->rtm_protocol == RTPROT_ZEBRA && h->nlmsg_type == RTM_NEWROUTE)
    return 0;

  if (rtm->rtm_src_len != 0)
    {
      zlog_warn ("netlink_route_change(): no src len");
      return 0;
    }

  index = 0;
  dest = NULL;
  gate = NULL;

  if (tb[RTA_OIF])
    index = *(int *) RTA_DATA (tb[RTA_OIF]);

  if (tb[RTA_DST])
    dest = RTA_DATA (tb[RTA_DST]);
  else
    dest = anyaddr;

  if (tb[RTA_GATEWAY])
    gate = RTA_DATA (tb[RTA_GATEWAY]);

  if (rtm->rtm_family == AF_INET)
    {
      struct prefix_ipv4 p;
      p.family = AF_INET;
      memcpy (&p.prefix, dest, 4);
      p.prefixlen = rtm->rtm_dst_len;

      if (IS_ZEBRA_DEBUG_KERNEL)
        {
          if (h->nlmsg_type == RTM_NEWROUTE)
            zlog_debug ("RTM_NEWROUTE %s/%d",
                       inet_ntoa (p.prefix), p.prefixlen);
          else
            zlog_debug ("RTM_DELROUTE %s/%d",
                       inet_ntoa (p.prefix), p.prefixlen);
        }

      if (h->nlmsg_type == RTM_NEWROUTE)
        rib_add_ipv4 (ZEBRA_ROUTE_KERNEL, 0, &p, gate, index, table, 0, 0);
      else
        rib_delete_ipv4 (ZEBRA_ROUTE_KERNEL, 0, &p, gate, index, table);
    }

#ifdef HAVE_IPV6
  if (rtm->rtm_family == AF_INET6)
    {
      struct prefix_ipv6 p;
      char buf[BUFSIZ];

      p.family = AF_INET6;
      memcpy (&p.prefix, dest, 16);
      p.prefixlen = rtm->rtm_dst_len;

      if (IS_ZEBRA_DEBUG_KERNEL)
        {
          if (h->nlmsg_type == RTM_NEWROUTE)
            zlog_debug ("RTM_NEWROUTE %s/%d",
                       inet_ntop (AF_INET6, &p.prefix, buf, BUFSIZ),
                       p.prefixlen);
          else
            zlog_debug ("RTM_DELROUTE %s/%d",
                       inet_ntop (AF_INET6, &p.prefix, buf, BUFSIZ),
                       p.prefixlen);
        }

      if (h->nlmsg_type == RTM_NEWROUTE)
        rib_add_ipv6 (ZEBRA_ROUTE_KERNEL, 0, &p, gate, index, 0, 0, 0);
      else
        rib_delete_ipv6 (ZEBRA_ROUTE_KERNEL, 0, &p, gate, index, 0);
    }
#endif /* HAVE_IPV6 */

  return 0;
}

int
netlink_link_change (struct sockaddr_nl *snl, struct nlmsghdr *h)
{
  int len;
  struct ifinfomsg *ifi;
  struct rtattr *tb[IFLA_MAX + 1];
  struct interface_FOO *ifp;
  char *name;

  ifi = NLMSG_DATA (h);

  if (!(h->nlmsg_type == RTM_NEWLINK || h->nlmsg_type == RTM_DELLINK))
    {
      /* If this is not link add/delete message so print warning. */
      zlog_warn ("netlink_link_change: wrong kernel message %d\n",
                 h->nlmsg_type);
      return 0;
    }

  len = h->nlmsg_len - NLMSG_LENGTH (sizeof (struct ifinfomsg));
  if (len < 0)
    return -1;

  /* Looking up interface name. */
  memset (tb, 0, sizeof tb);
  netlink_parse_rtattr (tb, IFLA_MAX, IFLA_RTA (ifi), len);
  if (tb[IFLA_IFNAME] == NULL)
    return -1;
  name = (char *) RTA_DATA (tb[IFLA_IFNAME]);

  /* Add interface. */
  if (h->nlmsg_type == RTM_NEWLINK)
    {
      ifp = if_lookup_by_name (name);

      if (ifp == NULL || !CHECK_FLAG (ifp->status, ZEBRA_INTERFACE_ACTIVE))
        {
          if (ifp == NULL)
            ifp = if_get_by_name (name);

          ifp->ifindex = ifi->ifi_index;
          ifp->flags = ifi->ifi_flags & 0x0000fffff;
          ifp->mtu6 = ifp->mtu = *(int *) RTA_DATA (tb[IFLA_MTU]);
          ifp->metric = 1;

          /* If new link is added. */
          if_add_update (ifp);
        }
      else
        {
          /* Interface status change. */
          ifp->ifindex = ifi->ifi_index;
          ifp->mtu6 = ifp->mtu = *(int *) RTA_DATA (tb[IFLA_MTU]);
          ifp->metric = 1;

          if (if_is_operative (ifp))
            {
              ifp->flags = ifi->ifi_flags & 0x0000fffff;
              if (!if_is_operative (ifp))
                if_down (ifp);
	      else
		/* Must notify client daemons of new interface status. */
	        zebra_interface_up_update (ifp);
            }
          else
            {
              ifp->flags = ifi->ifi_flags & 0x0000fffff;
              if (if_is_operative (ifp))
                if_up (ifp);
            }
        }
    }
  else
    {
      /* RTM_DELLINK. */
      ifp = if_lookup_by_name (name);

      if (ifp == NULL)
        {
          zlog (NULL, LOG_WARNING, "interface %s is deleted but can't find",
                name);
          return 0;
        }

      if_delete_update (ifp);
    }

  return 0;
}

int
netlink_information_fetch (struct sockaddr_nl *snl, struct nlmsghdr *h)
{
  switch (h->nlmsg_type)
    {
    case RTM_NEWROUTE:
      return netlink_route_change (snl, h);
      break;
    case RTM_DELROUTE:
      return netlink_route_change (snl, h);
      break;
    case RTM_NEWLINK:
      return netlink_link_change (snl, h);
      break;
    case RTM_DELLINK:
      return netlink_link_change (snl, h);
      break;
    case RTM_NEWADDR:
      return netlink_interface_addr (snl, h);
      break;
    case RTM_DELADDR:
      return netlink_interface_addr (snl, h);
      break;
    default:
      zlog_warn ("Unknown netlink nlmsg_type %d\n", h->nlmsg_type);
      break;
    }
  return 0;
}

/* Interface lookup by netlink socket. */
int
interface_lookup_netlink ()
{
  int ret;
  int flags;
  int snb_ret;

  /* 
   * Change netlink socket flags to blocking to ensure we get 
   * a reply via nelink_parse_info
   */
  snb_ret = set_netlink_blocking (&netlink_cmd, &flags);
  if (snb_ret < 0)
    zlog (NULL, LOG_WARNING,
          "%s:%i Warning: Could not set netlink socket to blocking.",
          __FUNCTION__, __LINE__);

  /* Get interface information. */
  ret = netlink_request (AF_PACKET, RTM_GETLINK, &netlink_cmd);
  if (ret < 0)
    return ret;
  ret = netlink_parse_info (netlink_interface, &netlink_cmd);
  if (ret < 0)
    return ret;

  /* Get IPv4 address of the interfaces. */
  ret = netlink_request (AF_INET, RTM_GETADDR, &netlink_cmd);
  if (ret < 0)
    return ret;
  ret = netlink_parse_info (netlink_interface_addr, &netlink_cmd);
  if (ret < 0)
    return ret;

#ifdef HAVE_IPV6
  /* Get IPv6 address of the interfaces. */
  ret = netlink_request (AF_INET6, RTM_GETADDR, &netlink_cmd);
  if (ret < 0)
    return ret;
  ret = netlink_parse_info (netlink_interface_addr, &netlink_cmd);
  if (ret < 0)
    return ret;
#endif /* HAVE_IPV6 */

  /* restore socket flags */
  if (snb_ret == 0)
    set_netlink_nonblocking (&netlink_cmd, &flags);
  return 0;
}

/* Routing table read function using netlink interface.  Only called
   bootstrap time. */
int
netlink_route_read ()
{
  int ret;
  int flags;
  int snb_ret;

  /* 
   * Change netlink socket flags to blocking to ensure we get 
   * a reply via nelink_parse_info
   */
  snb_ret = set_netlink_blocking (&netlink_cmd, &flags);
  if (snb_ret < 0)
    zlog (NULL, LOG_WARNING,
          "%s:%i Warning: Could not set netlink socket to blocking.",
          __FUNCTION__, __LINE__);

  /* Get IPv4 routing table. */
  ret = netlink_request (AF_INET, RTM_GETROUTE, &netlink_cmd);
  if (ret < 0)
    return ret;
  ret = netlink_parse_info (netlink_routing_table, &netlink_cmd);
  if (ret < 0)
    return ret;

#ifdef HAVE_IPV6
  /* Get IPv6 routing table. */
  ret = netlink_request (AF_INET6, RTM_GETROUTE, &netlink_cmd);
  if (ret < 0)
    return ret;
  ret = netlink_parse_info (netlink_routing_table, &netlink_cmd);
  if (ret < 0)
    return ret;
#endif /* HAVE_IPV6 */

  /* restore flags */
  if (snb_ret == 0)
    set_netlink_nonblocking (&netlink_cmd, &flags);
  return 0;
}

/* Utility function  comes from iproute2. 
   Authors:	Alexey Kuznetsov, <kuznet@ms2.inr.ac.ru> */
int
addattr_l (struct nlmsghdr *n, int maxlen, int type, void *data, int alen)
{
  int len;
  struct rtattr *rta;

  len = RTA_LENGTH (alen);

  if (NLMSG_ALIGN (n->nlmsg_len) + len > maxlen)
    return -1;

  rta = (struct rtattr *) (((char *) n) + NLMSG_ALIGN (n->nlmsg_len));
  rta->rta_type = type;
  rta->rta_len = len;
  memcpy (RTA_DATA (rta), data, alen);
  n->nlmsg_len = NLMSG_ALIGN (n->nlmsg_len) + len;

  return 0;
}

int
rta_addattr_l (struct rtattr *rta, int maxlen, int type, void *data, int alen)
{
  int len;
  struct rtattr *subrta;

  len = RTA_LENGTH (alen);

  if (RTA_ALIGN (rta->rta_len) + len > maxlen)
    return -1;

  subrta = (struct rtattr *) (((char *) rta) + RTA_ALIGN (rta->rta_len));
  subrta->rta_type = type;
  subrta->rta_len = len;
  memcpy (RTA_DATA (subrta), data, alen);
  rta->rta_len = NLMSG_ALIGN (rta->rta_len) + len;

  return 0;
}

/* Utility function comes from iproute2. 
   Authors:	Alexey Kuznetsov, <kuznet@ms2.inr.ac.ru> */
int
addattr32 (struct nlmsghdr *n, int maxlen, int type, int data)
{
  int len;
  struct rtattr *rta;

  len = RTA_LENGTH (4);

  if (NLMSG_ALIGN (n->nlmsg_len) + len > maxlen)
    return -1;

  rta = (struct rtattr *) (((char *) n) + NLMSG_ALIGN (n->nlmsg_len));
  rta->rta_type = type;
  rta->rta_len = len;
  memcpy (RTA_DATA (rta), &data, 4);
  n->nlmsg_len = NLMSG_ALIGN (n->nlmsg_len) + len;

  return 0;
}

static int
netlink_talk_filter (struct sockaddr_nl *snl, struct nlmsghdr *h)
{
  zlog_warn ("netlink_talk: ignoring message type 0x%04x", h->nlmsg_type);
  return 0;
}

/* sendmsg() to netlink socket then recvmsg(). */
int
netlink_talk (struct nlmsghdr *n, struct nlsock *nl)
{
  int status;
  struct sockaddr_nl snl;
  struct iovec iov = { (void *) n, n->nlmsg_len };
  struct msghdr msg = { (void *) &snl, sizeof snl, &iov, 1, NULL, 0, 0 };
  int flags = 0;
  int snb_ret;
  int save_errno;

  memset (&snl, 0, sizeof snl);
  snl.nl_family = AF_NETLINK;

  n->nlmsg_seq = ++nl->seq;

  /* Request an acknowledgement by setting NLM_F_ACK */
  n->nlmsg_flags |= NLM_F_ACK;

  if (IS_ZEBRA_DEBUG_KERNEL)
    zlog_debug ("netlink_talk: %s type %s(%u), seq=%u", nl->name,
               lookup (nlmsg_str, n->nlmsg_type), n->nlmsg_type,
               n->nlmsg_seq);

  /* Send message to netlink interface. */
  if (zserv_privs.change (ZPRIVS_RAISE))
    zlog (NULL, LOG_ERR, "Can't raise privileges");
  status = sendmsg (nl->sock, &msg, 0);
  save_errno = errno;
  if (zserv_privs.change (ZPRIVS_LOWER))
    zlog (NULL, LOG_ERR, "Can't lower privileges");

  if (status < 0)
    {
      zlog (NULL, LOG_ERR, "netlink_talk sendmsg() error: %s",
            safe_strerror (save_errno));
      return -1;
    }

  /* 
   * Change socket flags for blocking I/O. 
   * This ensures we wait for a reply in netlink_parse_info().
   */
  snb_ret = set_netlink_blocking (nl, &flags);
  if (snb_ret < 0)
    zlog (NULL, LOG_WARNING,
          "%s:%i Warning: Could not set netlink socket to blocking.",
          __FUNCTION__, __LINE__);

  /* 
   * Get reply from netlink socket. 
   * The reply should either be an acknowlegement or an error.
   */
  status = netlink_parse_info (netlink_talk_filter, nl);

  /* Restore socket flags for nonblocking I/O */
  if (snb_ret == 0)
    set_netlink_nonblocking (nl, &flags);

  return status;
}

/* Routing table change via netlink interface. */
int
netlink_route (int cmd, int family, void *dest, int length, void *gate,
               int index, int zebra_flags, int table)
{
  int ret;
  int bytelen;
  struct sockaddr_nl snl;
  int discard;

  struct
  {
    struct nlmsghdr n;
    struct rtmsg r;
    char buf[1024];
  } req;

  memset (&req, 0, sizeof req);

  bytelen = (family == AF_INET ? 4 : 16);

  req.n.nlmsg_len = NLMSG_LENGTH (sizeof (struct rtmsg));
  req.n.nlmsg_flags = NLM_F_CREATE | NLM_F_REQUEST;
  req.n.nlmsg_type = cmd;
  req.r.rtm_family = family;
  req.r.rtm_table = table;
  req.r.rtm_dst_len = length;

  if ((zebra_flags & ZEBRA_FLAG_BLACKHOLE)
      || (zebra_flags & ZEBRA_FLAG_REJECT))
    discard = 1;
  else
    discard = 0;

  if (cmd == RTM_NEWROUTE)
    {
      req.r.rtm_protocol = RTPROT_ZEBRA;
      req.r.rtm_scope = RT_SCOPE_UNIVERSE;

      if (discard)
        {
          if (zebra_flags & ZEBRA_FLAG_BLACKHOLE)
            req.r.rtm_type = RTN_BLACKHOLE;
          else if (zebra_flags & ZEBRA_FLAG_REJECT)
            req.r.rtm_type = RTN_UNREACHABLE;
          else
            assert (RTN_BLACKHOLE != RTN_UNREACHABLE);  /* false */
        }
      else
        req.r.rtm_type = RTN_UNICAST;
    }

  if (dest)
    addattr_l (&req.n, sizeof req, RTA_DST, dest, bytelen);

  if (!discard)
    {
      if (gate)
        addattr_l (&req.n, sizeof req, RTA_GATEWAY, gate, bytelen);
      if (index > 0)
        addattr32 (&req.n, sizeof req, RTA_OIF, index);
    }

  /* Destination netlink address. */
  memset (&snl, 0, sizeof snl);
  snl.nl_family = AF_NETLINK;

  /* Talk to netlink socket. */
  ret = netlink_talk (&req.n, &netlink_cmd);
  if (ret < 0)
    return -1;

  return 0;
}

/* Routing table change via netlink interface. */
int
netlink_route_multipath (int cmd, struct prefix *p, struct rib *rib,
                         int family)
{
  int bytelen;
  struct sockaddr_nl snl;
  struct nexthop *nexthop = NULL;
  int nexthop_num = 0;
  int discard;

  struct
  {
    struct nlmsghdr n;
    struct rtmsg r;
    char buf[1024];
  } req;

  memset (&req, 0, sizeof req);

  bytelen = (family == AF_INET ? 4 : 16);

  req.n.nlmsg_len = NLMSG_LENGTH (sizeof (struct rtmsg));
  req.n.nlmsg_flags = NLM_F_CREATE | NLM_F_REQUEST;
  req.n.nlmsg_type = cmd;
  req.r.rtm_family = family;
  req.r.rtm_table = rib->table;
  req.r.rtm_dst_len = p->prefixlen;

#ifdef RTM_F_EQUALIZE
  req.r.rtm_flags |= RTM_F_EQUALIZE;
#endif /* RTM_F_EQUALIZE */

  if ((rib->flags & ZEBRA_FLAG_BLACKHOLE) || (rib->flags & ZEBRA_FLAG_REJECT))
    discard = 1;
  else
    discard = 0;

  if (cmd == RTM_NEWROUTE)
    {
      req.r.rtm_protocol = RTPROT_ZEBRA;
      req.r.rtm_scope = RT_SCOPE_UNIVERSE;

      if (discard)
        {
          if (rib->flags & ZEBRA_FLAG_BLACKHOLE)
            req.r.rtm_type = RTN_BLACKHOLE;
          else if (rib->flags & ZEBRA_FLAG_REJECT)
            req.r.rtm_type = RTN_UNREACHABLE;
          else
            assert (RTN_BLACKHOLE != RTN_UNREACHABLE);  /* false */
        }
      else
        req.r.rtm_type = RTN_UNICAST;
    }

  addattr_l (&req.n, sizeof req, RTA_DST, &p->u.prefix, bytelen);

  /* Metric. */
  addattr32 (&req.n, sizeof req, RTA_PRIORITY, rib->metric);

  if (discard)
    {
      if (cmd == RTM_NEWROUTE)
        for (nexthop = rib->nexthop; nexthop; nexthop = nexthop->next)
          SET_FLAG (nexthop->flags, NEXTHOP_FLAG_FIB);
      goto skip;
    }

  /* Multipath case. */
  if (rib->nexthop_active_num == 1 || MULTIPATH_NUM == 1)
    {
      for (nexthop = rib->nexthop; nexthop; nexthop = nexthop->next)
        {

          if ((cmd == RTM_NEWROUTE
               && CHECK_FLAG (nexthop->flags, NEXTHOP_FLAG_ACTIVE))
              || (cmd == RTM_DELROUTE
                  && CHECK_FLAG (nexthop->flags, NEXTHOP_FLAG_FIB)))
            {

              if (CHECK_FLAG (nexthop->flags, NEXTHOP_FLAG_RECURSIVE))
                {
                  if (IS_ZEBRA_DEBUG_KERNEL)
                    {
                      zlog_debug
                        ("netlink_route_multipath() (recursive, 1 hop): "
                         "%s %s/%d, type %s", lookup (nlmsg_str, cmd),
#ifdef HAVE_IPV6
			 (family == AF_INET) ? inet_ntoa (p->u.prefix4) :
			 inet6_ntoa (p->u.prefix6),
#else
			 inet_ntoa (p->u.prefix4),
#endif /* HAVE_IPV6 */
			 
			 p->prefixlen, nexthop_types_desc[nexthop->rtype]);
                    }

                  if (nexthop->rtype == NEXTHOP_TYPE_IPV4
                      || nexthop->rtype == NEXTHOP_TYPE_IPV4_IFINDEX)
		    {
		      addattr_l (&req.n, sizeof req, RTA_GATEWAY,
				 &nexthop->rgate.ipv4, bytelen);

		      if (IS_ZEBRA_DEBUG_KERNEL)
			zlog_debug("netlink_route_multipath() (recursive, "
				   "1 hop): nexthop via %s if %u",
				   inet_ntoa (nexthop->rgate.ipv4),
				   nexthop->rifindex);
		    }
#ifdef HAVE_IPV6
                  if (nexthop->rtype == NEXTHOP_TYPE_IPV6
                      || nexthop->rtype == NEXTHOP_TYPE_IPV6_IFINDEX
                      || nexthop->rtype == NEXTHOP_TYPE_IPV6_IFNAME)
		    {
		      addattr_l (&req.n, sizeof req, RTA_GATEWAY,
				 &nexthop->rgate.ipv6, bytelen);

		      if (IS_ZEBRA_DEBUG_KERNEL)
			zlog_debug("netlink_route_multipath() (recursive, "
				   "1 hop): nexthop via %s if %u",
				   inet6_ntoa (nexthop->rgate.ipv6),
				   nexthop->rifindex);
		    }
#endif /* HAVE_IPV6 */
                  if (nexthop->rtype == NEXTHOP_TYPE_IFINDEX
                      || nexthop->rtype == NEXTHOP_TYPE_IFNAME
                      || nexthop->rtype == NEXTHOP_TYPE_IPV4_IFINDEX
                      || nexthop->rtype == NEXTHOP_TYPE_IPV6_IFINDEX
                      || nexthop->rtype == NEXTHOP_TYPE_IPV6_IFNAME)
		    {
		      addattr32 (&req.n, sizeof req, RTA_OIF,
				 nexthop->rifindex);

		      if (IS_ZEBRA_DEBUG_KERNEL)
			zlog_debug("netlink_route_multipath() (recursive, "
				   "1 hop): nexthop via if %u",
				   nexthop->rifindex);
		    }
                }
              else
                {
                  if (IS_ZEBRA_DEBUG_KERNEL)
                    {
                      zlog_debug
                        ("netlink_route_multipath() (single hop): "
                         "%s %s/%d, type %s", lookup (nlmsg_str, cmd),
#ifdef HAVE_IPV6
			 (family == AF_INET) ? inet_ntoa (p->u.prefix4) :
			 inet6_ntoa (p->u.prefix6),
#else
			 inet_ntoa (p->u.prefix4),
#endif /* HAVE_IPV6 */
			 p->prefixlen, nexthop_types_desc[nexthop->type]);
                    }

                  if (nexthop->type == NEXTHOP_TYPE_IPV4
                      || nexthop->type == NEXTHOP_TYPE_IPV4_IFINDEX)
		    {
		      addattr_l (&req.n, sizeof req, RTA_GATEWAY,
				 &nexthop->gate.ipv4, bytelen);

		      if (IS_ZEBRA_DEBUG_KERNEL)
			zlog_debug("netlink_route_multipath() (single hop): "
				   "nexthop via %s if %u",
				   inet_ntoa (nexthop->gate.ipv4),
				   nexthop->ifindex);
		    }
#ifdef HAVE_IPV6
                  if (nexthop->type == NEXTHOP_TYPE_IPV6
                      || nexthop->type == NEXTHOP_TYPE_IPV6_IFNAME
                      || nexthop->type == NEXTHOP_TYPE_IPV6_IFINDEX)
		    {
		      addattr_l (&req.n, sizeof req, RTA_GATEWAY,
				 &nexthop->gate.ipv6, bytelen);

		      if (IS_ZEBRA_DEBUG_KERNEL)
			zlog_debug("netlink_route_multipath() (single hop): "
				   "nexthop via %s if %u",
				   inet6_ntoa (nexthop->gate.ipv6),
				   nexthop->ifindex);
		    }
#endif /* HAVE_IPV6 */
                  if (nexthop->type == NEXTHOP_TYPE_IFINDEX
                      || nexthop->type == NEXTHOP_TYPE_IFNAME
                      || nexthop->type == NEXTHOP_TYPE_IPV4_IFINDEX
                      || nexthop->type == NEXTHOP_TYPE_IPV6_IFINDEX
                      || nexthop->type == NEXTHOP_TYPE_IPV6_IFNAME)
		    {
		      addattr32 (&req.n, sizeof req, RTA_OIF, nexthop->ifindex);

		      if (IS_ZEBRA_DEBUG_KERNEL)
			zlog_debug("netlink_route_multipath() (single hop): "
				   "nexthop via if %u", nexthop->ifindex);
		    }
                }

              if (cmd == RTM_NEWROUTE)
                SET_FLAG (nexthop->flags, NEXTHOP_FLAG_FIB);

              nexthop_num++;
              break;
            }
        }
    }
  else
    {
      char buf[1024];
      struct rtattr *rta = (void *) buf;
      struct rtnexthop *rtnh;

      rta->rta_type = RTA_MULTIPATH;
      rta->rta_len = RTA_LENGTH (0);
      rtnh = RTA_DATA (rta);

      nexthop_num = 0;
      for (nexthop = rib->nexthop;
           nexthop && (MULTIPATH_NUM == 0 || nexthop_num < MULTIPATH_NUM);
           nexthop = nexthop->next)
        {
          if ((cmd == RTM_NEWROUTE
               && CHECK_FLAG (nexthop->flags, NEXTHOP_FLAG_ACTIVE))
              || (cmd == RTM_DELROUTE
                  && CHECK_FLAG (nexthop->flags, NEXTHOP_FLAG_FIB)))
            {
              nexthop_num++;

              rtnh->rtnh_len = sizeof (*rtnh);
              rtnh->rtnh_flags = 0;
              rtnh->rtnh_hops = 0;
              rta->rta_len += rtnh->rtnh_len;

              if (CHECK_FLAG (nexthop->flags, NEXTHOP_FLAG_RECURSIVE))
                {
                  if (IS_ZEBRA_DEBUG_KERNEL)
                    {
                      zlog_debug ("netlink_route_multipath() "
                         "(recursive, multihop): %s %s/%d type %s",
			 lookup (nlmsg_str, cmd),
#ifdef HAVE_IPV6
			 (family == AF_INET) ? inet_ntoa (p->u.prefix4) :
			 inet6_ntoa (p->u.prefix6),
#else
			 inet_ntoa (p->u.prefix4),
#endif /* HAVE_IPV6 */
                         p->prefixlen, nexthop_types_desc[nexthop->rtype]);
                    }
                  if (nexthop->rtype == NEXTHOP_TYPE_IPV4
                      || nexthop->rtype == NEXTHOP_TYPE_IPV4_IFINDEX)
                    {
                      rta_addattr_l (rta, 4096, RTA_GATEWAY,
                                     &nexthop->rgate.ipv4, bytelen);
                      rtnh->rtnh_len += sizeof (struct rtattr) + 4;

		      if (IS_ZEBRA_DEBUG_KERNEL)
			zlog_debug("netlink_route_multipath() (recursive, "
				   "multihop): nexthop via %s if %u",
				   inet_ntoa (nexthop->rgate.ipv4),
				   nexthop->rifindex);
                    }
#ifdef HAVE_IPV6
                  if (nexthop->rtype == NEXTHOP_TYPE_IPV6
                      || nexthop->rtype == NEXTHOP_TYPE_IPV6_IFNAME
                      || nexthop->rtype == NEXTHOP_TYPE_IPV6_IFINDEX)
		    {
		      rta_addattr_l (rta, 4096, RTA_GATEWAY,
				     &nexthop->rgate.ipv6, bytelen);

		      if (IS_ZEBRA_DEBUG_KERNEL)
			zlog_debug("netlink_route_multipath() (recursive, "
				   "multihop): nexthop via %s if %u",
				   inet6_ntoa (nexthop->rgate.ipv6),
				   nexthop->rifindex);
		    }
#endif /* HAVE_IPV6 */
                  /* ifindex */
                  if (nexthop->rtype == NEXTHOP_TYPE_IFINDEX
                      || nexthop->rtype == NEXTHOP_TYPE_IFNAME
                      || nexthop->rtype == NEXTHOP_TYPE_IPV4_IFINDEX
                      || nexthop->rtype == NEXTHOP_TYPE_IPV6_IFINDEX
                      || nexthop->rtype == NEXTHOP_TYPE_IPV6_IFNAME)
		    {
		      rtnh->rtnh_ifindex = nexthop->rifindex;

		      if (IS_ZEBRA_DEBUG_KERNEL)
			zlog_debug("netlink_route_multipath() (recursive, "
				   "multihop): nexthop via if %u",
				   nexthop->rifindex);
		    }
                  else
		    {
		      rtnh->rtnh_ifindex = 0;
		    }
                }
              else
                {
                  if (IS_ZEBRA_DEBUG_KERNEL)
                    {
                      zlog_debug ("netlink_route_multipath() (multihop): "
                         "%s %s/%d, type %s", lookup (nlmsg_str, cmd),
#ifdef HAVE_IPV6
			 (family == AF_INET) ? inet_ntoa (p->u.prefix4) :
			 inet6_ntoa (p->u.prefix6),
#else
			 inet_ntoa (p->u.prefix4),
#endif /* HAVE_IPV6 */
			 p->prefixlen, nexthop_types_desc[nexthop->type]);
                    }
                  if (nexthop->type == NEXTHOP_TYPE_IPV4
                      || nexthop->type == NEXTHOP_TYPE_IPV4_IFINDEX)
                    {
		      rta_addattr_l (rta, 4096, RTA_GATEWAY,
				     &nexthop->gate.ipv4, bytelen);
		      rtnh->rtnh_len += sizeof (struct rtattr) + 4;

                      if (IS_ZEBRA_DEBUG_KERNEL)
			zlog_debug("netlink_route_multipath() (multihop): "
				   "nexthop via %s if %u",
				   inet_ntoa (nexthop->gate.ipv4),
				   nexthop->ifindex);
                    }
#ifdef HAVE_IPV6
                  if (nexthop->type == NEXTHOP_TYPE_IPV6
                      || nexthop->type == NEXTHOP_TYPE_IPV6_IFNAME
                      || nexthop->type == NEXTHOP_TYPE_IPV6_IFINDEX)
		    { 
		      rta_addattr_l (rta, 4096, RTA_GATEWAY,
				     &nexthop->gate.ipv6, bytelen);

		      if (IS_ZEBRA_DEBUG_KERNEL)
			zlog_debug("netlink_route_multipath() (multihop): "
				   "nexthop via %s if %u",
				   inet6_ntoa (nexthop->gate.ipv6),
				   nexthop->ifindex);
		    }
#endif /* HAVE_IPV6 */
                  /* ifindex */
                  if (nexthop->type == NEXTHOP_TYPE_IFINDEX
                      || nexthop->type == NEXTHOP_TYPE_IFNAME
                      || nexthop->type == NEXTHOP_TYPE_IPV4_IFINDEX
                      || nexthop->type == NEXTHOP_TYPE_IPV6_IFNAME
                      || nexthop->type == NEXTHOP_TYPE_IPV6_IFINDEX)
		    {
		      rtnh->rtnh_ifindex = nexthop->ifindex;

		      if (IS_ZEBRA_DEBUG_KERNEL)
			zlog_debug("netlink_route_multipath() (multihop): "
				   "nexthop via if %u", nexthop->ifindex);
		    }
                  else
		    {
		      rtnh->rtnh_ifindex = 0;
		    }
                }
              rtnh = RTNH_NEXT (rtnh);

              if (cmd == RTM_NEWROUTE)
                SET_FLAG (nexthop->flags, NEXTHOP_FLAG_FIB);
            }
        }

      if (rta->rta_len > RTA_LENGTH (0))
        addattr_l (&req.n, 1024, RTA_MULTIPATH, RTA_DATA (rta),
                   RTA_PAYLOAD (rta));
    }

  /* If there is no useful nexthop then return. */
  if (nexthop_num == 0)
    {
      if (IS_ZEBRA_DEBUG_KERNEL)
        zlog_debug ("netlink_route_multipath(): No useful nexthop.");
      return 0;
    }

skip:

  /* Destination netlink address. */
  memset (&snl, 0, sizeof snl);
  snl.nl_family = AF_NETLINK;

  /* Talk to netlink socket. */
  return netlink_talk (&req.n, &netlink_cmd);
}

int
kernel_add_ipv4 (struct prefix *p, struct rib *rib)
{
  return netlink_route_multipath (RTM_NEWROUTE, p, rib, AF_INET);
}

int
kernel_delete_ipv4 (struct prefix *p, struct rib *rib)
{
  return netlink_route_multipath (RTM_DELROUTE, p, rib, AF_INET);
}

#ifdef HAVE_IPV6
int
kernel_add_ipv6 (struct prefix *p, struct rib *rib)
{
  return netlink_route_multipath (RTM_NEWROUTE, p, rib, AF_INET6);
}

int
kernel_delete_ipv6 (struct prefix *p, struct rib *rib)
{
  return netlink_route_multipath (RTM_DELROUTE, p, rib, AF_INET6);
}

/* Delete IPv6 route from the kernel. */
int
kernel_delete_ipv6_old (struct prefix_ipv6 *dest, struct in6_addr *gate,
                        int index, int flags, int table)
{
  return netlink_route (RTM_DELROUTE, AF_INET6, &dest->prefix,
                        dest->prefixlen, gate, index, flags, table);
}
#endif /* HAVE_IPV6 */

/* Interface address modification. */
int
netlink_address (int cmd, int family, struct interface_FOO *ifp,
                 struct connected *ifc)
{
  int bytelen;
  struct prefix *p;

  struct
  {
    struct nlmsghdr n;
    struct ifaddrmsg ifa;
    char buf[1024];
  } req;

  p = ifc->address;
  memset (&req, 0, sizeof req);

  bytelen = (family == AF_INET ? 4 : 16);

  req.n.nlmsg_len = NLMSG_LENGTH (sizeof (struct ifaddrmsg));
  req.n.nlmsg_flags = NLM_F_REQUEST;
  req.n.nlmsg_type = cmd;
  req.ifa.ifa_family = family;

  req.ifa.ifa_index = ifp->ifindex;
  req.ifa.ifa_prefixlen = p->prefixlen;

  addattr_l (&req.n, sizeof req, IFA_LOCAL, &p->u.prefix, bytelen);

  if (family == AF_INET && cmd == RTM_NEWADDR)
    {
      if (if_is_broadcast (ifp) && ifc->destination)
        {
          p = ifc->destination;
          addattr_l (&req.n, sizeof req, IFA_BROADCAST, &p->u.prefix,
                     bytelen);
        }
    }

  if (CHECK_FLAG (ifc->flags, ZEBRA_IFA_SECONDARY))
    SET_FLAG (req.ifa.ifa_flags, IFA_F_SECONDARY);

  if (ifc->label)
    addattr_l (&req.n, sizeof req, IFA_LABEL, ifc->label,
               strlen (ifc->label) + 1);

  return netlink_talk (&req.n, &netlink_cmd);
}

int
kernel_address_add_ipv4 (struct interface_FOO *ifp, struct connected *ifc)
{
  return netlink_address (RTM_NEWADDR, AF_INET, ifp, ifc);
}

int
kernel_address_delete_ipv4 (struct interface_FOO *ifp, struct connected *ifc)
{
  return netlink_address (RTM_DELADDR, AF_INET, ifp, ifc);
}


extern struct thread_master *master_zebra;

/* Kernel route reflection. */
int
kernel_read (struct thread *thread)
{
  int ret;
  int sock;

  sock = THREAD_FD (thread);
  ret = netlink_parse_info (netlink_information_fetch, &netlink);
  thread_add_read (zebrad.master__item, kernel_read, NULL, netlink.sock);

  return 0;
}

/* Exported interface function.  This function simply calls
   netlink_socket (). */
void
kernel_init ()
{
  unsigned long groups;

  groups = RTMGRP_LINK | RTMGRP_IPV4_ROUTE | RTMGRP_IPV4_IFADDR;
#ifdef HAVE_IPV6
  groups |= RTMGRP_IPV6_ROUTE | RTMGRP_IPV6_IFADDR;
#endif /* HAVE_IPV6 */
  netlink_socket (&netlink, groups);
  netlink_socket (&netlink_cmd, 0);

  /* Register kernel socket. */
  if (netlink.sock > 0)
    thread_add_read (zebrad.master__item, kernel_read, NULL, netlink.sock);
}
