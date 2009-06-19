/* BGP network related fucntions
   Copyright (C) 1999 Kunihiro Ishiguro

This file is part of GNU Zebra.

GNU Zebra is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2, or (at your option) any
later version.

GNU Zebra is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU Zebra; see the file COPYING.  If not, write to the Free
Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
02111-1307, USA.  */

#include <zebra.h>

#include "thread.h"
#include "sockunion.h"
#include "sockopt.h"
#include "memory.h"
#include "log.h"
#include "if.h"
#include "prefix.h"
#include "command.h"
#include "privs.h"
#include "linklist.h"

#include "bgpd/bgpd.h"
#include "bgpd/bgp_fsm.h"
#include "bgpd/bgp_attr.h"
#include "bgpd/bgp_debug.h"
#include "bgpd/bgp_network.h"

extern struct zebra_privs_t bgpd_privs;


/*
 * Set MD5 key for the socket, for the given IPv4 peer address.
 * If the password is NULL or zero-length, the option will be disabled.
 */
static int
bgp_md5_set_socket (int socket, union sockunion *su, const char *password)
{
  int ret = -1;
  int en = ENOSYS;
  
  assert (socket >= 0);
  
#if HAVE_DECL_TCP_MD5SIG  
  ret = sockopt_tcp_signature (socket, su, password);
  en  = errno;
#endif /* HAVE_TCP_MD5SIG */
  
  if (ret < 0)
    zlog (NULL, LOG_WARNING, "can't set TCP_MD5SIG option on socket %d: %s",
          socket, safe_strerror (en));

  return ret;
}

/* Helper for bgp_connect */
static int
bgp_md5_set_connect (int socket, union sockunion *su, const char *password)
{
  int ret = -1;

#if HAVE_DECL_TCP_MD5SIG  
  if ( bgpd_privs.change (ZPRIVS_RAISE) )
    {
      zlog_err ("%s: could not raise privs", __func__);
      return ret;
    }
  
  ret = bgp_md5_set_socket (socket, su, password);

  if (bgpd_privs.change (ZPRIVS_LOWER) )
    zlog_err ("%s: could not lower privs", __func__);
#endif /* HAVE_TCP_MD5SIG */
  
  return ret;
}

int
bgp_md5_set (struct peer *peer)
{
  struct listnode *node;
  int fret = 0, ret;
  int *socket;

  if ( bgpd_privs.change (ZPRIVS_RAISE) )
    {
      zlog_err ("%s: could not raise privs", __func__);
      return -1;
    }
  
  /* Just set the password on the listen socket(s). Outbound connections
   * are taken care of in bgp_connect() below.
   */
  for (ALL_LIST_ELEMENTS_RO(bm->listen_sockets, node, socket))
    {
      ret = bgp_md5_set_socket ((int )socket, &peer->su, peer->password);
      if (ret < 0)
        fret = ret;
    }
  if (bgpd_privs.change (ZPRIVS_LOWER) )
    zlog_err ("%s: could not lower privs", __func__);
  
  return fret;
}

