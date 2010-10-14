#ifndef _XMLPARSERESTADO_CERRANDOTAG_H__
#define _XMLPARSERESTADO_CERRANDOTAG_H__

#define _CRT_SECURE_NO_DEPRECATE 1

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include <deque>

#include "XmlParserEstado.h"
#include "XmlParser.h"


using namespace std;

class XmlParserEstadoInicial;

class XmlParserEstadoCerrandoTag : public XmlParserEstado
{
private:
	XmlParserEstadoInicial* inicial;
	XmlParserEstadoInicial* getInicial();

public:
	XmlParserEstadoCerrandoTag(deque<string*>* nodosProcesados);
	XmlParserEstadoCerrandoTag(deque<string*>* nodosProcesados, XmlParserEstadoInicial* inicial);
	virtual ~XmlParserEstadoCerrandoTag(void);

	virtual XmlParserEstado* procesarFragmento();
};

#endif
