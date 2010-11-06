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

	if (ContextoJuego::getInstancia()->isTurnoCliente(this->getIdCliente())) {

		ContextoJuego::getInstancia()->igualarApuesta(this->getIdCliente());
	}

	FabricaOperacionesServidor fab;
	vector<string> parametros;
	Operacion* opEnviarEscenario = fab.newOperacion("OpEnviarEscenario", parametros, this->getIdCliente());
	bool resultado = opEnviarEscenario->ejecutarAccion(socket);
	delete (opEnviarEscenario);

	return resultado;
}
