#include "OpMostrarMensaje.h"
#include "ContextoJuego.h"
#include "MensajesUtil.h"

OpMostrarMensaje::OpMostrarMensaje(int idCliente, vector<string> parametros) : Operacion(idCliente) {
	this->parametros = parametros;
}

OpMostrarMensaje::~OpMostrarMensaje(void)
{
}

bool OpMostrarMensaje::ejecutarAccion(Socket* socket){

	bool error = false;
	string mensaje = this->parametros.at(0);

	string respuesta = ContextoJuego::getInstancia()->getEscenarioJuego(this->getIdCliente(), mensaje);

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
