#ifndef _TIMERSERVIDOR_H__
#define _TIMERSERVIDOR_H__

#include <stdio.h>
#include <time.h>

class TimerServidor
{
private:
	time_t tiempoInicial;

public:
	TimerServidor(void);
	virtual ~TimerServidor(void);

	void iniciar();
	int getSegundos();
};

#endif //_TIMERSERVIDOR_H__

