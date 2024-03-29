#ifndef _XMLPARSERESTADO_CERRANDOINLINE_H__
#define _XMLPARSERESTADO_CERRANDOINLINE_H__

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

class XmlParserEstadoCerrandoInline : public XmlParserEstado
{
private:
	XmlParserEstadoInicial* inicial;
	XmlParserEstadoInicial* getInicial();

	bool faltaProcesar;

public:
	XmlParserEstadoCerrandoInline(deque<string*>* nodosProcesados);
	XmlParserEstadoCerrandoInline(deque<string*>* nodosProcesados, XmlParserEstadoInicial* inicial);
	virtual ~XmlParserEstadoCerrandoInline(void);

	virtual XmlParserEstado* procesarFragmento();

	// redefiniciones
	virtual void setInicioTexto(unsigned int inicio);
	virtual bool terminado();
};

#endif
