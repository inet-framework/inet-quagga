/* BGP-4, BGP-4+ packet debug routine
   Copyright (C) 1996, 97, 99 Kunihiro Ishiguro

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

#include <lib/version.h>
#include "prefix.h"
#include "linklist.h"
#include "stream.h"
#include "command.h"
#include "str.h"
#include "log.h"
#include "sockunion.h"

#include "bgpd/bgpd.h"
#include "bgpd/bgp_aspath.h"
#include "bgpd/bgp_route.h"
#include "bgpd/bgp_attr.h"
#include "bgpd/bgp_debug.h"
#include "bgpd/bgp_community.h"

unsigned long conf_bgp_debug_as4_bgpd;
unsigned long conf_bgp_debug_fsm_bgpd;
unsigned long conf_bgp_debug_events_bgpd;
unsigned long conf_bgp_debug_packet_bgpd;
unsigned long conf_bgp_debug_filter_bgpd;
unsigned long conf_bgp_debug_keepalive_bgpd;
unsigned long conf_bgp_debug_update_bgpd;
unsigned long conf_bgp_debug_normal_bgpd;
unsigned long conf_bgp_debug_zebra_bgpd;

unsigned long term_bgp_debug_as4_bgpd;
unsigned long term_bgp_debug_fsm_bgpd;
unsigned long term_bgp_debug_events_bgpd;
unsigned long term_bgp_debug_packet_bgpd;
unsigned long term_bgp_debug_filter_bgpd;
unsigned long term_bgp_debug_keepalive_bgpd;
unsigned long term_bgp_debug_update_bgpd;
unsigned long term_bgp_debug_normal_bgpd;
unsigned long term_bgp_debug_zebra_bgpd;

/* messages for BGP-4 status */
struct message bgp_status_msg[] = 
{
  { Idle, "Idle" },
  { Connect, "Connect" },
  { Active, "Active" },
  { OpenSent, "OpenSent" },
  { OpenConfirm, "OpenConfirm" },
  { Established, "Established" },
  { Clearing,    "Clearing"    },
  { Deleted,     "Deleted"     },
};
int bgp_status_msg_max_bgpd ;

/* BGP message type string. */
const char *bgp_type_str[] =
{
  NULL,
  "OPEN",
  "UPDATE",
  "NOTIFICATION",
  "KEEPALIVE",
  "ROUTE-REFRESH",
  "CAPABILITY"
};

/* message for BGP-4 Notify */
struct message bgp_notify_msg[] = 
{
  { BGP_NOTIFY_HEADER_ERR, "Message Header Error"},
  { BGP_NOTIFY_OPEN_ERR, "OPEN Message Error"},
  { BGP_NOTIFY_UPDATE_ERR, "UPDATE Message Error"},
  { BGP_NOTIFY_HOLD_ERR, "Hold Timer Expired"},
  { BGP_NOTIFY_FSM_ERR, "Finite State Machine Error"},
  { BGP_NOTIFY_CEASE, "Cease"},
  { BGP_NOTIFY_CAPABILITY_ERR, "CAPABILITY Message Error"},
};
int bgp_notify_msg_max_bgpd ;

struct message bgp_notify_head_msg[] = 
{
  { BGP_NOTIFY_HEADER_NOT_SYNC, "/Connection Not Synchronized"},
  { BGP_NOTIFY_HEADER_BAD_MESLEN, "/Bad Message Length"},
  { BGP_NOTIFY_HEADER_BAD_MESTYPE, "/Bad Message Type"}
};
int bgp_notify_head_msg_max_bgpd ;

struct message bgp_notify_open_msg[] = 
{
  { BGP_NOTIFY_OPEN_UNSUP_VERSION, "/Unsupported Version Number" },
  { BGP_NOTIFY_OPEN_BAD_PEER_AS, "/Bad Peer AS"},
  { BGP_NOTIFY_OPEN_BAD_BGP_IDENT, "/Bad BGP Identifier"},
  { BGP_NOTIFY_OPEN_UNSUP_PARAM, "/Unsupported Optional Parameter"},
  { BGP_NOTIFY_OPEN_AUTH_FAILURE, "/Authentication Failure"},
  { BGP_NOTIFY_OPEN_UNACEP_HOLDTIME, "/Unacceptable Hold Time"}, 
  { BGP_NOTIFY_OPEN_UNSUP_CAPBL, "/Unsupported Capability"},
};
int bgp_notify_open_msg_max_bgpd ;

struct message bgp_notify_update_msg[] = 
{
  { BGP_NOTIFY_UPDATE_MAL_ATTR, "/Malformed Attribute List"},
  { BGP_NOTIFY_UPDATE_UNREC_ATTR, "/Unrecognized Well-known Attribute"},
  { BGP_NOTIFY_UPDATE_MISS_ATTR, "/Missing Well-known Attribute"},
  { BGP_NOTIFY_UPDATE_ATTR_FLAG_ERR, "/Attribute Flags Error"},
  { BGP_NOTIFY_UPDATE_ATTR_LENG_ERR, "/Attribute Length Error"},
  { BGP_NOTIFY_UPDATE_INVAL_ORIGIN, "/Invalid ORIGIN Attribute"},
  { BGP_NOTIFY_UPDATE_AS_ROUTE_LOOP, "/AS Routing Loop"},
  { BGP_NOTIFY_UPDATE_INVAL_NEXT_HOP, "/Invalid NEXT_HOP Attribute"},
  { BGP_NOTIFY_UPDATE_OPT_ATTR_ERR, "/Optional Attribute Error"},
  { BGP_NOTIFY_UPDATE_INVAL_NETWORK, "/Invalid Network Field"},
  { BGP_NOTIFY_UPDATE_MAL_AS_PATH, "/Malformed AS_PATH"},
};
int bgp_notify_update_msg_max_bgpd ;

