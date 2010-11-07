#include "OpPasar.h"
#include "ContextoJuego.h"
#include "MensajesUtil.h"
#include "OpEnviarEscenario.h"
#include "FabricaOperacionesServidor.h"
#include <vector>

OpPasar::OpPasar(int idCliente) : Operacion(idCliente)
{
}

OpPasar::~OpPasar(void)
{
}

bool OpPasar::ejecutarAccion(Socket* socket){

	if (ContextoJuego::getInstancia()->isTurnoCliente(this->getIdCliente())) {

		ContextoJuego::getInstancia()->pasar(this->getIdCliente());
	}

	FabricaOperacionesServidor fab;
	vector<string> parametros;
	Operacion* opEnviarEscenario = fab.newOperacion("OpEnviarEscenario", parametros, this->getIdCliente());
	bool resultado = opEnviarEscenario->ejecutarAccion(socket);
	delete (opEnviarEscenario);

	return resultado;
}
