#include "Operacion.h"
#include "ContextoJuego.h"
#include "RecursosServidor.h"
#include "PokerException.h"
#include "Respuesta.h"

Operacion::Operacion(int idCliente) {
	this->setIdCliente(idCliente);
}

Operacion::~Operacion() {}

bool Operacion::ejecutar(Socket* socket){

	bool resultado = false;
	HANDLE mutexContexto = ContextoJuego::getInstancia()->getMutex();
	
	// TODO: VERIFICAR TIMEOUT
	if(WaitForSingleObject(mutexContexto, 10000)==WAIT_TIMEOUT) {
	   // TODO: handle time-out error
		cout << "DIO TIMEOUT !!!! ID CLIENTE: " << this->getIdCliente() << endl;

	} 

	try {
		resultado = this->ejecutarAccion(socket);

	} catch(PokerException& e){
		RecursosServidor::getLog()->escribir(&(e.getError()));

	} catch(exception& e){
		RecursosServidor::getLog()->escribir("Se produjo un error ejecutando la operacion. " + string(e.what()));

	} catch(...){
		RecursosServidor::getLog()->escribir("Se produjo un error ejecutando la operacion.");
	}
	
	ReleaseMutex(mutexContexto);
	return resultado;
}
