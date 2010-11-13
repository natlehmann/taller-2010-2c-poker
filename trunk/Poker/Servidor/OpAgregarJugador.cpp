#include "OpAgregarJugador.h"
#include "ContextoJuego.h"
#include "MensajesUtil.h"
#include "OpEnviarEscenario.h"
#include "FabricaOperacionesServidor.h"
#include "JugadorModelo.h"
#include "UtilTiposDatos.h"
#include "SincronizadorThreads.h"
#include <vector>
#include <windows.h>


OpAgregarJugador::OpAgregarJugador(int idCliente, vector<string> parametros) : Operacion(idCliente) {
	this->parametros = parametros;
}

OpAgregarJugador::~OpAgregarJugador(void)
{
}

bool OpAgregarJugador::ejecutarAccion(Socket* socket){

	bool error = false;

	if (ContextoJuego::getInstancia()->hayLugar()) {

		// TODO: REEMPLAZAR ESTO SACANDO LOS DATOS DE LA BASE!!
		string nombreJugador = "jugador " + UtilTiposDatos::enteroAString(this->getIdCliente());
		string nombreImagen = "jugador5.bmp";
		int fichas = 1000;
		bool esVirtual = false;
		bool esObservador;
		if (ContextoJuego::getInstancia()->getCantidadJugadoresActivos() == 0)
			esObservador = true;
		else
			esObservador = false;

		JugadorModelo* jugador = ContextoJuego::getInstancia()->agregarJugador(
			this->getIdCliente(), nombreJugador, nombreImagen, fichas, esVirtual, esObservador);

		SincronizadorThreads::getInstancia()->registrarThreadJugador(::GetCurrentThread(), jugador->getId());

		FabricaOperacionesServidor fab;
		vector<string> parametros;
		Operacion* opEnviarEscenario = fab.newOperacion("OpEnviarEscenario", parametros, this->getIdCliente());
		error = opEnviarEscenario->ejecutarAccion(socket);
		delete (opEnviarEscenario);


	} else{
		
		string respuesta = ContextoJuego::getInstancia()->getEscenarioJuego(
			this->getIdCliente(), "No hay lugar en esta mesa.");

		if (socket != NULL && !MensajesUtil::esVacio(respuesta)){
			if(!socket->enviar(respuesta)) {
				error = true;
			}
		}
		else {
			error = true;
		}
	}

	return error;
}
