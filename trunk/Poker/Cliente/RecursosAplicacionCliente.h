#ifndef _RECURSOSAPLICACIONCLIENTE_H__
#define _RECURSOSAPLICACIONCLIENTE_H__

#define _CRT_SECURE_NO_DEPRECATE 1

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "Properties.h"
#include "Log.h"

using namespace std;

class RecursosAplicacionCliente
{
private:
	RecursosAplicacionCliente(void);

	static Properties parserConfig;
	static Properties config;
	static Log log;

public:
	~RecursosAplicacionCliente(void);

	static Properties* getParserConfig();
	static Properties* getConfig();
	static Log* getLog();
};

#endif //_RECURSOSAPLICACIONCLIENTE_H__
