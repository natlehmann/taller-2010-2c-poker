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
	this->agregarMesa(arbol);
	this->agregarBote(arbol);

	// TODO: Ver si se manda el mensaje al archivo de configuracion
	this->agregarMensaje(arbol, "Esperando que se sumen jugadores ...");

	this->agregarJugadores(arbol, idJugador);
	this->agregarPanelBotones(arbol, false);

	string resultado = this->arbolToString(arbol);
	delete(arbol);

	return resultado;
}

string EstadoEsperandoJugadores::getEscenarioJuego(int idJugador, string mensaje){
	// MEtodo vacio: nunca puede llamarse
	return "";
}