struct message bgp_notify_cease_msg[] =
{
  { BGP_NOTIFY_CEASE_MAX_PREFIX, "/Maximum Number of Prefixes Reached"},
  { BGP_NOTIFY_CEASE_ADMIN_SHUTDOWN, "/Administratively Shutdown"},
  { BGP_NOTIFY_CEASE_PEER_UNCONFIG, "/Peer Unconfigured"},
  { BGP_NOTIFY_CEASE_ADMIN_RESET, "/Administratively Reset"},
  { BGP_NOTIFY_CEASE_CONNECT_REJECT, "/Connection Rejected"},
  { BGP_NOTIFY_CEASE_CONFIG_CHANGE, "/Other Configuration Change"},
  { BGP_NOTIFY_CEASE_COLLISION_RESOLUTION, "/Connection collision resolution"},
  { BGP_NOTIFY_CEASE_OUT_OF_RESOURCE, "/Out of Resource"},
};
int bgp_notify_cease_msg_max_bgpd ;

struct message bgp_notify_capability_msg[] = 
{
  { BGP_NOTIFY_CAPABILITY_INVALID_ACTION, "/Invalid Action Value" },
  { BGP_NOTIFY_CAPABILITY_INVALID_LENGTH, "/Invalid Capability Length"},
  { BGP_NOTIFY_CAPABILITY_MALFORMED_CODE, "/Malformed Capability Value"},
};
int bgp_notify_capability_msg_max_bgpd ;

/* Origin strings. */
const char *bgp_origin_str[] = {"i","e","?"};
const char *bgp_origin_long_str[] = {"IGP","EGP","incomplete"};

/* Dump attribute. */
int
bgp_dump_attr (struct peer *peer, struct attr *attr, char *buf, size_t size)
{
  if (! attr)
    return 0;

  if (CHECK_FLAG (attr->flag, ATTR_FLAG_BIT (BGP_ATTR_NEXT_HOP)))
    snprintf (buf, size, "nexthop %s", inet_ntoa (attr->nexthop));

  if (CHECK_FLAG (attr->flag, ATTR_FLAG_BIT (BGP_ATTR_ORIGIN)))
    snprintf (buf + strlen (buf), size - strlen (buf), ", origin %s",
	      bgp_origin_str[attr->origin]);

#ifdef HAVE_IPV6
  if (attr->extra)
    {
      char addrbuf[BUFSIZ];

      /* Add MP case. */
      if (attr->extra->mp_nexthop_len == 16 
          || attr->extra->mp_nexthop_len == 32)
        snprintf (buf + strlen (buf), size - strlen (buf), ", mp_nexthop %s",
                  inet_ntop (AF_INET6, &attr->extra->mp_nexthop_global, 
                             addrbuf, BUFSIZ));

      if (attr->extra->mp_nexthop_len == 32)
        snprintf (buf + strlen (buf), size - strlen (buf), "(%s)",
                  inet_ntop (AF_INET6, &attr->extra->mp_nexthop_local, 
                             addrbuf, BUFSIZ));
    }
#endif /* HAVE_IPV6 */

  if (CHECK_FLAG (attr->flag, ATTR_FLAG_BIT (BGP_ATTR_LOCAL_PREF)))
    snprintf (buf + strlen (buf), size - strlen (buf), ", localpref %d",
	      attr->local_pref);

  if (CHECK_FLAG (attr->flag, ATTR_FLAG_BIT (BGP_ATTR_MULTI_EXIT_DISC))) 
    snprintf (buf + strlen (buf), size - strlen (buf), ", metric %d",
	      attr->med);

  if (CHECK_FLAG (attr->flag, ATTR_FLAG_BIT (BGP_ATTR_COMMUNITIES))) 
    snprintf (buf + strlen (buf), size - strlen (buf), ", community %s",
	      community_str (attr->community));

  if (CHECK_FLAG (attr->flag, ATTR_FLAG_BIT (BGP_ATTR_ATOMIC_AGGREGATE)))
    snprintf (buf + strlen (buf), size - strlen (buf), ", atomic-aggregate");

  if (CHECK_FLAG (attr->flag, ATTR_FLAG_BIT (BGP_ATTR_AGGREGATOR)))
    snprintf (buf + strlen (buf), size - strlen (buf), ", aggregated by %u %s",
	      attr->extra->aggregator_as,
	      inet_ntoa (attr->extra->aggregator_addr));

  if (CHECK_FLAG (attr->flag, ATTR_FLAG_BIT (BGP_ATTR_ORIGINATOR_ID)))
    snprintf (buf + strlen (buf), size - strlen (buf), ", originator %s",
	      inet_ntoa (attr->extra->originator_id));

  if (CHECK_FLAG (attr->flag, ATTR_FLAG_BIT (BGP_ATTR_CLUSTER_LIST)))
    {
      int i;

      snprintf (buf + strlen (buf), size - strlen (buf), ", clusterlist");
      for (i = 0; i < attr->extra->cluster->length / 4; i++)
	snprintf (buf + strlen (buf), size - strlen (buf), " %s",
		  inet_ntoa (attr->extra->cluster->list[i]));
    }

  if (CHECK_FLAG (attr->flag, ATTR_FLAG_BIT (BGP_ATTR_AS_PATH))) 
    snprintf (buf + strlen (buf), size - strlen (buf), ", path %s",
	      aspath_print (attr->aspath));

  if (strlen (buf) > 1)
    return 1;
  else
    return 0;
}

