#include "EstadoRondaTurn.h"
#include "ContextoJuego.h"

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
	
	if (ContextoJuego::getInstancia()->isRondaTerminada()) {

		ContextoJuego::getInstancia()->mostrarRiver();
		ContextoJuego::getInstancia()->iniciarRonda();

		return this->rondaRiver;

	} else {
		return this;
	}
}

string EstadoRondaTurn::getEscenarioJuego(int idJugador){
	return this->getEscenarioEstandar(idJugador);
}

string EstadoRondaTurn::getEscenarioJuego(int idJugador, string mensaje){
	return this->getEscenarioConMensaje(idJugador, mensaje);
}
