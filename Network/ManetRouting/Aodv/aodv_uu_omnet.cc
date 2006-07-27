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
 * Authors: Björn Wiberg <bjorn.wiberg@home.se>
 *          Erik Nordström <erik.nordstrom@it.uu.se>
 *
 *****************************************************************************/

#include <string.h>
#include <assert.h>
#include "aodv_uu_omnet.h"

#include "UDPPacket.h"
#include "IPControlInfo.h"
#include "IPv6ControlInfo.h"
#include "ICMPMessage_m.h"
#include "ICMPAccess.h"


#include "ProtocolMap.h"
#include "IPAddress.h"
#include "IPvXAddress.h"
#include "ControlManetRouting.h"


const int UDP_HEADER_BYTES = 8;
typedef std::vector<IPAddress> IPAddressVector;

Define_Module(AODVUU);

/* Constructor for the AODVUU routing agent */



bool AODVUU::log_file_fd_init=false;
int AODVUU::log_file_fd = -1; 

void NS_CLASS initialize(int stage)
{
	list_t *lista_ptr;
	/*
	   Enable usage of some of the configuration variables from Tcl.

	   Note: Do NOT change the values of these variables in the constructor
	   after binding them! The desired default values should be set in
	   ~ns/tcl/lib/ns-default.tcl instead.
	 */
   if (stage==1)
   {
        log_to_file = 0;
        hello_jittering = 0;
        optimized_hellos = 0;
        expanding_ring_search = 0;
        local_repair = 0;
        debug=0;
        rreq_gratuitous =0;
   }
   if (stage==4)
   {
       
    	sendMessageEvent = new cMessage("sendMessageEvent");

        if ((bool)par("log_to_file"))
	     log_to_file = 1;

        if ((bool) par("hello_jittering"))
            hello_jittering = 1;

        if ((bool)par("optimized_hellos"))
            optimized_hellos  = 1;

        if ((bool)par("expanding_ring_search"))
            expanding_ring_search = 1;

        if ((bool) par("local_repair"))
            local_repair = 1;

        if ((bool)par("rreq_gratuitous"))
            rreq_gratuitous = 1;

        if ((bool)par("debug"))
            debug = 1;

	unidir_hack = (int) par("unidir_hack");

	receive_n_hellos	= (int) par("receive_n_hellos");

	wait_on_reboot = (int)	par ("wait_on_reboot");

	rt_log_interval = (int)	par("rt_log_interval");	// Note: in milliseconds!

	ratelimit = (int)	par("ratelimit");
	llfeedback = (int)	par("llfeedback");
	internet_gw_mode	= (int) par("internet_gw_mode");
	gateWayAddress = new IPAddress(par("internet_gw_address").stringValue());



	if (llfeedback) {
		active_route_timeout = ACTIVE_ROUTE_TIMEOUT_LLF;
		ttl_start = TTL_START_LLF;
		delete_period =  DELETE_PERIOD_LLF;
	} else {
		active_route_timeout = (int) par("active_timeout");// ACTIVE_ROUTE_TIMEOUT_HELLO;
		ttl_start = TTL_START_HELLO;
		delete_period = DELETE_PERIOD_HELLO;
	}

	/* From main.c */
	progname = strdup("AODV-UU");
	/* From debug.c */
	/* Note: log_nmsgs was never used anywhere */
  	log_nmsgs = 0;

	log_rt_fd = -1;

        if (debug && !log_file_fd_init)
        {
 	log_file_fd = -1;
          openlog("aodv-uu ",0,LOG_USER);
          log_init();
          log_file_fd_init=true;
        }
  /* Set host parameters */
	memset(&this_host, 0, sizeof(struct host_info));
	memset(dev_indices, 0, sizeof(unsigned int) * MAX_NR_INTERFACES);
	this_host.seqno = 1;
	this_host.rreq_id = 0;
	this_host.nif = 1;
 
	inet_rt = RoutingTableAccess ().get();
	inet_ift = InterfaceTableAccess ().get();

	/* Search the 80211 interface */
	int  num_80211=0;
	InterfaceEntry *   ie;
	InterfaceEntry *   interface;
	const char *name;
	for (int i = 0; i < inet_ift->numInterfaces(); i++)
	{
		ie = inet_ift->interfaceAt(i);
		name = ie->name();
		if (strstr (name,"wlan")!=NULL)
		{
			interface = ie;
			num_80211++;
  			NS_DEV_NR=i;
			NS_IFINDEX=i;
		}
	}
   // One enabled network interface (in total)
	if (num_80211==1)
		interface80211ptr=interface;
	else
		opp_error ("Aodv has found %i 80211 interfaces",num_80211);

	for (int i = 0; i < MAX_NR_INTERFACES; i++) 
	{
		DEV_NR(i).enabled=0;
	}
    /* Set network interface parameters */
	DEV_NR(NS_DEV_NR).enabled = 1;
	DEV_NR(NS_DEV_NR).sock = -1;
	DEV_NR(NS_DEV_NR).ifindex = NS_IFINDEX;
	dev_indices[NS_DEV_NR] = NS_IFINDEX;
	strcpy(DEV_NR(NS_DEV_NR).ifname, interface80211ptr->name());

	DEV_NR(NS_DEV_NR).netmask.s_addr = interface80211ptr->ipv4()->inetAddress().getNetworkMask().getInt();
	DEV_NR(NS_DEV_NR).ipaddr.s_addr = interface80211ptr->ipv4()->inetAddress().getInt();
	DEV_NR(NS_DEV_NR).broadcast.s_addr = AODV_BROADCAST;
        
        lista_ptr=&rreq_records; 
	INIT_LIST_HEAD(&rreq_records);
        lista_ptr=&rreq_blacklist; 
	INIT_LIST_HEAD(&rreq_blacklist);
        lista_ptr=&seekhead; 
	INIT_LIST_HEAD(&seekhead);
        lista_ptr=&TQ; 
	INIT_LIST_HEAD(&TQ);

	/* Initialize data structures */
	worb_timer.data = NULL;
	worb_timer.used = 0;
	hello_timer.data = NULL;
	hello_timer.used = 0;
	rt_log_timer.data = NULL;
	rt_log_timer.used = 0;
	numSent=0;

        strcpy(nodeName,parentModule()->parentModule()->fullName());

	aodv_socket_init();
	rt_table_init();
	packet_queue_init();
	startAODVUUAgent();

	cGate *manetgate = gate("to_ip");
	if (manetgate->toGate()->toGate()->isConnected())
	{
		//cGate *gate = manetgate->toGate()->toGate()->toGate();
//                ipmod = gate->ownerModule();
                ipmod = manetgate->destinationGate()->ownerModule();
        	icmpAccess.get(ipmod);
	}
	else
		opp_error ("Aodv has not found ip module");

        is_init=true;
// Initialize the timer
        scheduleNextEvent();
}
}