/* dump notify packet */
void
bgp_notify_print(struct peer *peer, struct bgp_notify *bgp_notify, 
                 const char *direct)
{
  const char *subcode_str;

  subcode_str = "";

  switch (bgp_notify->code) 
    {
    case BGP_NOTIFY_HEADER_ERR:
      subcode_str = LOOKUP (bgp_notify_head_msg, bgp_notify->subcode);
      break;
    case BGP_NOTIFY_OPEN_ERR:
      subcode_str = LOOKUP (bgp_notify_open_msg, bgp_notify->subcode);
      break;
    case BGP_NOTIFY_UPDATE_ERR:
      subcode_str = LOOKUP (bgp_notify_update_msg, bgp_notify->subcode);
      break;
    case BGP_NOTIFY_HOLD_ERR:
      subcode_str = "";
      break;
    case BGP_NOTIFY_FSM_ERR:
      subcode_str = "";
      break;
    case BGP_NOTIFY_CEASE:
      subcode_str = LOOKUP (bgp_notify_cease_msg, bgp_notify->subcode);
      break;
    case BGP_NOTIFY_CAPABILITY_ERR:
      subcode_str = LOOKUP (bgp_notify_capability_msg, bgp_notify->subcode);
      break;
    }

  if (bgp_flag_check (peer->bgp, BGP_FLAG_LOG_NEIGHBOR_CHANGES))
    zlog_info ("%%NOTIFICATION: %s neighbor %s %d/%d (%s%s) %d bytes %s",
              strcmp (direct, "received") == 0 ? "received from" : "sent to",
              peer->host__item, bgp_notify->code, bgp_notify->subcode,
               LOOKUP (bgp_notify_msg, bgp_notify->code),
              subcode_str, bgp_notify->length,
              bgp_notify->data ? bgp_notify->data : "");
  else if (BGP_DEBUG (normal, NORMAL))
    plog_debug (peer->log, "%s %s NOTIFICATION %d/%d (%s%s) %d bytes %s",
	       peer ? peer->host__item : "",
	       direct, bgp_notify->code, bgp_notify->subcode,
	       LOOKUP (bgp_notify_msg, bgp_notify->code),
	       subcode_str, bgp_notify->length,
	       bgp_notify->data ? bgp_notify->data : "");
}

/* Debug option setting interface. */
unsigned long bgp_debug_option_bgpd ;

int  
debug (unsigned int option)
{
  return bgp_debug_option & option; 
}

#undef	debug_bgp_as4_cmd
DEFUN (debug_bgp_as4,
       debug_bgp_as4_cmd,
       "debug bgp as4",
       DEBUG_STR
       BGP_STR
       "BGP AS4 actions\n")
{
  if (vty->node == CONFIG_NODE)
    DEBUG_ON_BGPD (as4, AS4);
  else
    {
      TERM_DEBUG_ON_BGPD (as4, AS4);
      vty_out (vty, "BGP as4 debugging is on%s", VTY_NEWLINE);
    }
  return CMD_SUCCESS;
}
#define	debug_bgp_as4_cmd	debug_bgp_as4_cmd__VAR

#undef	no_debug_bgp_as4_cmd
DEFUN (no_debug_bgp_as4,
       no_debug_bgp_as4_cmd,
       "no debug bgp as4",
       NO_STR
       DEBUG_STR
       BGP_STR
       "BGP AS4 actions\n")
{
  if (vty->node == CONFIG_NODE)
    DEBUG_OFF_BGPD (as4, AS4);
  else
    {
      TERM_DEBUG_OFF_BGPD (as4, AS4);
      vty_out (vty, "BGP as4 debugging is off%s", VTY_NEWLINE);
    }
  return CMD_SUCCESS;
}
#define	no_debug_bgp_as4_cmd	no_debug_bgp_as4_cmd__VAR

#undef	undebug_bgp_as4_cmd
ALIAS (no_debug_bgp_as4,
       undebug_bgp_as4_cmd,
       "undebug bgp as4",
       UNDEBUG_STR
       DEBUG_STR
       BGP_STR
       "BGP AS4 actions\n");
#define	undebug_bgp_as4_cmd	undebug_bgp_as4_cmd__VAR

