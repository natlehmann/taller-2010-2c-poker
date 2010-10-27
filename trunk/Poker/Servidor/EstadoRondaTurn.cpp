#include "EstadoRondaTurn.h"

EstadoRondaTurn::EstadoRondaTurn(EstadoRondaRiver* rondaRiver)
{
	this->setEstadoRondaRiver(rondaRiver);
}

EstadoRondaTurn::~EstadoRondaTurn(void)
{
}

void EstadoRondaTurn::setEstadoRondaRiver(EstadoRondaRiver* rondaRiver){
	this->rondaRiver = rondaRiver;
}

EstadoJuego* EstadoRondaTurn::getSiguienteEstado(){
	return NULL;
}

string EstadoRondaTurn::getEscenarioJuego(int idJugador){
	return "";
}
