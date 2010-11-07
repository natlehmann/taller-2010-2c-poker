#include "OpAgregarJugador.h"
#include "ContextoJuego.h"
#include "MensajesUtil.h"
#include "OpEnviarEscenario.h"
#include "FabricaOperacionesServidor.h"
#include "JugadorModelo.h"
#include <vector>


OpAgregarJugador::OpAgregarJugador(int idCliente, vector<string> parametros) : Operacion(idCliente) {
	this->parametros = parametros;
}

OpAgregarJugador::~OpAgregarJugador(void)
{
}

bool OpAgregarJugador::ejecutarAccion(Socket* socket){

	if (ContextoJuego::getInstancia()->hayLugar()) {

		// TODO: REEMPLAZAR ESTO SACANDO LOS DATOS DE LA BASE!!
		string nombreJugador = "jugadorX";
		string nombreImagen = "jugador5.bmp";
		int fichas = 1000;
		bool esVirtual = false;

		ContextoJuego::getInstancia()->agregarJugador(
			this->getIdCliente(), nombreJugador, nombreImagen, fichas, esVirtual);

	} else{
		// TODO !!!!!
	}

	FabricaOperacionesServidor fab;
	vector<string> parametros;
	Operacion* opEnviarEscenario = fab.newOperacion("OpEnviarEscenario", parametros, this->getIdCliente());
	bool resultado = opEnviarEscenario->ejecutarAccion(socket);
	delete (opEnviarEscenario);

	return resultado;
}
