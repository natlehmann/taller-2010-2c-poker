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
#include "XmlParser.h"
#include "ParserException.h"

using namespace std;

class XmlParserEstadoAbriendoTag : public XmlParserEstado
{
private:
	XmlParserEstadoCerrandoInline* cerrandoInline;
	XmlParserEstadoDentroTag* dentroTag;
	XmlParserEstadoProcesandoAtt* procesandoAtt;

	XmlParserEstadoCerrandoInline* getCerrandoInline();
	XmlParserEstadoDentroTag* getDentroTag();
	XmlParserEstadoProcesandoAtt* getProcesandoAtt();

public:
	XmlParserEstadoAbriendoTag(deque<string*>* nodosProcesados);
	XmlParserEstadoAbriendoTag(deque<string*>* nodosProcesados, XmlParserEstadoDentroTag* dentroTag,
		XmlParserEstadoCerrandoInline* cerrandoInline, XmlParserEstadoProcesandoAtt* procesandoAtt);
	virtual ~XmlParserEstadoAbriendoTag(void);

	virtual XmlParserEstado* procesarFragmento();
};

#endif