#undef	debug_bgp_as4_segment_cmd
DEFUN (debug_bgp_as4_segment,
       debug_bgp_as4_segment_cmd,
       "debug bgp as4 segment",
       DEBUG_STR
       BGP_STR
       "BGP AS4 aspath segment handling\n")
{
  if (vty->node == CONFIG_NODE)
    DEBUG_ON_BGPD (as4, AS4_SEGMENT);
  else
    {
      TERM_DEBUG_ON_BGPD (as4, AS4_SEGMENT);
      vty_out (vty, "BGP as4 segment debugging is on%s", VTY_NEWLINE);
    }
  return CMD_SUCCESS;
}
#define	debug_bgp_as4_segment_cmd	debug_bgp_as4_segment_cmd__VAR

#undef	no_debug_bgp_as4_segment_cmd
DEFUN (no_debug_bgp_as4_segment,
       no_debug_bgp_as4_segment_cmd,
       "no debug bgp as4 segment",
       NO_STR
       DEBUG_STR
       BGP_STR
       "BGP AS4 aspath segment handling\n")
{
  if (vty->node == CONFIG_NODE)
    DEBUG_OFF_BGPD (as4, AS4_SEGMENT);
  else
    {
      TERM_DEBUG_OFF_BGPD (as4, AS4_SEGMENT);
      vty_out (vty, "BGP as4 segment debugging is off%s", VTY_NEWLINE);
    }
  return CMD_SUCCESS;
}
#define	no_debug_bgp_as4_segment_cmd	no_debug_bgp_as4_segment_cmd__VAR

#undef	undebug_bgp_as4_segment_cmd
ALIAS (no_debug_bgp_as4_segment,
       undebug_bgp_as4_segment_cmd,
       "undebug bgp as4 segment",
       UNDEBUG_STR
       DEBUG_STR
       BGP_STR
       "BGP AS4 aspath segment handling\n");
#define	undebug_bgp_as4_segment_cmd	undebug_bgp_as4_segment_cmd__VAR

#undef	debug_bgp_fsm_cmd
DEFUN (debug_bgp_fsm,
       debug_bgp_fsm_cmd,
       "debug bgp fsm",
       DEBUG_STR
       BGP_STR
       "BGP Finite State Machine\n")
{
  if (vty->node == CONFIG_NODE)
    DEBUG_ON_BGPD (fsm, FSM);
  else
    {
      TERM_DEBUG_ON_BGPD (fsm, FSM);
      vty_out (vty, "BGP fsm debugging is on%s", VTY_NEWLINE);
    }
  return CMD_SUCCESS;
}
#define	debug_bgp_fsm_cmd	debug_bgp_fsm_cmd__VAR

#undef	no_debug_bgp_fsm_cmd
DEFUN (no_debug_bgp_fsm,
       no_debug_bgp_fsm_cmd,
       "no debug bgp fsm",
       NO_STR
       DEBUG_STR
       BGP_STR
       "Finite State Machine\n")
{
  if (vty->node == CONFIG_NODE)
    DEBUG_OFF_BGPD (fsm, FSM);
  else
    {
      TERM_DEBUG_OFF_BGPD (fsm, FSM);
      vty_out (vty, "BGP fsm debugging is off%s", VTY_NEWLINE);
    }
  return CMD_SUCCESS;
}
#define	no_debug_bgp_fsm_cmd	no_debug_bgp_fsm_cmd__VAR

#undef	undebug_bgp_fsm_cmd
ALIAS (no_debug_bgp_fsm,
       undebug_bgp_fsm_cmd,
       "undebug bgp fsm",
       UNDEBUG_STR
       DEBUG_STR
       BGP_STR
       "Finite State Machine\n");
#define	undebug_bgp_fsm_cmd	undebug_bgp_fsm_cmd__VAR

#undef	debug_bgp_events_cmd
DEFUN (debug_bgp_events,
       debug_bgp_events_cmd,
       "debug bgp events",
       DEBUG_STR
       BGP_STR
       "BGP events\n")
{
  if (vty->node == CONFIG_NODE)
    DEBUG_ON_BGPD (events, EVENTS);
  else
    {
      TERM_DEBUG_ON_BGPD (events, EVENTS);
      vty_out (vty, "BGP events debugging is on%s", VTY_NEWLINE);
    }
  return CMD_SUCCESS;
}
#define	debug_bgp_events_cmd	debug_bgp_events_cmd__VAR

#undef	no_debug_bgp_events_cmd
DEFUN (no_debug_bgp_events,
       no_debug_bgp_events_cmd,
       "no debug bgp events",
       NO_STR
       DEBUG_STR
       BGP_STR
       "BGP events\n")
{
  if (vty->node == CONFIG_NODE)
    DEBUG_OFF_BGPD (events, EVENTS);
  else
    {
      TERM_DEBUG_OFF_BGPD (events, EVENTS);
      vty_out (vty, "BGP events debugging is off%s", VTY_NEWLINE);
    }
  return CMD_SUCCESS;
}
#define	no_debug_bgp_events_cmd	no_debug_bgp_events_cmd__VAR

#undef	undebug_bgp_events_cmd
ALIAS (no_debug_bgp_events,
       undebug_bgp_events_cmd,
       "undebug bgp events",
       UNDEBUG_STR
       BGP_STR
       "BGP events\n");
#define	undebug_bgp_events_cmd	undebug_bgp_events_cmd__VAR

