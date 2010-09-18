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

public:
	DomTree(void);

	/**
	* Construye un arbol conteniendo el elemento recibido por parametro
	*/
	DomTree(Elemento* elemento);

	virtual ~DomTree(void);

	/**
	* Agrega un elemento al nivel de la raiz del arbol
	*/
	Elemento* agregarElemento(string nombre);

	Elemento* getRaiz();
};

#endif
