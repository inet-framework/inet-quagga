//
// Copyright (C) 2001  Vincent Oberle (vincent@oberle.com)
// Institute of Telematics, University of Karlsruhe, Germany.
// University Comillas, Madrid, Spain.
// Copyright (C) 2004 Andras Varga
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//

//
// Author: Vincent Oberle, Jan-March 2001
// Cleanup and rewrite: Andras Varga, 2004
//

#ifndef __IPADDRESS_H
#define __IPADDRESS_H

#include <omnetpp.h>
#include <iostream>
#include <string>
#include "INETDefs.h"


/**
 * String size to hold an address.
 * This is the size of the string that should be used to
 * initialize the IPAddress class, and it is the max length of the string
 * returned by IPAddress::str()
 */
const int ADDRESS_STRING_SIZE = 20;


// FIXME do something (away) with this:
#define IPADDRESS_UNDEF IPAddress()


/**
 * TCP/UDP port number
 */
typedef short PortNumber;

const short PORT_UNDEF = 0;
const short PORT_MAX = 0x7fff;



/**
 * IPv4 address.
 */
class INET_API IPAddress
{
  protected:
    // Coded in the form of 4 numbers, following the format "addr[0].addr[1].addr[2].addr[3]"
    // Example for the address 192.24.65.10: addr[0]=192, addr[1]=24 etc.
    unsigned char addr[4];  // FIXME use a simple uint32 instead

  protected:
    // Only keeps the n first bits of the address, completing it with zeros.
    // Typical usage is when the length of an IP prefix is done and to check
    // the address ends with the right number of 0.
    void keepFirstBits (unsigned int n);

    // Parses IP address into the given bytes, and returns true if syntax was OK.
    static bool parseIPAddress(const char *text, unsigned char tobytes[]);
  public:
    /** @name Predefined addresses */
    //@{
    static const IPAddress UNSPECIFIED_ADDRESS; ///< 0.0.0.0
    static const IPAddress LOOPBACK_ADDRESS;    ///< 127.0.0.1
    static const IPAddress LOOPBACK_NETMASK;    ///< 255.0.0.0
    static const IPAddress ALLONES_ADDRESS;     ///< 255.255.255.255

    static const IPAddress ALL_HOSTS_MCAST;          ///< 224.0.0.1 All hosts on a subnet
    static const IPAddress ALL_ROUTERS_MCAST;        ///< 224.0.0.2 All routers on a subnet
    static const IPAddress ALL_DVMRP_ROUTERS_MCAST;  ///< 224.0.0.4 All DVMRP routers
    static const IPAddress ALL_OSPF_ROUTERS_MCAST;   ///< 224.0.0.5 All OSPF routers (DR Others)
    static const IPAddress ALL_OSPF_DESIGNATED_ROUTERS_MCAST;  ///< 224.0.0.6 All OSPF Designated Routers
    //@}

    /** name Constructors, destructor */
    //@{

    /**
     * Default constructor, initializes to 0.0.0.0.
     */
    IPAddress() {addr[0] = addr[1] = addr[2] = addr[3] = 0;}

    /**
     * IP address as int
     */
    IPAddress(uint32 i);

    /**
     * IP address bytes: "i0.i1.i2.i3" format
     */
    IPAddress(int i0, int i1, int i2, int i3);

    /**
     * IP address given as text: "192.66.86.1"
     */
    IPAddress(const char *t);

    /**
     * Copy constructor
     */
    IPAddress(const IPAddress& obj);

    ~IPAddress() {}
    //@}

    /** name Setting the address */
    //@{
    /**
     * IP address as int
     */
    void set(uint32 i);

    /**
     * IP address bytes: "i0.i1.i2.i3" format
     */
    void set(int i0, int i1, int i2, int i3);

    /**
     * IP address given as text: "192.66.86.1"
     */
    void set(const char *t);
    //@}

    /**
     * Assignment
     */
    IPAddress& operator=(const IPAddress& obj);