#undef	debug_bgp_filter_cmd
DEFUN (debug_bgp_filter,
       debug_bgp_filter_cmd,
       "debug bgp filters",
       DEBUG_STR
       BGP_STR
       "BGP filters\n")
{
  if (vty->node == CONFIG_NODE)
    DEBUG_ON_BGPD (filter, FILTER);
  else
    {
      TERM_DEBUG_ON_BGPD (filter, FILTER);
      vty_out (vty, "BGP filters debugging is on%s", VTY_NEWLINE);
    }
  return CMD_SUCCESS;
}
#define	debug_bgp_filter_cmd	debug_bgp_filter_cmd__VAR

#undef	no_debug_bgp_filter_cmd
DEFUN (no_debug_bgp_filter,
       no_debug_bgp_filter_cmd,
       "no debug bgp filters",
       NO_STR
       DEBUG_STR
       BGP_STR
       "BGP filters\n")
{
  if (vty->node == CONFIG_NODE)
    DEBUG_OFF_BGPD (filter, FILTER);
  else
    {
      TERM_DEBUG_OFF_BGPD (filter, FILTER);
      vty_out (vty, "BGP filters debugging is off%s", VTY_NEWLINE);
    }
  return CMD_SUCCESS;
}
#define	no_debug_bgp_filter_cmd	no_debug_bgp_filter_cmd__VAR

#undef	undebug_bgp_filter_cmd
ALIAS (no_debug_bgp_filter,
       undebug_bgp_filter_cmd,
       "undebug bgp filters",
       UNDEBUG_STR
       BGP_STR
       "BGP filters\n");
#define	undebug_bgp_filter_cmd	undebug_bgp_filter_cmd__VAR

#undef	debug_bgp_keepalive_cmd
DEFUN (debug_bgp_keepalive,
       debug_bgp_keepalive_cmd,
       "debug bgp keepalives",
       DEBUG_STR
       BGP_STR
       "BGP keepalives\n")
{
  if (vty->node == CONFIG_NODE)
    DEBUG_ON_BGPD (keepalive, KEEPALIVE);
  else
    {
      TERM_DEBUG_ON_BGPD (keepalive, KEEPALIVE);
      vty_out (vty, "BGP keepalives debugging is on%s", VTY_NEWLINE);
    }
  return CMD_SUCCESS;
}
#define	debug_bgp_keepalive_cmd	debug_bgp_keepalive_cmd__VAR

#undef	no_debug_bgp_keepalive_cmd
DEFUN (no_debug_bgp_keepalive,
       no_debug_bgp_keepalive_cmd,
       "no debug bgp keepalives",
       NO_STR
       DEBUG_STR
       BGP_STR
       "BGP keepalives\n")
{
  if (vty->node == CONFIG_NODE)
    DEBUG_OFF_BGPD (keepalive, KEEPALIVE);
  else
    {
      TERM_DEBUG_OFF_BGPD (keepalive, KEEPALIVE);
      vty_out (vty, "BGP keepalives debugging is off%s", VTY_NEWLINE);
    }
  return CMD_SUCCESS;
}
#define	no_debug_bgp_keepalive_cmd	no_debug_bgp_keepalive_cmd__VAR

#undef	undebug_bgp_keepalive_cmd
ALIAS (no_debug_bgp_keepalive,
       undebug_bgp_keepalive_cmd,
       "undebug bgp keepalives",
       UNDEBUG_STR
       BGP_STR
       "BGP keepalives\n");
#define	undebug_bgp_keepalive_cmd	undebug_bgp_keepalive_cmd__VAR

#undef	debug_bgp_update_cmd
DEFUN (debug_bgp_update,
       debug_bgp_update_cmd,
       "debug bgp updates",
       DEBUG_STR
       BGP_STR
       "BGP updates\n")
{
  if (vty->node == CONFIG_NODE)
    {
      DEBUG_ON_BGPD (update, UPDATE_IN);
      DEBUG_ON_BGPD (update, UPDATE_OUT);
    }
  else
    {
      TERM_DEBUG_ON_BGPD (update, UPDATE_IN);
      TERM_DEBUG_ON_BGPD (update, UPDATE_OUT);
      vty_out (vty, "BGP updates debugging is on%s", VTY_NEWLINE);
    }
  return CMD_SUCCESS;
}
#define	debug_bgp_update_cmd	debug_bgp_update_cmd__VAR

#undef	debug_bgp_update_direct_cmd
DEFUN (debug_bgp_update_direct,
       debug_bgp_update_direct_cmd,
       "debug bgp updates (in|out)",
       DEBUG_STR
       BGP_STR
       "BGP updates\n"
       "Inbound updates\n"
       "Outbound updates\n")
{
  if (vty->node == CONFIG_NODE)
    {
      if (strncmp ("i", argv[0], 1) == 0)
	{
	  DEBUG_OFF_BGPD (update, UPDATE_OUT);
	  DEBUG_ON_BGPD (update, UPDATE_IN);
	}
      else
	{	
	  DEBUG_OFF_BGPD (update, UPDATE_IN);
	  DEBUG_ON_BGPD (update, UPDATE_OUT);
	}
    }
  else
    {
      if (strncmp ("i", argv[0], 1) == 0)
	{
	  TERM_DEBUG_OFF_BGPD (update, UPDATE_OUT);
	  TERM_DEBUG_ON_BGPD (update, UPDATE_IN);
	  vty_out (vty, "BGP updates debugging is on (inbound)%s", VTY_NEWLINE);
	}
      else
	{
	  TERM_DEBUG_OFF_BGPD (update, UPDATE_IN);
	  TERM_DEBUG_ON_BGPD (update, UPDATE_OUT);
	  vty_out (vty, "BGP updates debugging is on (outbound)%s", VTY_NEWLINE);
	}
    }
  return CMD_SUCCESS;
}
#define	debug_bgp_update_direct_cmd	debug_bgp_update_direct_cmd__VAR

