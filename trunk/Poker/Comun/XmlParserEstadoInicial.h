#ifndef _XMLPARSERESTADO_INICIAL_H__
#define _XMLPARSERESTADO_INICIAL_H__

#define _CRT_SECURE_NO_DEPRECATE 1

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include <deque>

#include "Elemento.h"
#include "XmlParserEstado.h"
#include "XmlParserEstadoAbriendoTag.h"

using namespace std;

class XmlParserEstadoInicial : public XmlParserEstado
{
private:
	XmlParserEstadoAbriendoTag* abriendoTag;

public:
	XmlParserEstadoInicial(deque<string*>* nodosProcesados);
	virtual ~XmlParserEstadoInicial(void);

	virtual XmlParserEstado* procesarFragmento();
};

#endif