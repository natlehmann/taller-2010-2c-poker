#ifndef _XMLPARSERESTADO_DENTROTAG_H__
#define _XMLPARSERESTADO_DENTROTAG_H__

#define _CRT_SECURE_NO_DEPRECATE 1

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include <deque>

#include "XmlParserEstado.h"
#include "XmlParser.h"
#include "XmlParserEstadoCerrandoTag.h"
#include "XmlParserEstadoProcesandoTxt.h"


using namespace std;

class XmlParserEstadoInicial;

class XmlParserEstadoDentroTag : public XmlParserEstado
{
private:
	XmlParserEstadoProcesandoTxt* procesandoTexto;
	XmlParserEstadoCerrandoTag* cerrandoTag;
	XmlParserEstadoInicial* inicial;

	XmlParserEstadoProcesandoTxt* getProcesandoTexto();
	XmlParserEstadoCerrandoTag* getCerrandoTag();
	XmlParserEstadoInicial* getInicial();

public:
	XmlParserEstadoDentroTag(deque<string*>* nodosProcesados);
	XmlParserEstadoDentroTag(deque<string*>* nodosProcesados, XmlParserEstadoInicial* inicial,
		XmlParserEstadoProcesandoTxt* procesandoTexto, XmlParserEstadoCerrandoTag* cerrandoTag);
	virtual ~XmlParserEstadoDentroTag(void);

	virtual XmlParserEstado* procesarFragmento();
};

#endif