/* Destructor for the AODV-UU routing agent */
NS_CLASS ~ AODVUU()
{
	rt_table_destroy();
	log_cleanup();
	delete sendMessageEvent;
	delete gateWayAddress;
}

/*
  Link layer callback function.
  Used when link layer packet delivery fails.
*/
static void link_layer_callback(cMessage *p,void *arg)
{
	((AODVUU *) arg)->packetFailed(p);
}

/*
  Moves pending packets with a certain next hop from the interface
  queue to the packet buffer or simply drops it.
*/

/* Called for packets whose delivery fails at the link layer */
void NS_CLASS packetFailed(cMessage *msg)
{
	IPDatagram *dgram;
	rt_table_t *rt_next_hop, *rt;
	struct in_addr dest_addr, src_addr, next_hop;
	if (dynamic_cast<IPDatagram *>(msg)) {
		dgram = check_and_cast<IPDatagram *>(msg);
	}
	else
	{
		delete  msg;
		return;
	}
        bool isLocal=false;

 	src_addr.s_addr = dgram->srcAddress().getInt();
	dest_addr.s_addr = dgram->destAddress().getInt();
 	InterfaceEntry *   ie;

	for (int i = 0; i <inet_ift->numInterfaces(); i++)
	{
		ie = inet_ift->interfaceAt(i);
		IPv4InterfaceData *ipv4data = ie->ipv4();
		if (ipv4data->inetAddress().getInt()== src_addr.s_addr)
		{
			isLocal=true;

		}
	}
	DEBUG(LOG_DEBUG, 0, "Got failure callback");
	/* We don't care about link failures for broadcast or non-data packets */
	if (dgram->destAddress().getInt() == IP_BROADCAST ||
		dgram->destAddress().getInt() == AODV_BROADCAST) {
		delete msg;
		DEBUG(LOG_DEBUG, 0, "Ignoring callback");
		scheduleNextEvent();
		return;
	}


	DEBUG(LOG_DEBUG, 0, "LINK FAILURE for next_hop=%s dest=%s uid=%d",
	  ip_to_str(next_hop), ip_to_str(dest_addr), ch->uid());

	if (seek_list_find(dest_addr)) {
		DEBUG(LOG_DEBUG, 0, "Ongoing route discovery, buffering packet...");
		packet_queue_add(dgram, dest_addr);
		scheduleNextEvent();
		return;
	}

	
	rt = rt_table_find(dest_addr);


	if (!rt || rt->state == INVALID)
	{
		delete dgram;
		scheduleNextEvent();
		return;
	}

	if (rt->next_hop.s_addr != next_hop.s_addr) {
	DEBUG(LOG_DEBUG, 0, "next hop mismatch - DROPPING pkt");
		delete dgram;
		scheduleNextEvent();
		return;
	}

	/* Do local repair? */
	if (local_repair && rt->hcnt <= MAX_REPAIR_TTL)
	/* && ch->num_forwards() > rt->hcnt */
	 {
		/* Buffer the current packet */
		packet_queue_add(dgram, dest_addr);

// In omnet++ it's not possible to access to the mac queue
//	/* Buffer pending packets from interface queue */
//	interfaceQueue((nsaddr_t) next_hop.s_addr, IFQ_BUFFER);

	/* Mark the route to be repaired */
		rt_next_hop->flags |= RT_REPAIR;
		neighbor_link_break(rt_next_hop);
		rreq_local_repair(rt, src_addr, NULL);

	 }
	 else
	 {
	/* No local repair - just force timeout of link and drop packets */
		neighbor_link_break(rt_next_hop);
		delete dgram;
// In omnet++ it's not possible to access to the mac queue
//	interfaceQueue((nsaddr_t) next_hop.s_addr, IFQ_DROP);
	}
	scheduleNextEvent();
}


