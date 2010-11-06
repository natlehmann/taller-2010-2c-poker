#ifndef _SINCRONIZADOR_THREADS_H_
#define _SINCRONIZADOR_THREADS_H_

#include <windows.h>

#define MAX_CANT_CLIENTES  6

class SincronizadorThreads
{
private:
	int clientes[MAX_CANT_CLIENTES];
	int indice;
	HANDLE mutex;

public:
	SincronizadorThreads(void);
	virtual ~SincronizadorThreads(void);

	int getSiguienteId();
	void agregarCliente(int idCliente);
	void borrarCliente(int idCliente);
};

#endif //_SINCRONIZADOR_THREADS_H_

