#include "Timer.h"

Timer::Timer(void) {
	this->iniciado = false;
	this->ticksIniciales = 0;
}

Timer::~Timer(void)
{
}

void Timer::iniciar(){
	this->iniciado = true;
	this->ticksIniciales = SDL_GetTicks();
}

void Timer::detener(){
	this->iniciado = false;
}

int Timer::getMs(){
	if (this->iniciado) {
		return SDL_GetTicks() - this->ticksIniciales;

	} else {
		return 0;
	}
}

bool Timer::isIniciado(){
	return this->iniciado;
}