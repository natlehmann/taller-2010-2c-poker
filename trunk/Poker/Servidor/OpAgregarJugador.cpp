#include "OpAgregarJugador.h"
#include "ContextoJuego.h"
#include "MensajesUtil.h"
#include "OpEnviarEscenario.h"


OpAgregarJugador::OpAgregarJugador(int idCliente, vector<string> parametros) : Operacion(idCliente) {
	this->parametros = parametros;
}

OpAgregarJugador::~OpAgregarJugador(void)
{
}

bool OpAgregarJugador::ejecutar(Socket* socket){

	if (ContextoJuego::getInstancia()->hayLugar()) {
		ContextoJuego::getInstancia()->agregarJugador(this->getIdCliente());

	} else{
		// TODO !!!!!
	}

	OpEnviarEscenario op(this->getIdCliente());
	return op.ejecutar(socket);
}
