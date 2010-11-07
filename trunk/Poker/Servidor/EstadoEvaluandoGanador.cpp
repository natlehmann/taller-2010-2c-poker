#include "EstadoEvaluandoGanador.h"
#include "EstadoEsperandoJugadores.h"
#include "EstadoRondaCiega.h"
#include "ContextoJuego.h"

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
	
	if (ContextoJuego::getInstancia()->isTiempoMostrandoGanadorCumplido()) {
		
		if (ContextoJuego::getInstancia()->getCantidadJugadoresActivos() > 1) {

			ContextoJuego::getInstancia()->iniciarJuego();
			return this->rondaCiega;

		} else{

			ContextoJuego::getInstancia()->resetTimerEsperandoJugadores();
			return this->esperandoJugadores;
		}

	} else {
		return this;
	}
}

string EstadoEvaluandoGanador::getEscenarioJuego(int idJugador){

	DomTree* arbol = this->crearArbolEscenario();
	this->agregarMesa(arbol);
	this->agregarBote(arbol);
	this->agregarJugadores(arbol, idJugador);
	this->agregarCartasComunitarias(arbol);

	if (!ContextoJuego::getInstancia()->getJugador(idJugador)->isVirtual()) {
		this->agregarPanelBotones(arbol, false);
	}

	this->agregarMensaje(arbol, ContextoJuego::getInstancia()->getNombreGanador() 
		+  string(" gana esta mano."));

	string resultado = this->arbolToString(arbol);
	delete (arbol);

	return resultado;
}

string EstadoEvaluandoGanador::getEscenarioJuego(int idJugador, string mensaje){
	// no deberia llamarse este metodo
	return "";
}