/* Entry-level packet reception */
void NS_CLASS handleMessage (cMessage *msg)
{
	AODV_msg *aodvMsg=NULL;
	IPDatagram * ipDgram=NULL;
	UDPPacket * udpPacket=NULL;
	IPControlInfo *controlInfo=NULL;
	cMessage *msg_aux;
        struct in_addr src_addr;
        struct in_addr dest_addr;

        if (is_init==false)
		initialize(0);
	if (msg==sendMessageEvent)
	{
	// timer event
		scheduleNextEvent();
		return;
	}
	/* Handle packet depending on type */
	if (dynamic_cast<ControlManetRouting *>(msg)){
                ControlManetRouting * control =  check_and_cast <ControlManetRouting *> (msg);
                if (control->getOptionCode()== MANET_ROUTE_NOROUTE)
                {
		   ipDgram = (IPDatagram*) control->decapsulate();
		   EV << "Aodv rec datagram  " << ipDgram->name() << " with dest=" << ipDgram->destAddress().str() << "\n";
		   processPacket(ipDgram);   // Data path
                }
                else if (control->getOptionCode()== MANET_ROUTE_UPDATE)
                {
 
                   src_addr.s_addr = control->getSrcAddress().getInt();
                   dest_addr.s_addr = control->getDestAddress().getInt();
                   rt_table_t * fwd_rt = rt_table_find(dest_addr);
                   rt_table_t * rev_rt = rt_table_find(src_addr);
                   rt_table_update_route_timeouts(fwd_rt, rev_rt);
                }
                delete msg;
		scheduleNextEvent();      
		return;
	}
	else if (dynamic_cast<UDPPacket *>(msg))
	{
		udpPacket = check_and_cast<UDPPacket*>(msg);
		if (udpPacket->destinationPort()!= 654)
		{
		   delete  msg;
		   scheduleNextEvent();
		   return;
		}
		msg_aux  = udpPacket->decapsulate();

		if (dynamic_cast<AODV_msg  *>(msg_aux))
		{
			controlInfo = check_and_cast<IPControlInfo*>(udpPacket->removeControlInfo());
			aodvMsg = check_and_cast  <AODV_msg *>(msg_aux);
			src_addr.s_addr = controlInfo->srcAddr().getInt();
			aodvMsg->setControlInfo(controlInfo);
		}
		else
		{
			delete udpPacket;
			delete msg_aux;
			delete controlInfo;
			scheduleNextEvent();
			return;

		}
		delete udpPacket;
	}
	else
	{
		delete msg;
		scheduleNextEvent();
		return;
	}
	/* Detect routing loops */
	if (src_addr.s_addr == inet_rt->routerId().getInt())
	{
		delete controlInfo;
		delete aodvMsg;
		aodvMsg=NULL;
		scheduleNextEvent();
		return;
	}
	recvAODVUUPacket(aodvMsg) ;
	scheduleNextEvent();
}
/*
	case PT_ENCAPSULATED:
	// Decapsulate...
	if (internet_gw_mode) {
		rt_table_t *rev_rt, *next_hop_rt;
		 rev_rt = rt_table_find(saddr);

		 if (rev_rt && rev_rt->state == VALID) {
		 rt_table_update_timeout(rev_rt, ACTIVE_ROUTE_TIMEOUT);

		 next_hop_rt = rt_table_find(rev_rt->next_hop);

		 if (next_hop_rt && next_hop_rt->state == VALID &&
			 rev_rt && next_hop_rt->dest_addr.s_addr != rev_rt->dest_addr.s_addr)
			 rt_table_update_timeout(next_hop_rt, ACTIVE_ROUTE_TIMEOUT);
		 }
		 p = pkt_decapsulate(p);

		 target_->recv(p, (Handler *)0);
		 break;
	}

	processPacket(p);   // Data path
	}
*/



