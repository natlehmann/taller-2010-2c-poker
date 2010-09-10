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
//#include "Parser.h"
//#include "XmlParserEstado.h"
//#include "PokerException.h"

using namespace std;

class ParserEntradaTeclado
{
private:
	string _codigoOperacion;
	list<string>* _lstOperandos;

	//string abrirNodo(Elemento* elemento, string indent);
	//string cerrarNodo(Elemento* elemento, string indent);
	//string procesarNodo(Elemento* elemento, string indent);
	DomTree* toDom();
	//string toString(DomTree* domTree);

public:
	ParserEntradaTeclado(string codigoOperacion, list<string>* lstOperandos);
	virtual ~ParserEntradaTeclado(void);

	string generarMensaje();
	string obtenerRespuesta(string respuesta);
};

#endif
