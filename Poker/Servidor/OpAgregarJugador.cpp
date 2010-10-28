#include "OpAgregarJugador.h"
#include "ContextoJuego.h"
#include "MensajesUtil.h"
#include "OpEnviarEscenario.h"
#include "FabricaOperacionesServidor.h"
#include <vector>


OpAgregarJugador::OpAgregarJugador(int idCliente, vector<string> parametros) : Operacion(idCliente) {
	this->parametros = parametros;
}

OpAgregarJugador::~OpAgregarJugador(void)
{
}

bool OpAgregarJugador::ejecutarAccion(Socket* socket){

	if (ContextoJuego::getInstancia()->hayLugar()) {
		ContextoJuego::getInstancia()->agregarJugador(this->getIdCliente());

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
