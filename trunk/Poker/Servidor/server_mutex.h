#ifndef MUTEX_H_
#define MUTEX_H_
#include <windows.h>

class Mutex
{
	private:
		//pthread_mutex_t m;
	
	public:
		Mutex(){};//pthread_mutex_init(&m, NULL);};
		~Mutex(){};//pthread_mutex_destroy(&m);};
		int lock(){return 0;};//pthread_mutex_lock(&m);};
		int unlock(){return 0;};//pthread_mutex_unlock(&m);};
		
};

#endif /*MUTEX_H_*/
