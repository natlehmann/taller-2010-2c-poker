#include "OpDejarMesa.h"
#include "ContextoJuego.h"
#include "MensajesUtil.h"
#include "OpEnviarEscenario.h"
#include "FabricaOperacionesServidor.h"
#include "SincronizadorThreads.h"
#include <vector>

OpDejarMesa::OpDejarMesa(int idCliente) : Operacion(idCliente)
{
}

OpDejarMesa::~OpDejarMesa(void)
{
}

bool OpDejarMesa::ejecutarAccion(Socket* socket){

	SincronizadorThreads::getInstancia()->borrarThreadJugador(
		ContextoJuego::getInstancia()->idClienteToIdJugador(this->getIdCliente()));

	// TODO: Aca habría que resguardar las fichas en la base?
	ContextoJuego::getInstancia()->quitarJugador(this->getIdCliente());


	
	
	//FabricaOperacionesServidor fab;
	//vector<string> parametros;
	//Operacion* opEnviarEscenario = fab.newOperacion("OpEnviarEscenario", parametros, this->getIdCliente());
	//bool resultado = opEnviarEscenario->ejecutarAccion(socket);
	//delete (opEnviarEscenario);

	//return resultado;

	return true;
}
