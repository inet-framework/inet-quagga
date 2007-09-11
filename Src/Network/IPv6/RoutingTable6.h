//
// Copyright (C) 2005 Andras Varga
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

#ifndef __ROUTINGTABLE6_H
#define __ROUTINGTABLE6_H

#include <vector>
#include <omnetpp.h>
#include "INETDefs.h"
#include "IPv6Address.h"
#include "InterfaceTable.h"


/**
 * Represents a route in the route table. Routes with src=FROM_RA represent
 * on-link prefixes advertised by routers.
 */
class INET_API IPv6Route : public cPolymorphic
{
  public:
    /** Specifies where the route comes from */
    enum RouteSrc
    {
        FROM_RA,        ///< on-link prefix, from Router Advertisement
        OWN_ADV_PREFIX, ///< on routers: on-link prefix that the router **itself** advertises on the link
        STATIC,         ///< static route
        ROUTING_PROT, ///< route is managed by a routing protocol (OSPF,BGP,etc)
    };

  private:
    IPv6Address _destPrefix;
    short _length;
    RouteSrc _src;
    int _interfaceID;
    IPv6Address _nextHop; // unspecified means "direct"
    simtime_t _expiryTime; // if route is an advertised prefix: prefix lifetime
    int _metric;

  public:
    /**
     * Constructor. The destination prefix and the route source is passed
     * to the constructor and cannot be changed afterwards.
     */
    IPv6Route(IPv6Address destPrefix, int length, RouteSrc src) {
        _destPrefix = destPrefix;
        _length = length;
        _src = src;
        _interfaceID = -1;
        _expiryTime = 0;
        _metric = 0;
    }

    virtual std::string info() const;
    virtual std::string detailedInfo() const;
    static const char *routeSrcName(RouteSrc src);

    void setInterfaceID(int interfaceId)  {_interfaceID = interfaceId;}
    void setNextHop(const IPv6Address& nextHop)  {_nextHop = nextHop;}
    void setExpiryTime(simtime_t expiryTime)  {_expiryTime = expiryTime;}
    void setMetric(int metric)  {_metric = _metric;}

    const IPv6Address& destPrefix() const {return _destPrefix;}
    int prefixLength() const  {return _length;}
    RouteSrc src() const  {return _src;}
    int interfaceID() const  {return _interfaceID;}
    const IPv6Address& nextHop() const  {return _nextHop;}
    simtime_t expiryTime() const  {return _expiryTime;}
    int metric() const  {return _metric;}
};


/**
 * Represents the IPv6 routing table and neighbour discovery data structures.
 * This object has one instance per host or router.
 *
 * See the NED documentation for general overview.
 *
 * This is a simple module without gates, it requires function calls to it
 * (message handling does nothing). Methods are provided for reading and
 * updating the interface table and the route table, as well as for unicast
 * and multicast routing.
 *
 * The route table is read from a file. The route table can also
 * be read and modified during simulation, typically by routing protocol
 * implementations.
 */
class INET_API RoutingTable6 : public cSimpleModule
{
  private:
    InterfaceTable *ift; // cached pointer
    bool isrouter;

    // Destination Cache maps dest address to next hop and interfaceId.
    // NOTE: nextHop might be a link-local address from which interfaceId cannot be deduced
    struct DestCacheEntry
    {
        int interfaceId;
        IPv6Address nextHopAddr;
        // more destination specific data may be added here, e.g. path MTU
    };
    friend std::ostream& operator<<(std::ostream& os, const DestCacheEntry& e);
    typedef std::map<IPv6Address,DestCacheEntry> DestCache;
    DestCache destCache;

    // RouteList contains local prefixes, and (for routers)
    // static, OSPF, RIP etc routes as well
    typedef std::vector<IPv6Route*> RouteList;
    RouteList routeList;

  private:
    // internal: routes of different type can only be added via well-defined functions
    void addRoute(IPv6Route *route);
    // helper for addRoute()
    static bool routeLessThan(const IPv6Route *a, const IPv6Route *b);
    // internal
    void configureInterfaceForIPv6(InterfaceEntry *ie);
    /**
     *  RFC 3513: Section 2.8 A Node's Required Address
     *  Assign the various addresses to the node's respective interface. This
     *  should be done when the IPv6 Protocol stack is created.
     */
    void assignRequiredNodeAddresses(InterfaceEntry *ie);
    // internal
    void configureInterfaceFromXML(InterfaceEntry *ie, cXMLElement *cfg);

  protected:
    // displays summary above the icon
    void updateDisplayString();

  public:
    RoutingTable6();
    virtual ~RoutingTable6();

  protected:
    int numInitStages() const  {return 5;}
    void initialize(int stage);
    void parseXMLConfigFile();

