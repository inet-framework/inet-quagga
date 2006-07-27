

#include  <string.h>

#include "aodv_msg_struct.h"
#include "InterfaceTable.h"
#include "UDPPacket.h"
#include "IPControlInfo.h"
#include "IPv6ControlInfo.h"
#include "ICMPMessage_m.h"
#include "IPDatagram_m.h"
#include "RoutingTable.h"
#include "ICMPAccess.h"
#include "IPControlInfo.h"
#include "IPDatagram.h"
#include "ProtocolMap.h"



Register_Class(AODV_msg);


AODV_msg::AODV_msg(const AODV_msg& m) : cPacket()
{
	setName(m.name());
	operator=(m);
}


AODV_msg& AODV_msg::operator=(const AODV_msg& m)
{
	if (this==&m) return *this;

	cPacket::operator=(m);
	type = m.type;
	extensionsize = m.extensionsize;
	if (extensionsize==0) {
		extension =   NULL;
		return *this;
	}
	extension =   new AODV_ext [extensionsize];
	for (int i=0; i < extensionsize; i++)
	{
		 extension[i].type = m.extension[i].type;
		 extension[i].length=m.extension[i].length;
		 extension[i].pointer = new char[extension[i].length];
		 memcpy (extension[i].pointer,m.extension[i].pointer,extension[i].length);
	}
	return *this;
}

void AODV_msg:: clearExtension()
{
	if (extensionsize==0) {
		return;
	}
	for (int i=0; i < extensionsize; i++)
	{
		 delete extension[i].pointer;
	}
	delete [] extension;
	extensionsize=0;
}

AODV_msg::~AODV_msg()
{
	clearExtension();
}

AODV_ext * AODV_msg::addExtension(int type,int len,char *data)
{
	AODV_ext* extension_aux;
	if (len<0) {
		return NULL;
	}
	extension_aux =   new AODV_ext [extensionsize+1];
	for (int i=0; i < extensionsize; i++)
	{
		 extension_aux[i].type = extension[i].type;
		 extension_aux[i].length=extension[i].length;
		 extension_aux[i].pointer = extension[i].pointer;
	}
	delete [] extension;
	extension =  extension_aux;
	extensionsize++;
	extension[extensionsize].type = type;
	extension[extensionsize].length = len;
	extension[extensionsize].pointer  =  new char[len];
	memcpy (extension_aux[extensionsize].pointer,data,len);
	setLength(length ()+((AODV_EXT_HDR_SIZE+len) *8));
	return & extension[extensionsize];
}


AODV_ext * AODV_msg::getNexExtension(AODV_ext* aodv_ext)
{
	if ((extension+extensionsize)>aodv_ext+1)
	   return aodv_ext+1;
	else
	   return NULL;
}

//=== registration
Register_Class(RERR);

//=========================================================================

RERR::RERR(const RERR& m) : AODV_msg()
{
	setName(m.name());
	operator=(m);
}

RERR& RERR::operator=(const RERR& m)
{
	if (this==&m) return *this;

	AODV_msg::operator=(m);
	n = m.n;
	res1= m.res1;
	res2= m.res2;
	dest_count= m.dest_count;
	_udest  = new RERR_udest [dest_count];
	for (int i=0; i < dest_count; i++) {
		 _udest[i].dest_addr = m._udest[i].dest_addr;
		 _udest[i].dest_seqno=m._udest[i].dest_seqno;
	}
	return *this;
}

RERR::~RERR ()
{
	clearUdest();
}

void RERR::addUdest(u_int32_t dest_addr, u_int32_t udest_seqno)
{

	RERR_udest *temp_udest;
	temp_udest = new RERR_udest [dest_count+1];
	for (int i=0; i < dest_count; i++)
	{
		 temp_udest[i].dest_addr = _udest[i].dest_addr;
		 temp_udest[i].dest_seqno= _udest[i].dest_seqno;
	}
	delete []  _udest;
	temp_udest[dest_count].dest_addr = dest_addr;
	temp_udest[dest_count].dest_seqno= udest_seqno;
	_udest= temp_udest;
	dest_count++;
	setLength(length ()+(RERR_UDEST_SIZE*8));
}

RERR_udest * RERR::getUdest(int i)
{
	if (i < dest_count)
	{
		return  &(_udest[i]);
	}
	else
	{
		return NULL;
	}
}

void RERR::clearUdest()
{
	if (_udest!=NULL) {
		delete []  _udest;
	}
	_udest=NULL;
}


Register_Class(RREP);
RREP::RREP(const RREP& m) : AODV_msg()
{
	setName(m.name());
	operator=(m);
}

RREP& RREP::operator=(const RREP& m)
{
	if (this==&m) return *this;
	AODV_msg::operator=(m);
	res1 = m.res1;
	a= m.a;
	r =m.r;
	prefix = m.prefix;
	res2 = m.res2;
	hcnt = m.hcnt;
	dest_addr = m.dest_addr;
	dest_seqno = m.dest_seqno;
	orig_addr = m.orig_addr;
	lifetime = m.lifetime;
	return *this;
}

Register_Class(RREP_ack);
RREP_ack::RREP_ack(const RREP_ack& m) : AODV_msg()
{
	setName(m.name());
	operator=(m);
}

RREP_ack& RREP_ack::operator=(const RREP_ack& m)
{
	if (this==&m) return *this;
	AODV_msg::operator=(m);
	reserved = m.reserved;
	return *this;
}



Register_Class(RREQ);
RREQ::RREQ(const RREQ& m) : AODV_msg()
{
	setName(m.name());
	operator=(m);
}

RREQ& RREQ::operator=(const RREQ& m)
{
	if (this==&m) return *this;
	AODV_msg::operator=(m);
	j=m.j;		/* Join flag (multicast) */
	r=m.r;		/* Repair flag */
	g=m.g;		/* Gratuitous RREP flag */
	d=m.d;		/* Destination only respond */
	res1=m.res1;
	res2=m.res2;
	hcnt=m.hcnt;
	rreq_id=m.rreq_id;
	dest_addr=m.dest_addr;
	dest_seqno=m.dest_seqno;
	orig_addr=m.orig_addr;
	orig_seqno=m.orig_seqno;
	return *this;
}



