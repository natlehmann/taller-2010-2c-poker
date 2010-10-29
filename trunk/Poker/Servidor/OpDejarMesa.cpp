#include "OpDejarMesa.h"
#include "ContextoJuego.h"
#include "MensajesUtil.h"
#include "OpEnviarEscenario.h"
#include "FabricaOperacionesServidor.h"
#include <vector>

OpDejarMesa::OpDejarMesa(int idCliente) : Operacion(idCliente)
{
}

OpDejarMesa::~OpDejarMesa(void)
{
}

bool OpDejarMesa::ejecutarAccion(Socket* socket){

	// TODO !!!!!!!!!!!!!!!!
	
	FabricaOperacionesServidor fab;
	vector<string> parametros;
	Operacion* opEnviarEscenario = fab.newOperacion("OpEnviarEscenario", parametros, this->getIdCliente());
	bool resultado = opEnviarEscenario->ejecutarAccion(socket);
	delete (opEnviarEscenario);

	return resultado;
}
