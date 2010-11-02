#include "OpIgualarApuesta.h"
#include "ContextoJuego.h"
#include "MensajesUtil.h"
#include "OpEnviarEscenario.h"
#include "FabricaOperacionesServidor.h"
#include <vector>

OpIgualarApuesta::OpIgualarApuesta(int idCliente) : Operacion(idCliente)
{
}

OpIgualarApuesta::~OpIgualarApuesta(void)
{
}

bool OpIgualarApuesta::ejecutarAccion(Socket* socket){

	bool error = false;

	if (ContextoJuego::getInstancia()->isTurnoCliente(this->getIdCliente())) {

		ContextoJuego::getInstancia()->igualarApuesta(this->getIdCliente());
	}

	string respuesta = ContextoJuego::getInstancia()->getEscenarioJuego(this->getIdCliente());
cout << respuesta << endl << endl;
	if (socket != NULL && !MensajesUtil::esVacio(respuesta)){
		if(!socket->enviar(respuesta)) {
			error = true;
		}
	}
	else {
		error = true;
	}

	return error;
}
