#ifndef _LOG_H_
#define _LOG_H_

#define _CRT_SECURE_NO_DEPRECATE 1

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>

#include "Respuesta.h"

using namespace std;

class Log {
private:
	string nombreArchivo;
	ofstream* archivo;

	string getFecha();

public:
	Log(string nombreArchivo);
	virtual ~Log(void);

	void escribir(Respuesta* respuesta);
	void escribir(string mensaje);
};

#endif //_LOG_H_
