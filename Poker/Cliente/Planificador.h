#ifndef _PLANIFICADOR_H__
#define _PLANIFICADOR_H__

#include "SDL.h" 
#include "Ventana.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;

class Planificador
{
private:
	static Ventana* ventana;
	static bool enEjecucion;
	static bool finalizado;

	Planificador(void);

public:
	virtual ~Planificador(void);

	static void setVentana(Ventana* ventana);
	static int planificarOperacion(void* data);
	static void finalizar();
	static bool isFinalizado();
};

#endif //_PLANIFICADOR_H__
