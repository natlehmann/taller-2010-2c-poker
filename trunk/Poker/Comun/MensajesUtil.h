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
	static string concatMensaje(char* partes[]);
	static bool sonIguales(string primero, string segundo);

	/**
	* Devuelve true si el texto recibido tiene tamaño 0 o està formado por espacios
	*/
	static bool esVacio(string texto);

	/**
	* Elimina espacios en blanco antes y despues del texto recibido
	*/
	static string trim(string texto);

	static string intToString(int value);

	template < class T >
	static string toString(const T &arg);

};

#endif