#ifndef __RIPD_H__
#define	__RIPD_H__

#include "Daemon.h"

class Ripd : public Daemon
{
	public:
		virtual void activity();
};

#endif
