#include "OpNoIr.h"
#include "ContextoJuego.h"
#include "MensajesUtil.h"
#include "OpEnviarEscenario.h"
#include "FabricaOperacionesServidor.h"
#include <vector>

OpNoIr::OpNoIr(int idCliente) : Operacion(idCliente)
{
}

OpNoIr::~OpNoIr(void)
{
}

bool OpNoIr::ejecutarAccion(Socket* socket){

	if (ContextoJuego::getInstancia()->isTurnoCliente(this->getIdCliente())) {

		ContextoJuego::getInstancia()->noIr(this->getIdCliente());
	}
	
	FabricaOperacionesServidor fab;
	vector<string> parametros;
	Operacion* opEnviarEscenario = fab.newOperacion("OpEnviarEscenario", parametros, this->getIdCliente());
	bool resultado = opEnviarEscenario->ejecutarAccion(socket);
	delete (opEnviarEscenario);

	return resultado;
}
