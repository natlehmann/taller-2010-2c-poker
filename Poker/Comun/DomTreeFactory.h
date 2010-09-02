#ifndef _DOMTREEFACTORY_H__
#define _DOMTREEFACTORY_H__

#define _CRT_SECURE_NO_DEPRECATE 1

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
//#include <algorithm>
//#include <cctype>
#include <set>
#include <map>

#include "DomTree.h"

using namespace std;

class DomTreeFactory
{
private:
	static Elemento* configurarNodo(string nombre, char* hijos[], char* atributos[]);

public:
	DomTreeFactory(void);
	virtual ~DomTreeFactory(void);

	static Elemento* crearElemento(string nombre);
};

#endif
