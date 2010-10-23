#include "OpAgregarJugador.h"

#include "FabricaOperacionesServidor.h"

OpAgregarJugador::OpAgregarJugador(vector<string> parametros){
	this->parametros = parametros;
}

OpAgregarJugador::~OpAgregarJugador(void)
{
}

bool OpAgregarJugador::ejecutar(Socket* socket){

	// TODO: BORRAR TODO ESTO, ES DE PRUEBA
	cout << "EL ID DEL CLIENTE ES " << this->getIdCliente() << endl;
	FabricaOperacionesServidor fab;
	Operacion* op = fab.newOperacion("OpEnviarEscenario", this->parametros, this->getIdCliente());
	bool resultado = op->ejecutar(socket);
	delete(op);
	return resultado;
}