#undef	no_debug_bgp_update_cmd
DEFUN (no_debug_bgp_update,
       no_debug_bgp_update_cmd,
       "no debug bgp updates",
       NO_STR
       DEBUG_STR
       BGP_STR
       "BGP updates\n")
{
  if (vty->node == CONFIG_NODE)
    {
      DEBUG_OFF_BGPD (update, UPDATE_IN);
      DEBUG_OFF_BGPD (update, UPDATE_OUT);
    }
  else
    {
      TERM_DEBUG_OFF_BGPD (update, UPDATE_IN);
      TERM_DEBUG_OFF_BGPD (update, UPDATE_OUT);
      vty_out (vty, "BGP updates debugging is off%s", VTY_NEWLINE);
    }
  return CMD_SUCCESS;
}
#define	no_debug_bgp_update_cmd	no_debug_bgp_update_cmd__VAR

#undef	undebug_bgp_update_cmd
ALIAS (no_debug_bgp_update,
       undebug_bgp_update_cmd,
       "undebug bgp updates",
       UNDEBUG_STR
       BGP_STR
       "BGP updates\n");
#define	undebug_bgp_update_cmd	undebug_bgp_update_cmd__VAR

#undef	debug_bgp_normal_cmd
DEFUN (debug_bgp_normal,
       debug_bgp_normal_cmd,
       "debug bgp",
       DEBUG_STR
       BGP_STR)
{
  if (vty->node == CONFIG_NODE)
    DEBUG_ON_BGPD (normal, NORMAL);
  else
    {
      TERM_DEBUG_ON_BGPD (normal, NORMAL);
      vty_out (vty, "BGP debugging is on%s", VTY_NEWLINE);
    }
  return CMD_SUCCESS;
}
#define	debug_bgp_normal_cmd	debug_bgp_normal_cmd__VAR

#undef	no_debug_bgp_normal_cmd
DEFUN (no_debug_bgp_normal,
       no_debug_bgp_normal_cmd,
       "no debug bgp",
       NO_STR
       DEBUG_STR
       BGP_STR)
{
  if (vty->node == CONFIG_NODE)
    DEBUG_OFF_BGPD (normal, NORMAL);
  else
    {
      TERM_DEBUG_OFF_BGPD (normal, NORMAL);
      vty_out (vty, "BGP debugging is off%s", VTY_NEWLINE);
    }
  return CMD_SUCCESS;
}
#define	no_debug_bgp_normal_cmd	no_debug_bgp_normal_cmd__VAR

#undef	undebug_bgp_normal_cmd
ALIAS (no_debug_bgp_normal,
       undebug_bgp_normal_cmd,
       "undebug bgp",
       UNDEBUG_STR
       BGP_STR);
#define	undebug_bgp_normal_cmd	undebug_bgp_normal_cmd__VAR

#undef	debug_bgp_zebra_cmd
DEFUN (debug_bgp_zebra,
       debug_bgp_zebra_cmd,
       "debug bgp zebra",
       DEBUG_STR
       BGP_STR
       "BGP Zebra messages\n")
{
  if (vty->node == CONFIG_NODE)
    DEBUG_ON_BGPD (zebra, ZEBRA);
  else
    {
      TERM_DEBUG_ON_BGPD (zebra, ZEBRA);
      vty_out (vty, "BGP zebra debugging is on%s", VTY_NEWLINE);
    }
  return CMD_SUCCESS;
}
#define	debug_bgp_zebra_cmd	debug_bgp_zebra_cmd__VAR

#undef	no_debug_bgp_zebra_cmd
DEFUN (no_debug_bgp_zebra,
       no_debug_bgp_zebra_cmd,
       "no debug bgp zebra",
       NO_STR
       DEBUG_STR
       BGP_STR
       "BGP Zebra messages\n")
{
  if (vty->node == CONFIG_NODE)
    DEBUG_OFF_BGPD (zebra, ZEBRA);
  else
    {
      TERM_DEBUG_OFF_BGPD (zebra, ZEBRA);
      vty_out (vty, "BGP zebra debugging is off%s", VTY_NEWLINE);
    }
  return CMD_SUCCESS;
}
#define	no_debug_bgp_zebra_cmd	no_debug_bgp_zebra_cmd__VAR

#undef	undebug_bgp_zebra_cmd
ALIAS (no_debug_bgp_zebra,
       undebug_bgp_zebra_cmd,
       "undebug bgp zebra",
       UNDEBUG_STR
       DEBUG_STR
       BGP_STR
       "BGP Zebra messages\n");
