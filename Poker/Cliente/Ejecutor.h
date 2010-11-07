#ifndef _EJECUTOR_H__
#define _EJECUTOR_H__

#include "SDL.h" 
#include "Ventana.h"
#include "OperacionUICliente.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;

class Ejecutor
{
private:
	static bool enEjecucion;
	static string parametro;
	static string idOperacion;
	static Ventana* ventana;

	Ejecutor(void);

	static int ejecutarAsync(void* data);

public:	
	virtual ~Ejecutor(void);

	static bool isEnEjecucion();
	static void ejecutar(string idOperacion, Ventana* ventana);
	static void ejecutar(string idOperacion, string parametro, Ventana* ventana);
};

#endif //_EJECUTOR_H__

