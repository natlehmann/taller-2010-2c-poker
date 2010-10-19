#ifndef _TIMER_H__
#define _TIMER_H__

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "SDL.h"

class Timer
{
private:
	int ticksIniciales;
	bool iniciado;

public:
	Timer(void);
	virtual ~Timer(void);

	void iniciar();
	void detener();

	int getMs();

	bool isIniciado();
};

#endif //_TIMER_H__
