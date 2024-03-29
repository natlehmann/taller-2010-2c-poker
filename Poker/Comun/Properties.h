#ifndef _PROPERTIES_H__
#define _PROPERTIES_H__

#define _CRT_SECURE_NO_DEPRECATE 1

#define PROP_SEPARADOR "="
#define PROP_COMENTARIO "#"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include <map>

using namespace std;

class Properties
{
private:
	string nombreArchivo;
	ifstream* archivo;
	map<string,string>* properties;

	void inicializar();
	void procesarLinea(string linea);

public:
	Properties(string nombreArchivo);
	virtual ~Properties(void);

	string get(string clave);
	void setNombreArchivo(string nombreArchivo);
};

#endif
