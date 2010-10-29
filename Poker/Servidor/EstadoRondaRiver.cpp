#include "EstadoRondaRiver.h"

EstadoRondaRiver::EstadoRondaRiver(EstadoEvaluandoGanador* evaluandoGanador)
{
	this->setEstadoEvaluandoGanador(evaluandoGanador);
}

EstadoRondaRiver::~EstadoRondaRiver(void)
{
}

void EstadoRondaRiver::setEstadoEvaluandoGanador(EstadoEvaluandoGanador* evaluandoGanador){
	this->evaluandoGanador = evaluandoGanador;
}

EstadoJuego* EstadoRondaRiver::getSiguienteEstado(){
	return this; // TODO!!!!!!!!!!!!
}

string EstadoRondaRiver::getEscenarioJuego(int idJugador){
	return this->getEscenarioEstandar(idJugador);
}