/* Starts the AODV-UU routing agent */
int NS_CLASS startAODVUUAgent()
{

	/* Set up the wait-on-reboot timer */
	if (wait_on_reboot) {
		timer_init(&worb_timer, &NS_CLASS wait_on_reboot_timeout, &wait_on_reboot);
		timer_set_timeout(&worb_timer, DELETE_PERIOD);
		DEBUG(LOG_NOTICE, 0, "In wait on reboot for %d milliseconds.",DELETE_PERIOD);
	}
	/* Schedule the first HELLO */
	if (!llfeedback && !optimized_hellos)
		hello_start();

	/* Initialize routing table logging */
	if (rt_log_interval)
		log_rt_table_init();

	/* Initialization complete */
	initialized = 1;

	DEBUG(LOG_DEBUG, 0, "Routing agent with IP = %s : %d started.",
		  ip_to_str(DEV_NR(NS_DEV_NR).ipaddr), DEV_NR(NS_DEV_NR).ipaddr);

	DEBUG(LOG_DEBUG, 0, "Settings:");
	DEBUG(LOG_DEBUG, 0, "unidir_hack %s", unidir_hack ? "ON" : "OFF");
	DEBUG(LOG_DEBUG, 0, "rreq_gratuitous %s", rreq_gratuitous ? "ON" : "OFF");
	DEBUG(LOG_DEBUG, 0, "expanding_ring_search %s", expanding_ring_search ? "ON" : "OFF");
	DEBUG(LOG_DEBUG, 0, "local_repair %s", local_repair ? "ON" : "OFF");
	DEBUG(LOG_DEBUG, 0, "receive_n_hellos %s", receive_n_hellos ? "ON" : "OFF");
	DEBUG(LOG_DEBUG, 0, "hello_jittering %s", hello_jittering ? "ON" : "OFF");
	DEBUG(LOG_DEBUG, 0, "wait_on_reboot %s", wait_on_reboot ? "ON" : "OFF");
	DEBUG(LOG_DEBUG, 0, "optimized_hellos %s", optimized_hellos ? "ON" : "OFF");
	DEBUG(LOG_DEBUG, 0, "ratelimit %s", ratelimit ? "ON" : "OFF");
	DEBUG(LOG_DEBUG, 0, "llfeedback %s", llfeedback ? "ON" : "OFF");
	DEBUG(LOG_DEBUG, 0, "internet_gw_mode %s", internet_gw_mode ? "ON" : "OFF");
	DEBUG(LOG_DEBUG, 0, "ACTIVE_ROUTE_TIMEOUT=%d", ACTIVE_ROUTE_TIMEOUT);
	DEBUG(LOG_DEBUG, 0, "TTL_START=%d", TTL_START);
	DEBUG(LOG_DEBUG, 0, "DELETE_PERIOD=%d", DELETE_PERIOD);

	/* Schedule the first timeout */
	scheduleNextEvent();
	return 0;

}



