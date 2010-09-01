#ifndef LOCK_H_
#define LOCK_H_
#include "server_Mutex.h"

class Lock
{
	private:
		Mutex &m;
	
	public:
		Lock(Mutex &z):m(z){m.lock();};
		~Lock(){m.unlock();};
};

#endif /*LOCK_H_*/
