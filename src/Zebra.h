#ifndef ZEBRA_H_
#define ZEBRA_H_

#include "Daemon.h"

class Zebra : public Daemon
{
	public:
		virtual void activity();
};

#endif
