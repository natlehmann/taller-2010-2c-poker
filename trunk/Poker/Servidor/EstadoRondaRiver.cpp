#include "EstadoRondaRiver.h"
#include "ContextoJuego.h"

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

	if (ContextoJuego::getInstancia()->isRondaTerminada()) {

		ContextoJuego::getInstancia()->finalizarRonda();

		return this->evaluandoGanador;

	} else {
		return this;
	}
}

string EstadoRondaRiver::getEscenarioJuego(int idJugador){
	return this->getEscenarioEstandar(idJugador);
}

string EstadoRondaRiver::getEscenarioJuego(int idJugador, string mensaje){
	return this->getEscenarioConMensaje(idJugador, mensaje);
}