#include "SincronizadorThreads.h"
#include "PokerException.h"

SincronizadorThreads::SincronizadorThreads(void)
{
	this->mutex = CreateMutexA(NULL, false, "MutexSincronizadorThreads");

	for (int i = 0; i < MAX_CANT_CLIENTES; i++) {
		this->clientes[i] = -1;
	}
	this->indice = 0;
}

SincronizadorThreads::~SincronizadorThreads(void)
{
	CloseHandle(this->mutex);
}

int SincronizadorThreads::getSiguienteId(){

	if(WaitForSingleObject(this->mutex, INFINITE)==WAIT_TIMEOUT) {
	   // TODO: handle time-out error
	}

	int cantVeces = MAX_CANT_CLIENTES;
	int resultado = -1;

	while(this->clientes[this->indice] < 0  && cantVeces > 0) {
		this->indice++;
		if (this->indice >= MAX_CANT_CLIENTES) {
			this->indice = 0;
		}
		cantVeces--;
	}

	if (this->clientes[this->indice] >= 0) {
		resultado = this->clientes[this->indice];
		this->indice++;
		if (this->indice >= MAX_CANT_CLIENTES) {
			this->indice = 0;
		}
	}

	ReleaseMutex(this->mutex);
	return resultado;
}

void SincronizadorThreads::agregarCliente(int idCliente){
	if(WaitForSingleObject(this->mutex, INFINITE)==WAIT_TIMEOUT) {
	   // TODO: handle time-out error
	}

	int cantVeces = MAX_CANT_CLIENTES;

	while(this->clientes[this->indice] >= 0  && cantVeces > 0) {
		this->indice++;
		if (this->indice >= MAX_CANT_CLIENTES) {
			this->indice = 0;
		}
		cantVeces--;
	}

	if (this->clientes[this->indice] < 0) {
		this->clientes[this->indice] = idCliente;

	} else {
		ReleaseMutex(this->mutex);
		throw PokerException("No se pueden agregar mas clientes.");
	}

	ReleaseMutex(this->mutex);
}

void SincronizadorThreads::borrarCliente(int idCliente){

	if(WaitForSingleObject(this->mutex, INFINITE)==WAIT_TIMEOUT) {
	   // TODO: handle time-out error
	}

	for (int i = 0; i < MAX_CANT_CLIENTES; i++) {
		if (this->clientes[i] == idCliente) {
			this->clientes[i] = -1;
		}
	}

	ReleaseMutex(this->mutex);
}