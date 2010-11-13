#ifndef _SINCRONIZADOR_THREADS_H_
#define _SINCRONIZADOR_THREADS_H_

#include <windows.h>
#include <iostream>

#define MAX_CANT_CLIENTES  6

using namespace std;

class SincronizadorThreads
{
private:
	HANDLE clientes[MAX_CANT_CLIENTES];
	int indice;
	HANDLE mutex;
	bool inicializado;
	int cantThreadsActivos;

	static SincronizadorThreads* instancia;

	SincronizadorThreads(void);

public:	
	virtual ~SincronizadorThreads(void);

	static SincronizadorThreads* getInstancia();

	void registrarThreadJugador(HANDLE threadHandle, int idJugador);
	void notificarFin(int idJugador);
	void borrarThreadJugador(int idJugador);
};

#endif //_SINCRONIZADOR_THREADS_H_

