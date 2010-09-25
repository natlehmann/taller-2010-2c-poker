#ifndef _RECURSOSAPLICACION_H__
#define _RECURSOSAPLICACION_H__

#define _CRT_SECURE_NO_DEPRECATE 1

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "Properties.h"

using namespace std;

class RecursosAplicacion
{
private:
	RecursosAplicacion(void);
	static Properties parserConfigProperties;

public:
	~RecursosAplicacion(void);

	static Properties* getParserConfigProperties();
};

#endif
