#include "EstadoRondaFlop.h"

EstadoRondaFlop::EstadoRondaFlop(EstadoRondaTurn* rondaTurn)
{
	this->setEstadoRondaTurn(rondaTurn);
}

EstadoRondaFlop::~EstadoRondaFlop(void)
{
}

void EstadoRondaFlop::setEstadoRondaTurn(EstadoRondaTurn* rondaTurn){
	this->rondaTurn = rondaTurn;
}

EstadoJuego* EstadoRondaFlop::getSiguienteEstado(){
	return NULL;
}

string EstadoRondaFlop::getEscenarioJuego(int idJugador){
	return "";
}