// for use with gateway in the future
IPDatagram * NS_CLASS pkt_encapsulate(IPDatagram *p, IPAddress gateway)
{
	IPDatagram *datagram = new IPDatagram(p->name());
	datagram->setByteLength(IP_HEADER_BYTES);
	datagram->encapsulate(p);

	// set source and destination address
	datagram->setDestAddress(gateway);

	IPAddress src = p->srcAddress();

	// when source address was given, use it; otherwise it'll get the address
	// of the outgoing interface after routing
	// set other fields
	datagram->setDiffServCodePoint(p->diffServCodePoint());
	datagram->setIdentification(p->identification());
	datagram->setMoreFragments(false);
	datagram->setDontFragment (p->dontFragment());
	datagram->setFragmentOffset(0);
	datagram->setTimeToLive(
		   p->timeToLive() > 0 ?
		   p->timeToLive() :
		   0);

	datagram->setTransportProtocol(IP_PROT_IP);
	return datagram;
}



IPDatagram *NS_CLASS pkt_decapsulate(IPDatagram *p)
{

	if (p->transportProtocol() == IP_PROT_IP) {
		IPDatagram *datagram = check_and_cast  <IPDatagram *>(p->decapsulate());
		datagram->setTimeToLive(p->timeToLive());
		delete p;
		return datagram;
	}
	return NULL;
}



/*
  Reschedules the timer queue timer to go off at the time of the
  earliest event (so that the timer queue will be investigated then).
  Should be called whenever something might have changed the timer queue.
*/
void NS_CLASS scheduleNextEvent()
{
	struct timeval *timeout;
	double timer;
	timeout = timer_age_queue();
	if (timeout)
	{
		timer  = (double)(((double)timeout->tv_usec/(double)1000000.0) +
							(double)timeout->tv_sec)+simTime();
		if (sendMessageEvent->isScheduled())
		{
			if (timer < sendMessageEvent->arrivalTime()) {
				cancelEvent(sendMessageEvent);
				scheduleAt(timer, sendMessageEvent);
			}
		}
		else
		{
			scheduleAt(timer, sendMessageEvent);
		}
	}
}