    /**
     * True if all four address bytes are zero. The null value is customarily
     * used to represent a missing, unspecified or invalid address in the
     * simulation models.
     */
    bool isUnspecified() const {return !addr[0] && !addr[1] && !addr[2] && !addr[3];}

    /**
     * Returns true if the two addresses are equal
     */
    bool equals(const IPAddress& toCmp) const;

    /**
     * Returns binary AND of the two addresses
     */
    IPAddress doAnd(const IPAddress& ip) const;

    /**
     * Returns the string representation of the address (e.g. "152.66.86.92")
     */
    std::string str() const;

    /**
     * Returns the address as an int.
     */
    uint32 getInt() const;

    /**
     * Returns the corresponding part of the address specified by the index
     * ("[0].[1].[2].[3]")
     */
    int getDByte(int i) const {return addr[i];}

    /**
     * Returns the network class of the address: char 'A', 'B', 'C', 'D', 'E',
     * or '?' (returned when the address begins with at least five 1 bits.)
     */
    char getIPClass() const;

    /**
     * Returns true if this address is in the multicast address range,
     * 224.0.0.0 thru 239.255.255.255, that is, it's a class D address.
     */
    bool isMulticast() const {return (addr[0] & 0xF0)==0xE0;}

    /**
     * Returns true if this address is in the range 224.0.0.0 to 224.0.0.255.
     * These addresses are reserved for local purposes meaning, that routers should
     * not forward these datagrams since the applications that use these addresses
     * do not need the datagrams to go further than one hop.
     */
    bool isLinkLocalMulticast() const {return addr[0]==224 && addr[1]==0 && addr[2]==0;}

    /**
     * Returns an address with the network part of the address (the bits
     * of the hosts part are to 0). For D and E class addresses,
     * it returns a null address.
     */
    IPAddress getNetwork() const;

    /**
     * Returns an address with the network mask corresponding to the
     * address class. For D and E class addresses, it returns a null address.
     */
    IPAddress getNetworkMask() const;

    /**
     * Indicates if the address is from the same network
     */
    bool isNetwork(const IPAddress& toCmp) const;

    /**
     * Compares the first numbits bits of the two addresses.
     */
    bool prefixMatches(const IPAddress& to_cmp, int numbits) const;

    /**
     * Indicates how many bits from the to_cmp address, starting counting
     * from the left, matches the address.
     * E.g. if the address is 130.206.72.237, and to_cmp 130.206.72.0,
     * 24 will be returned.
     *
     * Typical usage for comparing IP prefixes.
     */
    int numMatchingPrefixBits(const IPAddress& to_cmp) const;

    /**
     * Counts 1 bits in a netmask. E.g. for 255.255.254.0, it will return 23.
     */
    int netmaskLength() const;

    /**
     * Test if the masked addresses (ie the mask is applied to addr1 and
     * addr2) are equal.
     */
    static bool maskedAddrAreEqual(const IPAddress& addr1,
                                   const IPAddress& addr2,
                                   const IPAddress& netmask);

    /**
     * Returns equals(addr).
     */
    bool operator==(const IPAddress& addr1) const {return equals(addr1);}

    /**
     * Returns !equals(addr).
     */
    bool operator!=(const IPAddress& addr1) const {return !equals(addr1);}

    /**
     * Compares two IP addresses.
     */
    bool operator<(const IPAddress& addr1) const {return getInt()<addr1.getInt();}

    /**
     * Returns true if the format of the string corresponds to an IP address
     * with the dotted notation ("192.66.86.1"), and false otherwise.
     *
     * This function can be used to verify an IP address string before assigning
     * it to an IPAddress object (both its ctor and set() function raises an
     * error if the string has invalid format.)
     */
    static bool isWellFormed(const char *text);
};

inline std::ostream& operator<<(std::ostream& os, const IPAddress& ip)
{
    return os << ip.str();
}

#endif


