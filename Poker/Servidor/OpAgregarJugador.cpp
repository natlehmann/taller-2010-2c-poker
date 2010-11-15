#include "OpAgregarJugador.h"
#include "ContextoJuego.h"
#include "MensajesUtil.h"
#include "OpEnviarEscenario.h"
#include "FabricaOperacionesServidor.h"
#include "JugadorModelo.h"
#include "UtilTiposDatos.h"
#include "SincronizadorThreads.h"
#include "AccesoDatos.h"
#include "JugadorModelo.h"
#include "MensajesUtil.h"
#include "RecursosServidor.h"
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

		string nombreJugador = this->parametros.at(0);

		AccesoDatos ad;
		JugadorModelo* jugadorBD = ad.obtenerJugador(nombreJugador);

		string nombreImagen = jugadorBD->getNombreImagen();

		if (MensajesUtil::esVacio(nombreImagen)) {
			nombreImagen = "jugador_default.bmp";
		}
nombreImagen = "jugador5.bmp";		
		int fichas = jugadorBD->getFichas();

		bool esVirtual = false;
		bool esObservador = false;
		
		if (MensajesUtil::sonIguales(this->parametros.at(1), "true")){
			esVirtual = true;
		}

		if (MensajesUtil::sonIguales(this->parametros.at(2), "true")){
			esObservador = true;
		}

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
