/*****************************************************************************
 *
 * Copyright (C) 2002 Uppsala University.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Authors: Bj�rn Wiberg <bjorn.wiberg@home.se>
 *
 *****************************************************************************/

#ifndef _AODV_UU_H
#define _AODV_UU_H

/* Constants for interface queue packet buffering/dropping */
#define IFQ_BUFFER 0
#define IFQ_DROP 1
#define IFQ_DROP_BY_DEST 2
#define PKT_ENC 0x1       /* Packet is encapsulated */
#define PKT_DEC 0x2 /* Packet arrived at GW and has been decapsulated (and
		     * should therefore be routed to the Internet */ 
#define CONFIG_GATEWAY
// #define DEBUG_HELLO

#ifndef NS_PORT
#define NS_PORT
#endif
#ifndef OMNETPP
#define OMNETPP
#endif

#include <netinet/in.h>
#include <arpa/inet.h>

/* This is a C++ port of AODV-UU for ns-2 */
#ifndef NS_PORT
#error "To compile the ported version, NS_PORT must be defined!"
#endif /* NS_PORT */



/* System-dependent datatypes */
/* Needed by some network-related datatypes */
#include "aodv-uu/list.h"
#include "aodv_msg_struct.h"
#include "IPDatagram.h"
#include "InterfaceTableAccess.h"
#include "RoutingTableAccess.h"
#include "RoutingTable.h"
#include "IPvXAddress.h"
#include "ICMPAccess.h"
#include "IPv4InterfaceData.h"
#include "InterfaceTable.h"
#include <omnetpp.h>

#include "aodv-uu/list.h"

/* Forward declaration needed to be able to reference the class */
class AODVUU;

/* Global definitions and lib functions */
#include "aodv-uu/params.h"
#include "aodv-uu/defs.h"

#ifndef IP_BROADCAST 
#define IP_BROADCAST ((u_int32_t) 0xffffffff) 
#endif /* !IP_BROADCAST */

/* Extract global data types, defines and global declarations */
#undef NS_NO_GLOBALS
#define NS_NO_DECLARATIONS

#include "aodv-uu/timer_queue.h"
#include "aodv-uu/aodv_hello.h"
#include "aodv-uu/aodv_rerr.h"
#include "aodv-uu/aodv_rrep.h"
#include "aodv-uu/aodv_rreq.h"
#include "aodv-uu/aodv_socket.h"
#include "aodv-uu/aodv_timeout.h"
#include "aodv-uu/debug.h"
#include "aodv-uu/routing_table.h"
#include "aodv-uu/seek_list.h"
#include "aodv-uu/locality.h"

#include "packet_queue_omnet.h"

#undef NS_NO_DECLARATIONS

/* In omnet we don't care about byte order */
#undef ntohl
#define ntohl(x) x
#undef htonl
#define htonl(x) x
#undef htons
#define htons(x) x
#undef ntohs
#define ntohs(x) x



/* The AODV-UU routing agent class */
class AODVUU : public cSimpleModule {

  private:
  RoutingTable *inet_rt;
  InterfaceTable *inet_ift;
  char nodeName[50];


  ICMPAccess icmpAccess;
  void sendToIp (cMessage *, int, const IPvXAddress& , int ,int ,double);
  void sendToIp (cMessage *, int, const IPvXAddress& , int ,int);

 public:
  static int  log_file_fd;
  static bool log_file_fd_init;
  AODVUU(){is_init =false; log_file_fd_init=false;}
  ~AODVUU();

  void packetFailed(cMessage *p);

 protected:
  bool is_init;
  int startAODVUUAgent();
  void scheduleNextEvent();
  int gettimeofday(struct timeval *, struct timezone *);
  const char *if_indextoname(int, char *);
  IPDatagram *pkt_encapsulate(IPDatagram *, IPAddress);
  IPDatagram *pkt_decapsulate(IPDatagram *);
  virtual void handleMessage(cMessage *msg);
  virtual void finish(){}

  int numInitStages() const  {return 5;}
  void initialize(int stage);

  cMessage * sendMessageEvent;
  InterfaceEntry *   interface80211ptr;

  void recvAODVUUPacket(cMessage * p);
  void processPacket(IPDatagram *);

  int initialized;
  int  node_id;
  IPAddress *gateWayAddress;

  int NS_DEV_NR;
  int NS_IFINDEX;
  cModule *ipmod;


/*
  Extract method declarations (and occasionally, variables)
  from header files
*/
#define NS_NO_GLOBALS
#undef NS_NO_DECLARATIONS

#undef _AODV_NEIGHBOR_H
#include "aodv-uu/aodv_neighbor.h"

#undef _AODV_HELLO_H
#include "aodv-uu/aodv_hello.h"

#undef _AODV_RERR_H
#include "aodv-uu/aodv_rerr.h"

#undef _AODV_RREP_H
#include "aodv-uu/aodv_rrep.h"

#undef _AODV_RREQ_H
#include "aodv-uu/aodv_rreq.h"

#undef _AODV_SOCKET_H
#include "aodv-uu/aodv_socket.h"

#undef _AODV_TIMEOUT_H
#include "aodv-uu/aodv_timeout.h"

#undef _DEBUG_H
#include "aodv-uu/debug.h"

#undef _ROUTING_TABLE_H
#include "aodv-uu/routing_table.h"

#undef _SEEK_LIST_H
#include "aodv-uu/seek_list.h"

#undef _TIMER_QUEUE_H
#include "aodv-uu/timer_queue.h"

#undef _LOCALITY_H
#include "aodv-uu/locality.h"

#undef _PACKET_QUEUE_H
#include "packet_queue_omnet.h"

#undef NS_NO_GLOBALS

  /* (Previously global) variables from main.c */
  int log_to_file;
  int rt_log_interval;
  int unidir_hack;
  int rreq_gratuitous;
  int expanding_ring_search;
  int internet_gw_mode;
  int local_repair;
  int receive_n_hellos;
  int hello_jittering;
  int optimized_hellos;
  int ratelimit;
  int llfeedback;
  char *progname;
  int wait_on_reboot;
  struct timer worb_timer;

  /* Parameters that are dynamic configuration values: */
  int active_route_timeout;
  int ttl_start;
  int delete_period;

  /* From aodv_hello.c */
  struct timer hello_timer;

/* From aodv_rreq.c */
  list_t rreqRecords;
#define rreq_records this->rreqRecords

  list_t rreqBlacklist;
#define  rreq_blacklist this->rreqBlacklist

  /* From seek_list.c */
  list_t seekHead;
#define seekhead this->seekHead

/* From timer_queue.c */
  list_t timeList;
#define TQ this->timeList

  /* From debug.c */
 // int  log_file_fd;
  int log_rt_fd;
  int log_nmsgs;
  int debug;
  struct timer rt_log_timer;


  /* From defs.h */
  struct host_info this_host;

  struct dev_info dev_ifindex (int);
  struct dev_info dev_nr(int);



  unsigned int dev_indices[MAX_NR_INTERFACES];
//  inline int ifindex2devindex(unsigned int ifindex);
  int ifindex2devindex(unsigned int ifindex);
  


  int numSent;
};

#if 0
/* From defs.h (needs the AODVUU class declaration) */
inline int NS_CLASS ifindex2devindex(unsigned int ifindex)
{
  int i;

  for (i = 0; i < this_host.nif; i++)
	if (dev_indices[i] == ifindex)
	  return i;

  return -1;
}

#endif

#endif /* AODV_UU_H */
