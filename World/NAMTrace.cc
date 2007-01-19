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

#include "NAMTrace.h"
#include <errno.h>
#include "platdep/platmisc.h"

Define_Module(NAMTrace);

NAMTrace::NAMTrace()
{
    nams = NULL;
}

NAMTrace::~NAMTrace()
{
    if (nams)
    {
        nams->close();
        delete nams;
    }
}

void NAMTrace::initialize()
{
    lastnamid = 0;
    nams = NULL;
    const char *namlog = par("logfile");
    if (namlog && namlog[0])
    {
        EV << "nam tracing enabled (file " << namlog << ")" << endl;

        // open namlog for write
        if (unlink(namlog)!=0 && errno!=ENOENT)
            error("cannot remove old `%s' file: %s", namlog, strerror(errno));
        nams = new std::ofstream;
        nams->open(namlog, std::ios::out);
        if (nams->fail())
            error("cannot open `%s' for write", namlog);

        // print prolog into the file
        const char *prolog = par("prolog");
        if (strlen(prolog))
        {
            cStringTokenizer tokenizer(prolog, ";");
            const char *token;
            while((token = tokenizer.nextToken())!=NULL)
                    *nams << token << endl;
            *nams << std::flush;
        }
    }
}

void NAMTrace::handleMessage(cMessage *msg)
{
    error("This module doesn't process messages");
}

int NAMTrace::assignNamId(cModule *node, int namid)
{
    // FIXME make sure nobody's using that namid yet
    return modid2namid[node->id()] = namid==-1 ? ++lastnamid : namid;
}

int NAMTrace::getNamId(cModule *node) const
{
    int modid = node->id();
    std::map<int,int>::const_iterator it = modid2namid.find(modid);
    if (it == modid2namid.end())
        error("getNamId(): assignNamId() on module '%s' not yet called", node->fullPath().c_str());
    return it->second;
}