/*
  Replacement for gettimeofday(), used for timers.
  The timeval should only be interpreted as number of seconds and
  fractions of seconds since the start of the simulation.
*/
int NS_CLASS gettimeofday(struct timeval *tv, struct timezone *tz)
{
	double current_time, tmp;
	/* Timeval is required, timezone is ignored */
	if (!tv)
	return -1;
	current_time = simTime();
	tv->tv_sec = (long)current_time; /* Remove decimal part */
	tmp = (current_time - tv->tv_sec) * 1000000;
	tv->tv_usec = (long)tmp;
	return 0;
}


/*
  Replacement for if_indextoname(), used in routing table logging.
*/
const char *NS_CLASS if_indextoname(int ifindex, char *ifname)
{
 	InterfaceEntry *   ie;
	assert(ifindex >= 0);
	ie = inet_ift->interfaceAt(ifindex);
	return ie->name();
}




void NS_CLASS sendToIp (cMessage *msg, int srcPort, const IPvXAddress& destAddr, int destPort,int ttl)
{
     sendToIp (msg,srcPort,destAddr,destPort,ttl,0);
}


void NS_CLASS sendToIp (cMessage *msg, int srcPort, const IPvXAddress& destAddr, int destPort,int ttl,double delay)
{

	UDPPacket *udpPacket = new UDPPacket(msg->name());
	udpPacket->setByteLength(UDP_HEADER_BYTES);
	udpPacket->encapsulate(msg);
	IPvXAddress srcAddr = interface80211ptr->ipv4()->inetAddress();

        if (ttl==0)
        {
        // delete and return 
        delete msg;
        return;
        }
	// set source and destination port
	udpPacket->setSourcePort(srcPort);
	udpPacket->setDestinationPort(destPort);
	
      
	if (!destAddr.isIPv6())
	{
		// send to IPv4
		EV << "Sending app packet " << msg->name() << " over IPv4." << " from " << 
                       srcAddr.get4().str() << " to " << destAddr.get4().str() << "\n";
		IPControlInfo *ipControlInfo = new IPControlInfo();
		//ipControlInfo->setProtocol(IP_PROT_UDP);
		ipControlInfo->setProtocol(IP_PROT_MANET);

		ipControlInfo->setSrcAddr(srcAddr.get4());
		ipControlInfo->setDestAddr(destAddr.get4());

                DEBUG(LOG_DEBUG, 0,
		  "sendToIpSending %s src=%s dest=%s",msg->name()
		   srcAddr.get4().str(),destAddr.get4().str());
                if (destAddr.get4() == IPAddress::ALLONES_ADDRESS)
			ipControlInfo->setInterfaceId(NS_DEV_NR); // If broadcast packet send to interface
		ipControlInfo->setTimeToLive(ttl);
		udpPacket->setControlInfo(ipControlInfo);
		sendDelayed(udpPacket,delay,"to_ip");
	}
	else
	{
		// send to IPv6
		EV << "Sending app packet " << msg->name() << " over IPv6.\n";
		IPv6ControlInfo *ipControlInfo = new IPv6ControlInfo();
		// ipControlInfo->setProtocol(IP_PROT_UDP);
		ipControlInfo->setProtocol(IP_PROT_MANET);
		ipControlInfo->setSrcAddr(srcAddr.get6());
		ipControlInfo->setDestAddr(destAddr.get6());
		ipControlInfo->setHopLimit(ttl);
		// ipControlInfo->setInterfaceId(udpCtrl->InterfaceId()); FIXME extend IPv6 with this!!!
		udpPacket->setControlInfo(ipControlInfo);
		sendDelayed(udpPacket,delay,"to_ipv6");
	}
	numSent++;
}



