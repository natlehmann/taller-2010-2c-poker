#ifndef _MENSAJESUTIL_H__
#define _MENSAJESUTIL_H__

#define _CRT_SECURE_NO_DEPRECATE 1

#define countof(X) ( (size_t) ( sizeof(X)/sizeof*(X) ) )

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <sstream>



using namespace std;
 

class MensajesUtil{

public:
	static char* concatMensaje(char* partes[]);

	template < class T >
	static char* toString(const T &arg);

};

#endif