#define	undebug_bgp_zebra_cmd	undebug_bgp_zebra_cmd__VAR

#undef	no_debug_bgp_all_cmd
DEFUN (no_debug_bgp_all,
       no_debug_bgp_all_cmd,
       "no debug all bgp",
       NO_STR
       DEBUG_STR
       "Enable all debugging\n"
       BGP_STR)
{
  TERM_DEBUG_OFF_BGPD (normal, NORMAL);
  TERM_DEBUG_OFF_BGPD (events, EVENTS);
  TERM_DEBUG_OFF_BGPD (keepalive, KEEPALIVE);
  TERM_DEBUG_OFF_BGPD (update, UPDATE_IN);
  TERM_DEBUG_OFF_BGPD (update, UPDATE_OUT);
  TERM_DEBUG_OFF_BGPD (as4, AS4);
  TERM_DEBUG_OFF_BGPD (as4, AS4_SEGMENT);
  TERM_DEBUG_OFF_BGPD (fsm, FSM);
  TERM_DEBUG_OFF_BGPD (filter, FILTER);
  TERM_DEBUG_OFF_BGPD (zebra, ZEBRA);
  vty_out (vty, "All possible debugging has been turned off%s", VTY_NEWLINE);
      
  return CMD_SUCCESS;
}
#define	no_debug_bgp_all_cmd	no_debug_bgp_all_cmd__VAR

#undef	undebug_bgp_all_cmd
ALIAS (no_debug_bgp_all,
       undebug_bgp_all_cmd,
       "undebug all bgp",
       UNDEBUG_STR
       "Enable all debugging\n"
       BGP_STR);
#define	undebug_bgp_all_cmd	undebug_bgp_all_cmd__VAR

#undef	show_debugging_bgp_cmd
DEFUN (show_debugging_bgp,
       show_debugging_bgp_cmd,
       "show debugging bgp",
       SHOW_STR
       DEBUG_STR
       BGP_STR)
{
  vty_out (vty, "BGP debugging status:%s", VTY_NEWLINE);

  if (BGP_DEBUG (normal, NORMAL))
    vty_out (vty, "  BGP debugging is on%s", VTY_NEWLINE);
  if (BGP_DEBUG (events, EVENTS))
    vty_out (vty, "  BGP events debugging is on%s", VTY_NEWLINE);
  if (BGP_DEBUG (keepalive, KEEPALIVE))
    vty_out (vty, "  BGP keepalives debugging is on%s", VTY_NEWLINE);
  if (BGP_DEBUG (update, UPDATE_IN) && BGP_DEBUG (update, UPDATE_OUT))
    vty_out (vty, "  BGP updates debugging is on%s", VTY_NEWLINE);
  else if (BGP_DEBUG (update, UPDATE_IN))
    vty_out (vty, "  BGP updates debugging is on (inbound)%s", VTY_NEWLINE);
  else if (BGP_DEBUG (update, UPDATE_OUT))
    vty_out (vty, "  BGP updates debugging is on (outbound)%s", VTY_NEWLINE);
  if (BGP_DEBUG (fsm, FSM))
    vty_out (vty, "  BGP fsm debugging is on%s", VTY_NEWLINE);
  if (BGP_DEBUG (filter, FILTER))
    vty_out (vty, "  BGP filter debugging is on%s", VTY_NEWLINE);
  if (BGP_DEBUG (zebra, ZEBRA))
    vty_out (vty, "  BGP zebra debugging is on%s", VTY_NEWLINE);
  if (BGP_DEBUG (as4, AS4))
    vty_out (vty, "  BGP as4 debugging is on%s", VTY_NEWLINE);
  if (BGP_DEBUG (as4, AS4_SEGMENT))
    vty_out (vty, "  BGP as4 aspath segment debugging is on%s", VTY_NEWLINE);
  vty_out (vty, "%s", VTY_NEWLINE);
  return CMD_SUCCESS;
}
#define	show_debugging_bgp_cmd	show_debugging_bgp_cmd__VAR

static int
bgp_config_write_debug (struct vty *vty)
{
  int write = 0;

  if (CONF_BGP_DEBUG (normal, NORMAL))
    {
      vty_out (vty, "debug bgp%s", VTY_NEWLINE);
      write++;
    }

  if (CONF_BGP_DEBUG (as4, AS4))
    {
      vty_out (vty, "debug bgp as4%s", VTY_NEWLINE);
      write++;
    }

  if (CONF_BGP_DEBUG (as4, AS4_SEGMENT))
    {
      vty_out (vty, "debug bgp as4 segment%s", VTY_NEWLINE);
      write++;
    }

  if (CONF_BGP_DEBUG (events, EVENTS))
    {
      vty_out (vty, "debug bgp events%s", VTY_NEWLINE);
      write++;
    }

  if (CONF_BGP_DEBUG (keepalive, KEEPALIVE))
    {
      vty_out (vty, "debug bgp keepalives%s", VTY_NEWLINE);
      write++;
    }

  if (CONF_BGP_DEBUG (update, UPDATE_IN) && CONF_BGP_DEBUG (update, UPDATE_OUT))
    {
      vty_out (vty, "debug bgp updates%s", VTY_NEWLINE);
      write++;
    }
  else if (CONF_BGP_DEBUG (update, UPDATE_IN))
    {
      vty_out (vty, "debug bgp updates in%s", VTY_NEWLINE);
      write++;
    }
  else if (CONF_BGP_DEBUG (update, UPDATE_OUT))
    {
      vty_out (vty, "debug bgp updates out%s", VTY_NEWLINE);
      write++;
    }

  if (CONF_BGP_DEBUG (fsm, FSM))
    {
      vty_out (vty, "debug bgp fsm%s", VTY_NEWLINE);
      write++;
    }

  if (CONF_BGP_DEBUG (filter, FILTER))
    {
      vty_out (vty, "debug bgp filters%s", VTY_NEWLINE);
      write++;
    }

  if (CONF_BGP_DEBUG (zebra, ZEBRA))
    {
      vty_out (vty, "debug bgp zebra%s", VTY_NEWLINE);
      write++;
    }

  return write;
}