/* Accept bgp connection. */
static int
bgp_accept (struct thread *thread)
{
  int bgp_sock;
  int accept_sock;
  union sockunion su;
  struct peer *peer;
  struct peer *peer1;
  struct bgp *bgp;
  char buf[SU_ADDRSTRLEN];

  /* Regiser accept thread. */
  accept_sock = THREAD_FD (thread);
  bgp = THREAD_ARG (thread);

  if (accept_sock < 0)
    {
      zlog_err ("accept_sock is nevative value %d", accept_sock);
      return -1;
    }
  thread_add_read (master, bgp_accept, bgp, accept_sock);

  /* Accept client connection. */
  bgp_sock = sockunion_accept (accept_sock, &su);
  if (bgp_sock < 0)
    {
      zlog_err ("[Error] BGP socket accept failed (%s)", safe_strerror (errno));
      return -1;
    }

  if (BGP_DEBUG (events, EVENTS))
    zlog_debug ("[Event] BGP connection from host %s", inet_sutop (&su, buf));
  
  /* Check remote IP address */
  peer1 = peer_lookup (bgp, &su);
  if (! peer1 || peer1->status == Idle)
    {
      if (BGP_DEBUG (events, EVENTS))
	{
	  if (! peer1)
	    zlog_debug ("[Event] BGP connection IP address %s is not configured",
		       inet_sutop (&su, buf));
	  else
	    zlog_debug ("[Event] BGP connection IP address %s is Idle state",
		       inet_sutop (&su, buf));
	}
      close (bgp_sock);
      return -1;
    }

  /* In case of peer is EBGP, we should set TTL for this connection.  */
  if (peer_sort (peer1) == BGP_PEER_EBGP)
    sockopt_ttl (peer1->su.sa.sa_family, bgp_sock, peer1->ttl);

  if (! bgp)
    bgp = peer1->bgp;

  /* Make dummy peer until read Open packet. */
  if (BGP_DEBUG (events, EVENTS))
    zlog_debug ("[Event] Make dummy peer structure until read Open packet");

  {
    char buf[SU_ADDRSTRLEN + 1];

    peer = peer_create_accept (bgp);
    SET_FLAG (peer->sflags, PEER_STATUS_ACCEPT_PEER);
    peer->su = su;
    peer->fd = bgp_sock;
    peer->status = Active;
    peer->local_id = peer1->local_id;

    /* Make peer's address string. */
    sockunion2str (&su, buf, SU_ADDRSTRLEN);
    peer->host__item = XSTRDUP (MTYPE_BGP_PEER_HOST, buf);
  }

  BGP_EVENT_ADD (peer, TCP_connection_open);

  return 0;
}

/* BGP socket bind. */
static int
bgp_bind (struct peer *peer)
{
#ifdef SO_BINDTODEVICE
  int ret;
  struct ifreq ifreq;

  if (! peer->ifname)
    return 0;

  strncpy ((char *)&ifreq.ifr_name, peer->ifname, sizeof (ifreq.ifr_name));

  if ( bgpd_privs.change (ZPRIVS_RAISE) )
  	zlog_err ("bgp_bind: could not raise privs");
  
  ret = setsockopt (peer->fd, SOL_SOCKET, SO_BINDTODEVICE, 
		    &ifreq, sizeof (ifreq));

  if (bgpd_privs.change (ZPRIVS_LOWER) )
    zlog_err ("bgp_bind: could not lower privs");

  if (ret < 0)
    {
      zlog (peer->log, LOG_INFO, "bind to interface %s failed", peer->ifname);
      return ret;
    }
#endif /* SO_BINDTODEVICE */
  return 0;
}

static int
bgp_bind_address (int sock, struct in_addr *addr)
{
  int ret;
  struct sockaddr_in local;

  memset (&local, 0, sizeof (struct sockaddr_in));
  local.sin_family = AF_INET;
#ifdef HAVE_STRUCT_SOCKADDR_IN_SIN_LEN
  local.sin_len = sizeof(struct sockaddr_in);
#endif /* HAVE_STRUCT_SOCKADDR_IN_SIN_LEN */
  memcpy (&local.sin_addr, addr, sizeof (struct in_addr));

  if ( bgpd_privs.change (ZPRIVS_RAISE) )
    zlog_err ("bgp_bind_address: could not raise privs");
    
  ret = bind (sock, (struct sockaddr *)&local, sizeof (struct sockaddr_in));
  if (ret < 0)
    ;
    
  if (bgpd_privs.change (ZPRIVS_LOWER) )
    zlog_err ("bgp_bind_address: could not lower privs");
    
  return 0;
}

static struct in_addr *
bgp_update_address (struct interface_FOO *ifp)
{
  struct prefix_ipv4 *p;
  struct connected *connected;
  struct listnode *node;

  for (ALL_LIST_ELEMENTS_RO (ifp->connected, node, connected))
    {
      p = (struct prefix_ipv4 *) connected->address;

      if (p->family == AF_INET)
	return &p->prefix;
    }
  return NULL;
}

