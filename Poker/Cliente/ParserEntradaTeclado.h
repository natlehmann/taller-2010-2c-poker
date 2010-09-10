#ifndef _PARSERENTRADATECLADO_H__
#define _PARSERENTRADATECLADO_H__

#define XML_OPEN "<"
#define XML_CLOSE ">"
#define XML_CLOSE_TAG "</"
#define XML_CLOSE_TAG_INLINE "/>"
#define XML_INDENT "   "
#define XML_OPEN_ATTR "=\""
#define XML_CLOSE_ATTR "\""

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include <list>
#include <set>
#include <map>
#include <deque>

#include <list>
#include "DomTree.h"

using namespace std;

class ParserEntradaTeclado
{
private:
	string _codigoOperacion;
	list<string>* _lstOperandos;

	DomTree* toDom();

public:
	ParserEntradaTeclado(string codigoOperacion, list<string>* lstOperandos);
	virtual ~ParserEntradaTeclado(void);

	string generarMensaje();
	string obtenerRespuesta(string respuesta);
};

#endif