void NS_CLASS recvAODVUUPacket(cMessage * msg)
{
	struct in_addr src, dst;
	IPControlInfo *ctrl = check_and_cast<IPControlInfo *>(msg->controlInfo());
	IPvXAddress srcAddr = ctrl->srcAddr();
	IPvXAddress destAddr = ctrl->destAddr();
	int ttl =  ctrl->timeToLive();
	src.s_addr = srcAddr.get4().getInt();
	dst.s_addr =  destAddr.get4().getInt();
	AODV_msg *aodv_msg = check_and_cast<AODV_msg *> (msg);
	int len = aodv_msg->byteLength();

	InterfaceEntry *   ie;
	for (int i = 0; i <inet_ift->numInterfaces(); i++)
	{
		ie = inet_ift->interfaceAt(i);
		IPv4InterfaceData *ipv4data = ie->ipv4();
		if (ipv4data->inetAddress().getInt()== src.s_addr)
		{
			delete   aodv_msg;
			return;
		}
	}
	aodv_socket_process_packet(aodv_msg, len, src, dst, ttl, NS_IFINDEX);
	delete   aodv_msg;
}


void NS_CLASS processPacket(IPDatagram * p)
{
	rt_table_t *fwd_rt, *rev_rt;
	struct in_addr dest_addr, src_addr;
	u_int8_t rreq_flags = 0;
	unsigned int ifindex;
	struct ip_data *ipd = NULL;

	ifindex = NS_IFINDEX;	/* Always use ns interface */
	fwd_rt = NULL;		/* For broadcast we provide no next hop */
	ipd = NULL;			/* No ICMP messaging */
        bool isLocal=false;
	IPAddressVector phops;

 	src_addr.s_addr = p->srcAddress().getInt();
	dest_addr.s_addr = p->destAddress().getInt();
 	InterfaceEntry *   ie;

        if(!p->srcAddress().isUnspecified())
        {
	    for (int i = 0; i <inet_ift->numInterfaces(); i++)
	    {
		ie = inet_ift->interfaceAt(i);
		IPv4InterfaceData *ipv4data = ie->ipv4();
		if (ipv4data->inetAddress().getInt()== src_addr.s_addr)
		{
			isLocal=true;

		}
	    }
        }
        else
            isLocal=true;
	ie = inet_ift->interfaceAt(ifindex);
	if (p->transportProtocol()==IP_PROT_TCP)
		rreq_flags |= RREQ_GRATUITOUS;

	/* If this is a TCP packet and we don't have a route, we should
	   set the gratuituos flag in the RREQ. */
        phops = ie->ipv4()->multicastGroups();
	IPAddress mcastAdd;
	bool isMcast=false;
        for (unsigned int  i=0;i<phops.size();i++){
		mcastAdd = phops[i];
		if (dest_addr.s_addr == mcastAdd.getInt())
			isMcast=true;
	}


	/* If the packet is not interesting we just let it go through... */
	if (dest_addr.s_addr == AODV_BROADCAST ||isMcast) {
		send(p,"to_ip_from_network");
		return;
	}
	/* Find the entry of the neighboring node and the destination  (if any). */
	rev_rt = rt_table_find(src_addr);
	fwd_rt = rt_table_find(dest_addr);

#ifdef CONFIG_GATEWAY
	/* Check if we have a route and it is an Internet destination (Should be
	 * encapsulated and routed through the gateway). */
	if (fwd_rt && (fwd_rt->state == VALID) &&
	(fwd_rt->flags & RT_INET_DEST)) {
	/* The destination should be relayed through the IG */

		rt_table_update_timeout(fwd_rt, ACTIVE_ROUTE_TIMEOUT);

		p = pkt_encapsulate(p, *gateWayAddress);
	
		if (p == NULL) {
			DEBUG(LOG_ERR, 0, "IP Encapsulation failed!");
		   return;
		}
	/* Update pointers to headers */
		dest_addr.s_addr = gateWayAddress->getInt();
		fwd_rt = rt_table_find(dest_addr);
	}
#endif /* CONFIG_GATEWAY */

	/* UPDATE TIMERS on active forward and reverse routes...  */
	rt_table_update_route_timeouts(fwd_rt, rev_rt);

	/* OK, the timeouts have been updated. Now see if either: 1. The
	   packet is for this node -> ACCEPT. 2. The packet is not for this
	   node -> Send RERR (someone want's this node to forward packets
	   although there is no route) or Send RREQ. */

	if (!fwd_rt || fwd_rt->state == INVALID ||
	(fwd_rt->hcnt == 1 && (fwd_rt->flags & RT_UNIDIR))) {

	/* Check if the route is marked for repair or is INVALID. In
	 * that case, do a route discovery. */
		if (fwd_rt && (fwd_rt->flags & RT_REPAIR)|| isLocal)
			goto route_discovery;

		struct in_addr rerr_dest;
		RERR *rerr;

		DEBUG(LOG_DEBUG, 0,
		  "No route, src=%s dest=%s prev_hop=%s - DROPPING!",
		  ip_to_str(src_addr), ip_to_str(dest_addr));

		if (fwd_rt) {
			rerr = rerr_create(0, fwd_rt->dest_addr,fwd_rt->dest_seqno);
			rt_table_update_timeout(fwd_rt, DELETE_PERIOD);
		} 
		else
			rerr = rerr_create(0, dest_addr, 0);

		DEBUG(LOG_DEBUG, 0, "Sending RERR to prev hop %s for unknown dest %s", 
						ip_to_str(src_addr), ip_to_str(dest_addr));

	    /* Unicast the RERR to the source of the data transmission
	     * if possible, otherwise we broadcast it. */
	    
	    	if (rev_rt && rev_rt->state == VALID)
			rerr_dest = rev_rt->next_hop;
	    	else
			rerr_dest.s_addr = AODV_BROADCAST;

		aodv_socket_send((AODV_msg *) rerr, rerr_dest,RERR_CALC_SIZE(rerr), 
					1, &DEV_IFINDEX(ifindex));
		if (wait_on_reboot) {
			DEBUG(LOG_DEBUG, 0, "Wait on reboot timer reset.");
			timer_set_timeout(&worb_timer, DELETE_PERIOD);
	    	}

	    /* DEBUG(LOG_DEBUG, 0, "Dropping pkt uid=%d", ch->uid()); */
	//	icmpAccess.get()->sendErrorMessage(p, ICMP_DESTINATION_UNREACHABLE, 0);
    		return;
	

      	route_discovery:
	/* Buffer packets... Packets are queued by the ip_queue.o
	   module already. We only need to save the handle id, and
	   return the proper verdict when we know what to do... */

		packet_queue_add(p, dest_addr);

		if (fwd_rt && (fwd_rt->flags & RT_REPAIR))
	    		rreq_local_repair(fwd_rt, src_addr, ipd);
		else
	    		rreq_route_discovery(dest_addr, rreq_flags, ipd);

		return;

    	} 
	else {
	/* DEBUG(LOG_DEBUG, 0, "Sending pkt uid=%d", ch->uid()); */
		send(p,"to_ip");
	/* When forwarding data, make sure we are sending HELLO messages */
		gettimeofday(&this_host.fwd_time, NULL);

		if (!llfeedback && optimized_hellos)
		    hello_start();
	    }
}


struct dev_info NS_CLASS dev_ifindex (int ifindex)
{
 int index = ifindex2devindex(ifindex);
 return  (this_host.devs[index]);

}

struct dev_info NS_CLASS dev_nr(int n)
{
         return (this_host.devs[n]);
}

int NS_CLASS ifindex2devindex(unsigned int ifindex)
{
  int i;

  for (i = 0; i < this_host.nif; i++)
	if (dev_indices[i] == ifindex)
	  return i;

  return -1;
}
