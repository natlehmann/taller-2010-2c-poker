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
	return "";
}
