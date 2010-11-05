#include "EstadoEvaluandoGanador.h"
#include "EstadoEsperandoJugadores.h"
#include "EstadoRondaCiega.h"

EstadoEvaluandoGanador::EstadoEvaluandoGanador(void)
{
}

EstadoEvaluandoGanador::~EstadoEvaluandoGanador(void)
{
}

void EstadoEvaluandoGanador::setEstadoEsperandoJugadores(EstadoEsperandoJugadores* esperandoJugadores){
	this->esperandoJugadores = esperandoJugadores;
}

void EstadoEvaluandoGanador::setEstadoRondaCiega(EstadoRondaCiega* rondaCiega){
	this->rondaCiega = rondaCiega;
}

EstadoJuego* EstadoEvaluandoGanador::getSiguienteEstado(){
	return NULL;
}

string EstadoEvaluandoGanador::getEscenarioJuego(int idJugador){
	return "";
}

string EstadoEvaluandoGanador::getEscenarioJuego(int idJugador, string mensaje){
	return "";
}
