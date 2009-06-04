#ifndef OSPFD_H_
#define OSPFD_H_

#include "Daemon.h"

class Ospfd : public Daemon
{
	public:
		virtual void activity();
};

#endif
