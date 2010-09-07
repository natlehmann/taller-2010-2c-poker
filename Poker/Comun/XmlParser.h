#ifndef _XMLPARSER_H__
#define _XMLPARSER_H__

#define _CRT_SECURE_NO_DEPRECATE 1

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

#include "DomTree.h"
#include "Parser.h"
#include "XmlParserEstado.h"
#include "PokerException.h"

using namespace std;

class XmlParser : public Parser
{
private:
	XmlParserEstado* estadoInicial;
	XmlParserEstado* estadoActual;
	deque<string*>* nodosProcesados;

	string abrirNodo(Elemento* elemento, string indent);
	string cerrarNodo(Elemento* elemento, string indent);
	string procesarNodo(Elemento* elemento, string indent);

	void procesarLineaALinea(string textoAProcesar, 
						 unsigned int inicio, unsigned int contadorLinea);

public:
	XmlParser(void);
	virtual ~XmlParser(void);

	virtual DomTree* toDom(string texto);
	virtual string toString(DomTree* domTree);
};

#endif
