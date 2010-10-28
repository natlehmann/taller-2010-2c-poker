#include "TimerServidor.h"

TimerServidor::TimerServidor(void)
{
}

TimerServidor::~TimerServidor(void)
{
}

void TimerServidor::iniciar(){
	time (&this->tiempoInicial);
}

int TimerServidor::getSegundos(){

	time_t tiempoFinal;
	time (&tiempoFinal);
	return (int)(difftime(tiempoFinal, this->tiempoInicial));
}
