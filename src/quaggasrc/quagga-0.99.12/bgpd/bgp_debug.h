/* BGP message debug header.
   Copyright (C) 1996, 97, 98 Kunihiro Ishiguro

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

#ifndef _QUAGGA_BGP_DEBUG_H
#define _QUAGGA_BGP_DEBUG_H

#include "bgp_attr.h"

/* sort of packet direction */
#define DUMP_ON        1
#define DUMP_SEND      2
#define DUMP_RECV      4

/* for dump_update */
#define DUMP_WITHDRAW  8
#define DUMP_NLRI     16

/* dump detail */
#define DUMP_DETAIL   32

extern int dump_open_bgpd;
extern int dump_update_bgpd;
extern int dump_keepalive_bgpd;
extern int dump_notify_bgpd;

extern int Debug_Event_bgpd;
extern int Debug_Keepalive_bgpd;
extern int Debug_Update_bgpd;
extern int Debug_Radix_bgpd;

#define	NLRI	 1
#define	WITHDRAW 2
#define	NO_OPT	 3
#define	SEND	 4
#define	RECV	 5
#define	DETAIL	 6

/* Prototypes. */
extern void bgp_debug_init (void);
extern void bgp_packet_dump (struct stream *);

extern int debug (unsigned int option);

extern unsigned long conf_bgp_debug_as4_bgpd;
extern unsigned long conf_bgp_debug_fsm_bgpd;
extern unsigned long conf_bgp_debug_events_bgpd;
extern unsigned long conf_bgp_debug_packet_bgpd;
extern unsigned long conf_bgp_debug_filter_bgpd;
extern unsigned long conf_bgp_debug_keepalive_bgpd;
extern unsigned long conf_bgp_debug_update_bgpd;
extern unsigned long conf_bgp_debug_normal_bgpd;
extern unsigned long conf_bgp_debug_zebra_bgpd;

extern unsigned long term_bgp_debug_as4_bgpd;
extern unsigned long term_bgp_debug_fsm_bgpd;
extern unsigned long term_bgp_debug_events_bgpd;
extern unsigned long term_bgp_debug_packet_bgpd;
extern unsigned long term_bgp_debug_filter_bgpd;
extern unsigned long term_bgp_debug_keepalive_bgpd;
extern unsigned long term_bgp_debug_update_bgpd;
extern unsigned long term_bgp_debug_normal_bgpd;
extern unsigned long term_bgp_debug_zebra_bgpd;

#define BGP_DEBUG_AS4                 0x01
#define BGP_DEBUG_AS4_SEGMENT         0x02

#define BGP_DEBUG_FSM                 0x01
#define BGP_DEBUG_EVENTS              0x01
#define BGP_DEBUG_PACKET              0x01
#define BGP_DEBUG_FILTER              0x01
#define BGP_DEBUG_KEEPALIVE           0x01
#define BGP_DEBUG_UPDATE_IN           0x01
#define BGP_DEBUG_UPDATE_OUT          0x02
#define BGP_DEBUG_NORMAL              0x01
#define BGP_DEBUG_ZEBRA               0x01

#define BGP_DEBUG_PACKET_SEND         0x01
#define BGP_DEBUG_PACKET_SEND_DETAIL  0x02

#define BGP_DEBUG_PACKET_RECV         0x01
#define BGP_DEBUG_PACKET_RECV_DETAIL  0x02

#define CONF_DEBUG_ON_BGPD(a, b)	(conf_bgp_debug_ ## a |= (BGP_DEBUG_ ## b))
#define CONF_DEBUG_OFF_BGPD(a, b)	(conf_bgp_debug_ ## a &= ~(BGP_DEBUG_ ## b))

#define TERM_DEBUG_ON_BGPD(a, b)	(term_bgp_debug_ ## a |= (BGP_DEBUG_ ## b))
#define TERM_DEBUG_OFF_BGPD(a, b)	(term_bgp_debug_ ## a &= ~(BGP_DEBUG_ ## b))

#define DEBUG_ON_BGPD(a, b) \
    do { \
	CONF_DEBUG_ON_BGPD(a, b); \
	TERM_DEBUG_ON_BGPD(a, b); \
    } while (0)
#define DEBUG_OFF_BGPD(a, b) \
    do { \
	CONF_DEBUG_OFF_BGPD(a, b); \
	TERM_DEBUG_OFF_BGPD(a, b); \
    } while (0)

#define BGP_DEBUG(a, b)		(term_bgp_debug_ ## a & BGP_DEBUG_ ## b)
#define CONF_BGP_DEBUG(a, b)    (conf_bgp_debug_ ## a & BGP_DEBUG_ ## b)

extern const char *bgp_type_str[];

extern int bgp_dump_attr (struct peer *, struct attr *, char *, size_t);
extern void bgp_notify_print (struct peer *, struct bgp_notify *, const char *);

extern struct message bgp_status_msg[];
extern int bgp_status_msg_max_bgpd;

#endif /* _QUAGGA_BGP_DEBUG_H */
