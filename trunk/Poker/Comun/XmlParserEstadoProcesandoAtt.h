#ifndef _XMLPARSERESTADO_PROCESANDOATT_H__
#define _XMLPARSERESTADO_PROCESANDOATT_H__

#define _CRT_SECURE_NO_DEPRECATE 1

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include <deque>

#include "XmlParserEstado.h"

using namespace std;

class XmlParserEstadoProcesandoAtt : public XmlParserEstado
{
public:
	XmlParserEstadoProcesandoAtt(deque<string*>* nodosProcesados);
	virtual ~XmlParserEstadoProcesandoAtt(void);

	virtual XmlParserEstado* procesarFragmento();
};

#endif