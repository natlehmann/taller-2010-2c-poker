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
		ContextoJuego::getInstancia()->iniciarJuego();

		return this->rondaFlop;

	} else {
		return this;
	}
}

string EstadoRondaCiega::getEscenarioJuego(int idJugador){

	DomTree* arbol = EstadoJuego::crearArbolEscenario();
	EstadoJuego::agregarMesa(arbol);
	EstadoJuego::agregarBote(arbol);
	EstadoJuego::agregarJugadores(arbol, idJugador);
	EstadoJuego::agregarCartasComunitarias(arbol);
	EstadoJuego::agregarPanelBotones(arbol, idJugador);
	EstadoJuego::borrarMensaje(arbol);

	return EstadoJuego::arbolToString(arbol);
}
