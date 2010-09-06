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


using namespace std;

class XmlParserEstadoCerrandoInline : public XmlParserEstado
{
public:
	XmlParserEstadoCerrandoInline(deque<string*>* nodosProcesados);
	virtual ~XmlParserEstadoCerrandoInline(void);

	virtual XmlParserEstado* procesarFragmento();
};

#endif
