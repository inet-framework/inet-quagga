/*
 * Copyright (C) 2003 CTIE, Monash University
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#ifndef MACADDRESS_H_
#define MACADDRESS_H_

#include <string>
#include <omnetpp.h>
#include "INETDefs.h"


#define MAC_ADDRESS_BYTES 6

class InterfaceToken;


/**
 * Stores an IEEE 802 MAC address (6 octets = 48 bits).
 */
class INET_API MACAddress
{
  private:
    unsigned char address[6];   // 6*8=48 bit address
    static unsigned int autoAddressCtr; // global counter for generateAutoAddress()

  public:
    /** Returns the unspecified (null) MAC address */
    static const MACAddress UNSPECIFIED_ADDRESS;

    /** Returns the broadcast (ff:ff:ff:ff:ff:ff) MAC address */
    static const MACAddress BROADCAST_ADDRESS;

    /**
     * Default constructor initializes address bytes to zero.
     */
    MACAddress();

    /**
     * Constructor which accepts hex string or the string "auto".
     */
    MACAddress(const char *hexstr);

    /**
     * Copy constructor.
     */
    MACAddress(const MACAddress& other) {operator=(other);}

    /**
     * Assignment.
     */
    MACAddress& operator=(const MACAddress& other);

    /**
     * Returns 6.
     */
    unsigned int getAddressArraySize() const;

    /**
     * Returns the kth byte of the address.
     */
    unsigned char getAddress(unsigned int k) const;

    /**
     * Sets the kth byte of the address.
     */
    void setAddress(unsigned int k, unsigned char addrbyte);

    /**
     * Converts address value from hex string. The string "auto" is also
     * accepted, it'll generate a unique address starting with "A0 00".
     */
    void setAddress(const char *hexstr);

    /**
     * Returns pointer to internal binary representation of address (array of 6 unsigned chars).
     */
    unsigned char *getAddressBytes() {return address;}

    /**
     * Sets address bytes. The argument should point to an array of 6 unsigned chars.
     */
    void setAddressBytes(unsigned char *addrbytes);

    /**
     * Sets the address to the broadcast address (hex ff:ff:ff:ff:ff:ff).
     */
    void setBroadcast();

    /**
     * Returns true this is the broadcast address (hex ff:ff:ff:ff:ff:ff).
     */
    bool isBroadcast() const;

    /**
     * Returns true this is a multicast logical address (starts with bit 1).
     */
    bool isMulticast() const  {return address[0]&0x80;};

    /**
     * Returns true if all address bytes are zero.
     */
    bool isUnspecified() const;

    /**
     * Converts address to a hex string.
     */
    std::string str() const;

    /**
     * Returns true if the two addresses are equal.
     */
    bool equals(const MACAddress& other) const;

    /**
     * Returns true if the two addresses are equal.
     */
    bool operator==(const MACAddress& other) const {return (*this).equals(other);}

    /**
     * Returns true if the two addresses are not equal.
     */
    bool operator!=(const MACAddress& other) const {return !(*this).equals(other);}

    /**
     * Returns -1, 0 or 1 as result of comparison of 2 addresses.
     */
    int compareTo(const MACAddress& other) const;

    /**
     * Create interface identifier (IEEE EUI-64) which can be used by IPv6
     * stateless address autoconfiguration.
     */
    InterfaceToken formInterfaceIdentifier() const;

    /**
     * Generates a unique address which begins with 0a:aa and ends in a unique
     * suffix.
     */
    static MACAddress generateAutoAddress();

};

inline std::ostream& operator<<(std::ostream& os, const MACAddress& mac)
{
    return os << mac.str();
}

#endif