/* Update source selection.  */
static void
bgp_update_source (struct peer *peer)
{
  struct interface_FOO *ifp;
  struct in_addr *addr;

  /* Source is specified with interface name.  */
  if (peer->update_if)
    {
      ifp = if_lookup_by_name (peer->update_if);
      if (! ifp)
	return;

      addr = bgp_update_address (ifp);
      if (! addr)
	return;

      bgp_bind_address (peer->fd, addr);
    }

  /* Source is specified with IP address.  */
  if (peer->update_source)
    sockunion_bind (peer->fd, peer->update_source, 0, peer->update_source);
}

/* BGP try to connect to the peer.  */
int
bgp_connect (struct peer *peer)
{
  unsigned int ifindex = 0;

  /* Make socket for the peer. */
  peer->fd = sockunion_socket (&peer->su);
  if (peer->fd < 0)
    return -1;

  /* If we can get socket for the peer, adjest TTL and make connection. */
  if (peer_sort (peer) == BGP_PEER_EBGP)
    sockopt_ttl (peer->su.sa.sa_family, peer->fd, peer->ttl);

  sockopt_reuseaddr (peer->fd);
  sockopt_reuseport (peer->fd);
  
#ifdef IPTOS_PREC_INTERNETCONTROL
  if (sockunion_family (&peer->su) == AF_INET)
    setsockopt_ipv4_tos (peer->fd, IPTOS_PREC_INTERNETCONTROL);
#endif

  if (peer->password)
    bgp_md5_set_connect (peer->fd, &peer->su, peer->password);

  /* Bind socket. */
  bgp_bind (peer);

  /* Update source bind. */
  bgp_update_source (peer);

#ifdef HAVE_IPV6
  if (peer->ifname)
    ifindex = if_nametoindex (peer->ifname);
#endif /* HAVE_IPV6 */

  if (BGP_DEBUG (events, EVENTS))
    plog_debug (peer->log, "%s [Event] Connect start to %s fd %d",
	       peer->host__item, peer->host__item, peer->fd);

  /* Connect to the remote peer. */
  return sockunion_connect (peer->fd, &peer->su, htons (peer->port), ifindex);
}

/* After TCP connection is established.  Get local address and port. */
void
bgp_getsockname (struct peer *peer)
{
  if (peer->su_local)
    {
      sockunion_free (peer->su_local);
      peer->su_local = NULL;
    }

  if (peer->su_remote)
    {
      sockunion_free (peer->su_remote);
      peer->su_remote = NULL;
    }

  peer->su_local = sockunion_getsockname (peer->fd);
  peer->su_remote = sockunion_getpeername (peer->fd);

  bgp_nexthop_set (peer->su_local, peer->su_remote, &peer->nexthop, peer);
}

