#ifndef _DOMTREEFACTORYINSTACE_H__
#define _DOMTREEFACTORYINSTACE_H__

#define _CRT_SECURE_NO_DEPRECATE 1

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <set>
#include <map>

#include "DomTreeFactory.h"

using namespace std;

class DomTreeFactoryInstance : public DomTreeFactory
{
private:
	string nombreConfig;

	list<string> elementos;
	map<string,string> hijosPorElemento;
	map<string,string> attPorElemento;

public:
	DomTreeFactoryInstance(string nombreConfig);
	virtual ~DomTreeFactoryInstance(void);

	virtual Elemento* elemento(string nombre);

	void setElementos(list<string> elementos);
	void setHijosPorElemento(map<string,string> hijosPorElem);
	void setAttPorElemento(map<string,string> attPorElem);
};

#endif
