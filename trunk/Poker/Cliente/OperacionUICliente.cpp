#include "OperacionUICliente.h"
#include "PokerException.h"
#include "RecursosCliente.h"

OperacionUICliente::OperacionUICliente(void)
{
}

OperacionUICliente::~OperacionUICliente(void)
{
}

bool OperacionUICliente::ejecutar(Ventana* ventana){

	bool resultado = false;
	/*
	HANDLE mutexVentana = ventana->getMutex();
	
	// TODO: VERIFICAR TIMEOUT
	if(WaitForSingleObject(mutexVentana, 10000)==WAIT_TIMEOUT) {
	   // TODO: handle time-out error
		cout << "DIO TIMEOUT !!!!" << endl;

	} 
	*/

	ventana->bloquear();

	try {
		resultado = this->ejecutarAccion(ventana);

	} catch(PokerException& e){
		RecursosCliente::getLog()->escribir(&(e.getError()));

	} catch(...){
		RecursosCliente::getLog()->escribir("Se produjo un error ejecutando la operacion.");
	}

	//ReleaseMutex(mutexVentana);
	ventana->desbloquear();
	return resultado;
}
