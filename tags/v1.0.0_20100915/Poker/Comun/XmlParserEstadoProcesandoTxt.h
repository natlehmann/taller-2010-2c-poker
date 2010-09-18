#ifndef _XMLPARSERESTADO_PROCESANDOTXT_H__
#define _XMLPARSERESTADO_PROCESANDOTXT_H__

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


using namespace std;

class XmlParserEstadoInicial;

class XmlParserEstadoProcesandoTxt : public XmlParserEstado
{
private:
	string textoAcumulado;
	bool enProceso;

	XmlParserEstadoCerrandoTag* cerrandoTag;
	XmlParserEstadoInicial* inicial;

	XmlParserEstadoCerrandoTag* getCerrandoTag();
	XmlParserEstadoInicial* getInicial();

public:
	XmlParserEstadoProcesandoTxt(deque<string*>* nodosProcesados);
	virtual ~XmlParserEstadoProcesandoTxt(void);

	virtual XmlParserEstado* procesarFragmento();
};

#endif
