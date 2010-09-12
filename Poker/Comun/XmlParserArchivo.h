#ifndef _XMLPARSERARCHIVO_H__
#define _XMLPARSERARCHIVO_H__

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include <list>
#include <set>
#include <map>
#include <deque>
#include <fstream>

#include "XmlParser.h"

class XmlParserArchivo : public XmlParser
{
private:
	string nombreArchivo;
	bool finArchivo;
	bool inicializado;
	bool validado;
	ifstream* archivo;
	DomTree* arbol;
	unsigned int contadorLinea;

	void setNombreArchivo(string nombreArchivo);
	void procesarArchivo();
	void procesarLinea(string linea);

public:
	XmlParserArchivo(string nombreArchivo);
	virtual ~XmlParserArchivo(void);

	/**
	* Procesa el archivo recibido por parametro o el que se haya seteado en 
	* el contructor. El parametro nombreArchivo puede ser vacio.
	*/
	virtual DomTree* toDom(string nombreArchivo);

	/**
	* Devuelve un arbol conteniendo el siguiente elemento en el archivo
	* procesado o NULL en caso de que se haya llegado al fin de archivo.
	*/
	DomTree* getSiguiente();

};

#endif
