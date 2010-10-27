#ifndef _RECURSOSCLIENTE_H__
#define _RECURSOSCLIENTE_H__

#define _CRT_SECURE_NO_DEPRECATE 1

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "Properties.h"
#include "Log.h"

using namespace std;

class RecursosCliente
{
private:
	static Properties config;
	static Log log;

	RecursosCliente(void);

public:
	virtual ~RecursosCliente(void);

	static Properties* getConfig();
	static Log* getLog();
};

#endif //_RECURSOSCLIENTE_H__

