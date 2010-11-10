#include "EstadoEvaluandoGanador.h"
#include "EstadoEsperandoJugadores.h"
#include "EstadoRondaCiega.h"
#include "ContextoJuego.h"
#include <list>

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
	this->agregarPanelBotones(arbol, false);

	list<string> nombresGanadores = ContextoJuego::getInstancia()->getNombresGanadores();
	int cantidadGanadores = nombresGanadores.size();
	string ganadores;
	if (cantidadGanadores > 1) {
		ganadores = "Ganadores: ";
	} else {
		ganadores = "Ganador: ";
	}
	list<string>::iterator it = nombresGanadores.begin();
	for (int i=0 ; i < cantidadGanadores ; ++i) {
		ganadores.append(*it);
		if ((cantidadGanadores > 1) && (i != cantidadGanadores - 1)) {
			ganadores.append(", ");
		}
		++it;
	}
	ganadores.append(".");
	this->agregarMensaje(arbol, ganadores);

	string resultado = this->arbolToString(arbol);
	delete (arbol);

	return resultado;
}

string EstadoEvaluandoGanador::getEscenarioJuego(int idJugador, string mensaje){
	// no deberia llamarse este metodo
	return "";
}
