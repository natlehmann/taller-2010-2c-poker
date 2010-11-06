#include "OpEnviarEscenario.h"
#include "Resultado.h"
#include "RecursosServidor.h"
#include "ContextoJuego.h"
#include "MensajesUtil.h"
#include <fstream>

OpEnviarEscenario::OpEnviarEscenario(int idCliente) : Operacion(idCliente) {
}

OpEnviarEscenario::~OpEnviarEscenario(void){
}

bool OpEnviarEscenario::ejecutarAccion(Socket* socket){
cout << "Enviando escenario a cliente " << this->getIdCliente() << endl;


	bool error = false;

	ContextoJuego::getInstancia()->chequearJugadorVirtual(this->getIdCliente());
	string respuesta = ContextoJuego::getInstancia()->getEscenarioJuego(this->getIdCliente());
//cout << respuesta << endl;
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
