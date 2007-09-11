//
// Copyright (C) 2005 Andras Varga
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

#ifndef __IPv6CONTROLINFO_H
#define __IPv6CONTROLINFO_H

#include "IPv6ControlInfo_m.h"

class IPv6Datagram;

class IPv6ControlInfo : public IPv6ControlInfo_Base
{
  protected:
    IPv6Datagram *dgram;
  public:
    IPv6ControlInfo() : IPv6ControlInfo_Base() {dgram=NULL;}
    ~IPv6ControlInfo();
    IPv6ControlInfo(const IPv6ControlInfo& other) : IPv6ControlInfo_Base() {dgram=NULL; operator=(other);}
    IPv6ControlInfo& operator=(const IPv6ControlInfo& other) {IPv6ControlInfo_Base::operator=(other); return *this;}

    virtual void setOrigDatagram(IPv6Datagram *d);
    virtual IPv6Datagram *removeOrigDatagram();
};

#endif


