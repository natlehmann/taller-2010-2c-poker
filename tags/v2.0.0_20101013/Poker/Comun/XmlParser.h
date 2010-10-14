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

class XmlParserEstadoInicial;
class XmlParserEstadoAbriendoTag;
class XmlParserEstadoCerrandoInline;
class XmlParserEstadoCerrandoTag;
class XmlParserEstadoDentroTag;
class XmlParserEstadoProcesandoAtt;
class XmlParserEstadoProcesandoTxt;

class XmlParser : public Parser
{
protected:
	XmlParserEstadoInicial* estadoInicial;
	XmlParserEstadoAbriendoTag* abriendoTag;
	XmlParserEstadoCerrandoInline* cerrandoInline;
	XmlParserEstadoCerrandoTag* cerrandoTag;
	XmlParserEstadoDentroTag* dentroTag;
	XmlParserEstadoProcesandoAtt* procesandoAtt;
	XmlParserEstadoProcesandoTxt* procesandoTxt;

	string nombreConfiguracion;


	XmlParserEstado* estadoActual;
	deque<string*>* nodosProcesados;

	string abrirNodo(Elemento* elemento, string indent);
	string cerrarNodo(Elemento* elemento, string indent);
	string procesarNodo(Elemento* elemento, string indent);

	void procesarLineaALinea(string textoAProcesar, 
						 unsigned int inicio, unsigned int contadorLinea);
	void validarFinal();

	void guardarNombreConfiguracion(string nombreConfiguracion);

public:
	XmlParser(void);
	virtual ~XmlParser(void);

	/**
	* Parsea un string devolviendo un DomTree para la configuracion default
	*/
	virtual DomTree* toDom(string texto);

	/**
	* Parsea un string devolviendo un DomTree que responde a la configuracion recibida
	* por parametro
	*/
	virtual DomTree* toDom(string texto, string nombreConfiguracion);

	virtual string toString(DomTree* domTree);
};

#endif
