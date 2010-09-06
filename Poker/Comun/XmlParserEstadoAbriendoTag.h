#ifndef _XMLPARSERESTADO_ABRIENDOTAG_H__
#define _XMLPARSERESTADO_ABRIENDOTAG_H__

#define _CRT_SECURE_NO_DEPRECATE 1

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include <deque>

#include "Elemento.h"
#include "XmlParserEstado.h"
#include "XmlParserEstadoDentroTag.h"
#include "XmlParserEstadoCerrandoInline.h"
#include "XmlParserEstadoProcesandoAtt.h"

using namespace std;

class XmlParserEstadoAbriendoTag : public XmlParserEstado
{
private:
	XmlParserEstadoCerrandoInline* cerrandoInline;
	XmlParserEstadoDentroTag* dentroTag;
	XmlParserEstadoProcesandoAtt* procesandoAtt;

public:
	XmlParserEstadoAbriendoTag(deque<string*>* nodosProcesados);
	virtual ~XmlParserEstadoAbriendoTag(void);

	virtual XmlParserEstado* procesarFragmento();
};

#endif