struct cmd_node debug_node_bgpd =
{
  DEBUG_NODE,
  "",
  1
};

void
bgp_debug_init (void)
{
  install_node (&debug_node, bgp_config_write_debug);

  install_element (ENABLE_NODE, &show_debugging_bgp_cmd);

  install_element (ENABLE_NODE, &debug_bgp_as4_cmd);
  install_element (CONFIG_NODE, &debug_bgp_as4_cmd);
  install_element (ENABLE_NODE, &debug_bgp_as4_segment_cmd);
  install_element (CONFIG_NODE, &debug_bgp_as4_segment_cmd);

  install_element (ENABLE_NODE, &debug_bgp_fsm_cmd);
  install_element (CONFIG_NODE, &debug_bgp_fsm_cmd);
  install_element (ENABLE_NODE, &debug_bgp_events_cmd);
  install_element (CONFIG_NODE, &debug_bgp_events_cmd);
  install_element (ENABLE_NODE, &debug_bgp_filter_cmd);
  install_element (CONFIG_NODE, &debug_bgp_filter_cmd);
  install_element (ENABLE_NODE, &debug_bgp_keepalive_cmd);
  install_element (CONFIG_NODE, &debug_bgp_keepalive_cmd);
  install_element (ENABLE_NODE, &debug_bgp_update_cmd);
  install_element (CONFIG_NODE, &debug_bgp_update_cmd);
  install_element (ENABLE_NODE, &debug_bgp_update_direct_cmd);
  install_element (CONFIG_NODE, &debug_bgp_update_direct_cmd);
  install_element (ENABLE_NODE, &debug_bgp_normal_cmd);
  install_element (CONFIG_NODE, &debug_bgp_normal_cmd);
  install_element (ENABLE_NODE, &debug_bgp_zebra_cmd);
  install_element (CONFIG_NODE, &debug_bgp_zebra_cmd);

  install_element (ENABLE_NODE, &no_debug_bgp_as4_cmd);
  install_element (ENABLE_NODE, &undebug_bgp_as4_cmd);
  install_element (CONFIG_NODE, &no_debug_bgp_as4_cmd);
  install_element (ENABLE_NODE, &no_debug_bgp_as4_segment_cmd);
  install_element (ENABLE_NODE, &undebug_bgp_as4_segment_cmd);
  install_element (CONFIG_NODE, &no_debug_bgp_as4_segment_cmd);

  install_element (ENABLE_NODE, &no_debug_bgp_fsm_cmd);
  install_element (ENABLE_NODE, &undebug_bgp_fsm_cmd);
  install_element (CONFIG_NODE, &no_debug_bgp_fsm_cmd);
  install_element (ENABLE_NODE, &no_debug_bgp_events_cmd);
  install_element (ENABLE_NODE, &undebug_bgp_events_cmd);
  install_element (CONFIG_NODE, &no_debug_bgp_events_cmd);
  install_element (ENABLE_NODE, &no_debug_bgp_filter_cmd);
  install_element (ENABLE_NODE, &undebug_bgp_filter_cmd);
  install_element (CONFIG_NODE, &no_debug_bgp_filter_cmd);
  install_element (ENABLE_NODE, &no_debug_bgp_keepalive_cmd);
  install_element (ENABLE_NODE, &undebug_bgp_keepalive_cmd);
  install_element (CONFIG_NODE, &no_debug_bgp_keepalive_cmd);
  install_element (ENABLE_NODE, &no_debug_bgp_update_cmd);
  install_element (ENABLE_NODE, &undebug_bgp_update_cmd);
  install_element (CONFIG_NODE, &no_debug_bgp_update_cmd);
  install_element (ENABLE_NODE, &no_debug_bgp_normal_cmd);
  install_element (ENABLE_NODE, &undebug_bgp_normal_cmd);
  install_element (CONFIG_NODE, &no_debug_bgp_normal_cmd);
  install_element (ENABLE_NODE, &no_debug_bgp_zebra_cmd);
  install_element (ENABLE_NODE, &undebug_bgp_zebra_cmd);
  install_element (CONFIG_NODE, &no_debug_bgp_zebra_cmd);
  install_element (ENABLE_NODE, &no_debug_bgp_all_cmd);
  install_element (ENABLE_NODE, &undebug_bgp_all_cmd);
}