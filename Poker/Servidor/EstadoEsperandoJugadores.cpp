#include "EstadoEsperandoJugadores.h"
#include "ContextoJuego.h"
#include "RecursosServidor.h"
#include "UtilTiposDatos.h"

EstadoEsperandoJugadores::EstadoEsperandoJugadores(void)
{
}

EstadoEsperandoJugadores::~EstadoEsperandoJugadores(void)
{
}

void EstadoEsperandoJugadores::setEstadoRondaCiega(EstadoRondaCiega* rondaCiega){
	this->estadoRondaCiega = rondaCiega;
}

EstadoJuego* EstadoEsperandoJugadores::getSiguienteEstado(){

	int tiempoMinimo = UtilTiposDatos::getEntero( 
		RecursosServidor::getConfig()->get("servidor.logica.timeout.esperandoJugadores") );

	if (ContextoJuego::getInstancia()->getCantidadJugadoresActivos() > 1
		&& ContextoJuego::getInstancia()->getTiempoEsperandoJugadores() >= tiempoMinimo ) {

		ContextoJuego::getInstancia()->iniciarJuego();
		return this->estadoRondaCiega;

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
