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


using namespace std;

class XmlParserEstadoDentroTag : public XmlParserEstado
{
public:
	XmlParserEstadoDentroTag(deque<string*>* nodosProcesados);
	virtual ~XmlParserEstadoDentroTag(void);

	virtual XmlParserEstado* procesarFragmento();
};

#endif
