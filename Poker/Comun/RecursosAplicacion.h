#ifndef _RECURSOSAPLICACION_H__
#define _RECURSOSAPLICACION_H__

#define _CRT_SECURE_NO_DEPRECATE 1

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "Properties.h"
#include "Log.h"

using namespace std;

class RecursosAplicacion
{
private:
	RecursosAplicacion(void);
	static Properties parserConfigProperties;
	static Properties clienteConfigProperties;
	static Properties servidorConfigProperties;

	static Log logErroresCliente;
	static Log logErroresServidor;

public:
	~RecursosAplicacion(void);

	static Properties* getParserConfigProperties();
	static Properties* getClienteConfigProperties();
	static Properties* getServidorConfigProperties();

	static Log* getLogErroresCliente();
	static Log* getLogErroresServidor();
};

#endif
