#include "OpDejarMesa.h"
#include "ContextoJuego.h"
#include "MensajesUtil.h"
#include "OpEnviarEscenario.h"
#include "FabricaOperacionesServidor.h"
#include "SincronizadorThreads.h"
#include "AccesoDatos.h"
#include "GeneradorRespuesta.h"
#include "Respuesta.h"
#include <vector>

OpDejarMesa::OpDejarMesa(int idCliente) : Operacion(idCliente)
{
}

OpDejarMesa::~OpDejarMesa(void)
{
}

bool OpDejarMesa::ejecutarAccion(Socket* socket){

	//bool error = false;

	//SincronizadorThreads::getInstancia()->borrarThreadJugador(ContextoJuego::getInstancia()->idClienteToIdJugador(this->getIdCliente()));

	//// TODO: Aca habría que resguardar las fichas en la base?
	//ContextoJuego::getInstancia()->quitarJugador(this->getIdCliente());

	//
	//return error;

	bool error = false;
	bool ok = true;
	string respuesta = "";

	AccesoDatos ad;
	
	if (ok)//ad.guardarFichasJugador(usuario))
	{
		SincronizadorThreads::getInstancia()->borrarThreadJugador(ContextoJuego::getInstancia()->idClienteToIdJugador(this->getIdCliente()));

		// TODO: Aca habría que resguardar las fichas en la base?
		ContextoJuego::getInstancia()->quitarJugador(this->getIdCliente());

		respuesta = "OK";
	}

	if (socket != NULL && !MensajesUtil::esVacio(respuesta))
	{
		if(!socket->enviar(respuesta)) 
			error = true;
	}
	else 
		error = true;
	
	return error;
}
