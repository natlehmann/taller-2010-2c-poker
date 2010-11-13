#include "SincronizadorThreads.h"
#include "PokerException.h"
#include <windows.h>

SincronizadorThreads* SincronizadorThreads::instancia = new SincronizadorThreads();

SincronizadorThreads::SincronizadorThreads(void)
{
	this->mutex = CreateMutexA(NULL, false, "MutexSincronizadorThreads");

	for (int i = 0; i < MAX_CANT_CLIENTES; i++) {
		this->clientes[i] = NULL;
	}
	this->indice = 0;
	this->cantThreadsActivos = 0;
	this->inicializado = false;
}

SincronizadorThreads::~SincronizadorThreads(void)
{
	CloseHandle(this->mutex);
}

SincronizadorThreads* SincronizadorThreads::getInstancia(){
	return SincronizadorThreads::instancia;
}

void SincronizadorThreads::registrarThreadJugador(HANDLE threadHandle, int idJugador){
	this->clientes[idJugador] = threadHandle;
	this->cantThreadsActivos++;
	
	if (!this->inicializado) {
		SetThreadPriority(this->clientes[idJugador], THREAD_PRIORITY_HIGHEST);
		this->inicializado = true;

	} else {
		SetThreadPriority(this->clientes[idJugador], THREAD_PRIORITY_LOWEST);
	}
}

void SincronizadorThreads::notificarFin(int idJugador){

	// si termino el thread que tenia asignada la mayor prioridad
	if (this->indice == idJugador) {

		SetThreadPriority(this->clientes[this->indice], THREAD_PRIORITY_LOWEST);


		int indiceOrig = this->indice;
		this->indice++;
		if (this->indice >= MAX_CANT_CLIENTES) {
			this->indice = 0;
		}

		while (this->clientes[this->indice] == NULL && this->indice != indiceOrig) {
			this->indice++;
			if (this->indice >= MAX_CANT_CLIENTES) {
				this->indice = 0;
			}
		}

		if (this->clientes[this->indice] != NULL) {
			SetThreadPriority(this->clientes[this->indice], THREAD_PRIORITY_HIGHEST);
			//cout << "seteando prioridad mas alta a jugador " << indice << endl;
		}
	}
	
}

void SincronizadorThreads::borrarThreadJugador(int idJugador){

	this->clientes[idJugador] = NULL;
	this->notificarFin(idJugador);

	this->cantThreadsActivos--;

	if (this->cantThreadsActivos <= 0) {
		this->inicializado = false;
	}
}