#ifndef _SINCRONIZADOR_H__
#define _SINCRONIZADOR_H__


#include "SDL.h" 
#include "SDL_Thread.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "VentanaAuxiliar.h"
#include "Ventana.h"


using namespace std;

class Sincronizador
{
private:
	SDL_mutex* syncMutex;
	VentanaAuxiliar* ventanaAuxiliar;
	SDL_Surface* superficie;
	Ventana* ventana;

	static Sincronizador* instancia;

	Sincronizador(void);

public:
	virtual ~Sincronizador(void);

	static Sincronizador* getInstancia();

	/* Metodo bloqueante */
	VentanaAuxiliar* getVentanaAuxiliar();

	/* Metodo de liberacion del lock */
	void notificarCambio();

	void registrarVentana(Ventana* ventana);

	void limpiar();

};

#endif //_SINCRONIZADOR_H__

