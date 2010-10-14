#ifndef _DOMTREE_H__
#define _DOMTREE_H__

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <set>

#include "Elemento.h"

using namespace std;

class DomTree
{

private:
	Elemento* raiz;
	string nombreConfiguracion;

public:
	/*
	* Construye un arbol con la configuracion default
	*/
	DomTree(void);

	/*
	* Construye un arbol que se valida con una determinada configuracion
	*/
	DomTree(string nombreConfiguracion);

	/**
	* Construye un arbol conteniendo el elemento recibido por parametro, para la configuracion default
	*/
	DomTree(Elemento* elemento);

	/**
	* Construye un arbol conteniendo el elemento recibido por parametro, que se valida
	* con una determinada configuracion
	*/
	DomTree(Elemento* elemento, string nombreConfiguracion);

	virtual ~DomTree(void);

	/**
	* Agrega un elemento al nivel de la raiz del arbol
	*/
	Elemento* agregarElemento(string nombre);

	Elemento* getRaiz();
};

#endif
