#ifndef _RECURSOSSERVIDOR_H__
#define _RECURSOSSERVIDOR_H__

#define _CRT_SECURE_NO_DEPRECATE 1

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "Properties.h"
#include "Log.h"

using namespace std;

class RecursosServidor
{
private:
	static Properties config;
	static Log log;
	RecursosServidor(void);

public:
	virtual ~RecursosServidor(void);

	static Properties* getConfig();
	static Log* getLog();
};

#endif //_RECURSOSSERVIDOR_H__

