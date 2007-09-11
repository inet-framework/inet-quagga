//
// Copyright (C) 2005 Christian Dankbar, Irene Ruengeler, Michael Tuexen, Andras Varga
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//

#include "headers/defs.h"
namespace INETFw // load headers into a namespace, to avoid conflicts with platform definitions of the same stuff
{
#include "headers/bsdint.h"
#include "headers/in.h"
#include "headers/in_systm.h"
#include "headers/udp.h"
};

#include "UDPSerializer.h"

#ifndef _MSC_VER
#include <netinet/in.h>  // htonl, ntohl, ...
#endif


using namespace INETFw;


int UDPSerializer::serialize(UDPPacket *pkt, unsigned char *buf, unsigned int bufsize)
{
    struct udphdr *udphdr = (struct udphdr *) (buf);
    int packetLength;

	packetLength = pkt->byteLength();
	udphdr->uh_sport = htons(pkt->sourcePort());
	udphdr->uh_dport = htons(pkt->destinationPort());
	udphdr->uh_ulen  = htons(packetLength);
    udphdr->uh_sum   = checksum(buf, packetLength);
    return packetLength;
}

void UDPSerializer::parse(unsigned char *buf, unsigned int bufsize, UDPPacket *dest)
{
 
 	struct udphdr *udphdr = (struct udphdr*) buf;

	dest->setSourcePort(ntohs(udphdr->uh_sport));
	dest->setDestinationPort(ntohs(udphdr->uh_dport));
	dest->setByteLength(8);
	cMessage *encapPacket = new cMessage("Payload-from-wire");
	encapPacket->setByteLength(ntohs(udphdr->uh_ulen) - sizeof(struct udphdr));
    dest->encapsulate(encapPacket);
    dest->setName(encapPacket->name());
}

unsigned short UDPSerializer::checksum(unsigned char *addr, unsigned int count)
{
    long sum = 0;

    while (count > 1)  {
        sum += *((unsigned short *&)addr)++;
        if (sum & 0x80000000)
            sum = (sum & 0xFFFF) + (sum >> 16);
        count -= 2;
    }

    if (count)
        sum += *(unsigned char *)addr;

    while (sum >> 16)
        sum = (sum & 0xffff) + (sum >> 16);

    return ~sum;
}
