#ifndef _DOMTREEFACTORY_H__
#define _DOMTREEFACTORY_H__

#define _CRT_SECURE_NO_DEPRECATE 1

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <set>
#include <map>
#include "SDL_Thread.h"

#include "DomTree.h"

using namespace std;

class DomTreeFactoryInstance;

class DomTreeFactory
{
private:
	static map<string, DomTreeFactoryInstance> configuraciones;
	static string defaultConfig;

	static SDL_sem* semaforo;

protected:
	DomTreeFactory(void);

public:

	static void inicializar();

	/**
	* Crea un elemento del DomTree para la configuracion default del parser
	*/
	static Elemento* crearElemento(string nombre);

	/*
	* Crea un elemento del DomTree
	*/
	virtual Elemento* elemento(string nombre) = 0;

	/*
	* Devuelve un DomTreeFactory perteneciente a una determinada configuracion
	* del parser
	*/
	static DomTreeFactory* config(string nombreConfig);

	static void finalizar();
};

#endif