/* IPv6 supported version of BGP server socket setup.  */
#if defined (HAVE_IPV6) && ! defined (NRL)
int
bgp_socket (struct bgp *bgp, unsigned short port, char *address)
{
  int ret, en;
  struct addrinfo req;
  struct addrinfo *ainfo;
  struct addrinfo *ainfo_save;
  int sock = 0;
  char port_str[BUFSIZ];

  memset (&req, 0, sizeof (struct addrinfo));

  req.ai_flags = AI_PASSIVE;
  req.ai_family = AF_UNSPEC;
  req.ai_socktype = SOCK_STREAM;
  snprintf (port_str, sizeof(port_str), "%d", port);
  port_str[sizeof (port_str) - 1] = '\0';

  ret = getaddrinfo (address, port_str, &req, &ainfo);
  if (ret != 0)
    {
      zlog_err ("getaddrinfo: %s", gai_strerror (ret));
      return -1;
    }

  ainfo_save = ainfo;

  do
    {
      if (ainfo->ai_family != AF_INET && ainfo->ai_family != AF_INET6)
	continue;
     
      sock = socket (ainfo->ai_family, ainfo->ai_socktype, ainfo->ai_protocol);
      if (sock < 0)
	{
	  zlog_err ("socket: %s", safe_strerror (errno));
	  continue;
	}

      sockopt_reuseaddr (sock);
      sockopt_reuseport (sock);
      
#ifdef IPTOS_PREC_INTERNETCONTROL
      if (ainfo->ai_family == AF_INET)
	setsockopt_ipv4_tos (sock, IPTOS_PREC_INTERNETCONTROL);
#endif

#ifdef IPV6_V6ONLY
      /* Want only IPV6 on ipv6 socket (not mapped addresses) */
      if (ainfo->ai_family == AF_INET6) {
	int on = 1;
	setsockopt (sock, IPPROTO_IPV6, IPV6_V6ONLY, 
		    (void *) &on, sizeof (on));
      }
#endif

      if (bgpd_privs.change (ZPRIVS_RAISE) )
        zlog_err ("bgp_socket: could not raise privs");

      ret = bind (sock, ainfo->ai_addr, ainfo->ai_addrlen);
      en = errno;
      if (bgpd_privs.change (ZPRIVS_LOWER) )
	zlog_err ("bgp_bind_address: could not lower privs");

      if (ret < 0)
	{
	  zlog_err ("bind: %s", safe_strerror (en));
	  close(sock);
	  continue;
	}
      
      ret = listen (sock, 3);
      if (ret < 0) 
	{
	  zlog_err ("listen: %s", safe_strerror (errno));
	  close (sock);
	  continue;
	}
      
      listnode_add (bm->listen_sockets, (void *)sock);
      thread_add_read (master, bgp_accept, bgp, sock);
    }
  while ((ainfo = ainfo->ai_next) != NULL);

  freeaddrinfo (ainfo_save);

  return sock;
}
#else
/* Traditional IPv4 only version.  */
int
bgp_socket (struct bgp *bgp, unsigned short port, char *address)
{
  int sock;
  int socklen;
  struct sockaddr_in sin;
  int ret, en;

  sock = socket (AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
    {
      zlog_err ("socket: %s", safe_strerror (errno));
      return sock;
    }

  sockopt_reuseaddr (sock);
  sockopt_reuseport (sock);

#ifdef IPTOS_PREC_INTERNETCONTROL
  setsockopt_ipv4_tos (sock, IPTOS_PREC_INTERNETCONTROL);
#endif

  memset (&sin, 0, sizeof (struct sockaddr_in));

  sin.sin_family = AF_INET;
  sin.sin_port = htons (port);
  socklen = sizeof (struct sockaddr_in);

  if (address && ((ret = inet_aton(address, &sin.sin_addr)) < 1))
    {
      zlog_err("bgp_socket: could not parse ip address %s: %s",
                address, safe_strerror (errno));
      return ret;
    }
#ifdef HAVE_STRUCT_SOCKADDR_IN_SIN_LEN
  sin.sin_len = socklen;
#endif /* HAVE_STRUCT_SOCKADDR_IN_SIN_LEN */

  if ( bgpd_privs.change (ZPRIVS_RAISE) )
    zlog_err ("bgp_socket: could not raise privs");

  ret = bind (sock, (struct sockaddr *) &sin, socklen);
  en = errno;

  if (bgpd_privs.change (ZPRIVS_LOWER) )
    zlog_err ("bgp_socket: could not lower privs");

  if (ret < 0)
    {
      zlog_err ("bind: %s", safe_strerror (en));
      close (sock);
      return ret;
    }
  
  ret = listen (sock, 3);
  if (ret < 0) 
    {
      zlog_err ("listen: %s", safe_strerror (errno));
      close (sock);
      return ret;
    }

  thread_add_read (bm->master__item, bgp_accept, bgp, sock);

  return sock;
}
#endif /* HAVE_IPV6 && !NRL */
