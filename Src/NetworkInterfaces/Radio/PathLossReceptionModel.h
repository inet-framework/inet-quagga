//
// Copyright (C) 2006 Andras Varga
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

#ifndef PATHLOSSRECEPTIONMODEL_H
#define PATHLOSSRECEPTIONMODEL_H

#include "IReceptionModel.h"

/**
 * Path loss model which calculates the received power using a path loss exponent
 * and the distance.
 */
class INET_API PathLossReceptionModel : public IReceptionModel
{
  private:
    double pathLossAlpha;

  public:
    /**
     * Parameters read from the radio module: pathLossAlpha.
     */
    virtual void initializeFrom(cModule *radioModule);

    /**
     * Perform the calculation.
     */
    virtual double calculateReceivedPower(double pSend, double carrierFrequency, double distance);
};

#endif