    /**
     * Raises an error.
     */
    void handleMessage(cMessage *);

  public:
    /** @name Interfaces */
    //@{
    /**
     * Returns an interface given by its address. Returns NULL if not found.
     */
    InterfaceEntry *interfaceByAddress(const IPv6Address& address);
    //@}

    /**
     * IP forwarding on/off
     */
    bool isRouter()  const {return isrouter;}

    /** @name Routing functions */
    //@{
    /**
     * Checks if the address is one of the host's addresses, i.e.
     * assigned to one of its interfaces (tentatively or not).
     */
    bool localDeliver(const IPv6Address& dest);

    /**
     * Looks up the given destination address in the Destination Cache,
     * then returns the next-hop address and the interface in the outInterfaceId
     * variable. If the destination is not in the cache, outInterfaceId is set to
     * -1 and the unspecified address is returned. The caller should check
     * for interfaceId==-1, because unspecified address is also returned
     * if the link layer doesn't use addresses at all (e.g. PPP).
     *
     * NOTE: outInterfaceId is an OUTPUT parameter -- its initial value is ignored,
     * and the lookupDestCache() sets it to the correct value instead.
     */
    const IPv6Address& lookupDestCache(const IPv6Address& dest, int& outInterfaceId);

    /**
     * Performs longest prefix match in the routing table and returns
     * the resulting route, or NULL if there was no match.
     */
    const IPv6Route *doLongestPrefixMatch(const IPv6Address& dest);

    /**
     * Checks if the given prefix already exists in the routing table (prefix list)
     */
    bool isPrefixPresent(const IPv6Address& prefix);

    //TBD multicast delivery
    //@}

    /** @name Managing the destination cache */
    /**
     * Add or update a destination cache entry.
     */
    void updateDestCache(const IPv6Address& dest, const IPv6Address& nextHopAddr, int interfaceId);

    /**
     * Discard all entries in destination cache
     */
    void purgeDestCache();

    /**
     * Discard all entries in destination cache where next hop is the given
     * address on the given interface. This is typically called when a router
     * becomes unreachable, and all destinations going via that router have to
     * go though router selection again.
     */
    void purgeDestCacheEntriesToNeighbour(const IPv6Address& nextHopAddr, int interfaceId);
    //@}

    /** @name Managing prefixes and the route table */
    //@{
    /**
     * Add on-link prefix (route of type FROM_RA), or update existing one.
     * To be called from code processing on-link prefixes in Router Advertisements.
     * Expiry time can be derived from the Valid Lifetime field
     * in the Router Advertisements.
     *
     * NOTE: This method does NOT update the lifetime of matching addresses
     * in the InterfaceTable (see IPv6InterfaceData); that has to be done
     * separately.
     */
    void addOrUpdateOnLinkPrefix(const IPv6Address& destPrefix, int prefixLength,
                                 int interfaceId, simtime_t expiryTime);

    /**
     * Remove an on-link prefix. To be called when the prefix gets advertised
     * with zero lifetime, or to purge an expired prefix.
     *
     * NOTE: This method does NOT remove the matching addresses from the
     * InterfaceTable (see IPv6InterfaceData); that has to be done separately.
     */
    void removeOnLinkPrefix(const IPv6Address& destPrefix, int prefixLength);

    /**
     * Add route of type OWN_ADV_PREFIX. This is a prefix that *this* router
     * advertises on this interface.
     */
    void addOrUpdateOwnAdvPrefix(const IPv6Address& destPrefix, int prefixLength,
                                 int interfaceId, simtime_t expiryTime);

    /**
     * Creates a static route. If metric is omitted, it gets initialized
     * to the interface's metric value.
     */
    void addStaticRoute(const IPv6Address& destPrefix, int prefixLength,
                        unsigned int interfaceId, const IPv6Address& nextHop,
                        int metric=0);

    /**
     *  Adds a default route for a host. This method requires the RA's source
     *  address and the router expiry time plus the simTime().
     */
    void addDefaultRoute(const IPv6Address& raSrcAddr, unsigned int ifID,
        simtime_t routerLifetime);

    /**
     * Adds the given route (which can be OSPF, BGP, RIP or any other route)
     * with src==ROUTING_PROT. To store additional information with the route,
     * one can subclass from IPv6Route and add more fields.
     */
    void addRoutingProtocolRoute(IPv6Route *route);

    /**
     * Deletes the given route from the route table.
     */
    void removeRoute(IPv6Route *route);

    /**
     * Return the number of routes.
     */
    int numRoutes() const;

    /**
     * Return the ith route.
     */
    IPv6Route *route(int i);
    //@}

};

#endif

