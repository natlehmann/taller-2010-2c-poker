#include "EstadoEsperandoJugadores.h"
#include "ContextoJuego.h"

EstadoEsperandoJugadores::EstadoEsperandoJugadores(void)
{
}

EstadoEsperandoJugadores::~EstadoEsperandoJugadores(void)
{
}

EstadoJuego* EstadoEsperandoJugadores::getSiguienteEstado(){
	if (ContextoJuego::getInstancia()->getCantidadJugadoresActivos() > 1) {
		ContextoJuego::getInstancia()->iniciarJuego();
		return &(this->estadoRondaCiega);

	} else {
		return this;
	}
}

string EstadoEsperandoJugadores::getEscenarioJuego(int idJugador){
	DomTree* arbol = EstadoJuego::crearArbolEscenario();
	EstadoJuego::agregarMesa(arbol);
	EstadoJuego::agregarBote(arbol);

	// TODO: Ver si se manda el mensaje al archivo de configuracion
	EstadoJuego::agregarMensaje(arbol, "Esperando que se sumen jugadores ...");

	EstadoJuego::agregarJugadores(arbol, idJugador);

	return EstadoJuego::arbolToString(arbol);
}
