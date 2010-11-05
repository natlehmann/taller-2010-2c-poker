#include "EstadoRondaCiega.h"
#include "ContextoJuego.h"

EstadoRondaCiega::EstadoRondaCiega(EstadoRondaFlop* rondaFlop)
{
	this->setEstadoRondaFlop(rondaFlop);
}

EstadoRondaCiega::~EstadoRondaCiega(void)
{
}

void EstadoRondaCiega::setEstadoRondaFlop(EstadoRondaFlop* rondaFlop){
	this->rondaFlop = rondaFlop;
}

EstadoJuego* EstadoRondaCiega::getSiguienteEstado(){

	if (ContextoJuego::getInstancia()->isRondaTerminada()) {

		ContextoJuego::getInstancia()->mostrarFlop();
		ContextoJuego::getInstancia()->iniciarRonda();

		return this->rondaFlop;

	} else {
		return this;
	}
}

string EstadoRondaCiega::getEscenarioJuego(int idJugador){

	return this->getEscenarioEstandar(idJugador);
}

string EstadoRondaCiega::getEscenarioJuego(int idJugador, string mensaje){
	return this->getEscenarioConMensaje(idJugador, mensaje);
}
