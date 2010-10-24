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
	Elemento* elemEscenario = EstadoJuego::crearElementoEscenario();
	EstadoJuego::agregarMesa(elemEscenario);
	EstadoJuego::agregarBote(elemEscenario);
	EstadoJuego::agregarMensaje(elemEscenario, "Esperando que se sumen jugadores para iniciar el juego ...");

	return "";
}
