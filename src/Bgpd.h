#ifndef BGPD_H_
#define BGPD_H_

#include "Daemon.h"

class Bgpd : public Daemon
{
	public:
		virtual void activity();
};


#endif
