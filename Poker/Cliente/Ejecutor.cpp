#include "Ejecutor.h"
#include "FabricaOperacionesCliente.h"
#include "MensajesUtil.h"
#include <vector>

bool Ejecutor::enEjecucion = false;
string Ejecutor::parametro = "";
string Ejecutor::idOperacion = "";
Ventana* Ejecutor::ventana = NULL;
SDL_Thread* Ejecutor::thread = NULL;

Ejecutor::Ejecutor(void)
{
}

Ejecutor::~Ejecutor(void)
{
}

bool Ejecutor::isEnEjecucion(){
	return Ejecutor::enEjecucion;
}

void Ejecutor::ejecutar(string idOperacion, Ventana* ventana){
	Ejecutor::ejecutar(idOperacion, "", ventana);
}

void Ejecutor::ejecutar(string idOperacion, string parametro, Ventana* ventana){

	if (!Ejecutor::isEnEjecucion()) {

		Ejecutor::enEjecucion = true;
		Ejecutor::parametro = parametro;
		Ejecutor::idOperacion = idOperacion;
		Ejecutor::ventana = ventana;

		int (*puntero)(void*) = &Ejecutor::ejecutarAsync; 

		Ejecutor::thread = SDL_CreateThread(puntero, NULL);
	}
}

SDL_Thread* Ejecutor::getThread(){
	return Ejecutor::thread;
}

int Ejecutor::ejecutarAsync(void* data) {

	FabricaOperacionesCliente fab;
	vector<string> parametros;
	if (!MensajesUtil::esVacio(Ejecutor::parametro)) {
		parametros.push_back(Ejecutor::parametro);
	}

	OperacionUICliente* operacion = fab.newOperacion(
		Ejecutor::idOperacion, parametros);
	operacion->ejecutar(Ejecutor::ventana);
	delete(operacion);

	Ejecutor::enEjecucion = false;
	return 0;
}
