//
// Copyright (C) 2000 Institut fuer Telematik, Universitaet Karlsruhe
// Copyright (C) 2004 Andras Varga
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


//
//  Author:     Jochen Reber
//  Date:       18.5.00
//  On Linux:   19.5.00 - 29.5.00
//  Modified by Vincent Oberle
//  Date:       1.2.2001
//  Cleanup and rewrite: Andras Varga, 2004
//


#ifndef __ROUTINGTABLEPARSER_H
#define __ROUTINGTABLEPARSER_H

#include <omnetpp.h>
#include "RoutingTable.h"

/**
 * Parses a routing table file into a routing table.
 */
class INET_API RoutingTableParser
{
  private:
    InterfaceTable *ift;
    RoutingTable *rt;

  public:
    /**
     * Constructor
     */
    RoutingTableParser(InterfaceTable *ift, RoutingTable *rt);

    /**
     * Read Routing Table file; return 0 on success, -1 on error
     */
    int readRoutingTableFromFile (const char *filename);

  private:
    // Parsing functions


    // Used to create specific "files" char arrays without comments or blanks
    // from original file.
    char *createFilteredFile (char *file,
                              int &charpointer,
                              const char *endtoken);

    // Go through the ifconfigFile char array, parse all entries and
    // write them into the interface table.
    // Loopback interface is not part of the file.
    void parseInterfaces(char *ifconfigFile);

    // Go through the routeFile char array, parse all entries line by line and
    // write them into the routing table.
    void parseRouting(char *routeFile);

    char *parseEntry (char *ifconfigFile,
                      const char *tokenStr,
                      int &charpointer,
                      char* destStr);

    // Convert string separated by ':' into dynamic string array.
    void parseMulticastGroups (char *groupStr, InterfaceEntry*);

    // Return 1 if beginning of str1 and str2 is equal up to str2-len,
    // otherwise 0.
    static int streq(const char *str1, const char *str2);

    // Skip blanks in string
    static void skipBlanks (char *str, int &charptr);

    // Copies the first word of src up to a space-char into dest
    // and appends \0, returns position of next space-char in src
    static int strcpyword (char *dest, const char *src);
};


#endif

