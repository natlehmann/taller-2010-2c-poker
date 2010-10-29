#include "EstadoRondaFlop.h"
#include "ContextoJuego.h"

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
	
	if (ContextoJuego::getInstancia()->isRondaTerminada()) {

		ContextoJuego::getInstancia()->mostrarTurn();
		ContextoJuego::getInstancia()->iniciarJuego();

		return this->rondaTurn;

	} else {
		return this;
	}
}

string EstadoRondaFlop::getEscenarioJuego(int idJugador){
	return this->getEscenarioEstandar(idJugador);
}