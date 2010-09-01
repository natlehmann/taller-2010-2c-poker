#ifndef _ELEMENTO_H__
#define _ELEMENTO_H__

#define _CRT_SECURE_NO_DEPRECATE 1

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <map>
#include <set>
#include <list>

using namespace std;

class Elemento
{
private:
	char* nombre;
	char* texto;
	map<char*,char*>* atributos;
	set<char*>* atributosPermitidos;
	set<char*>* hijosPermitidos;

	list<Elemento*>* hijos;
	Elemento* padre;

	void setPadre(Elemento* padre);

public:
	Elemento(char* nombre);
	virtual ~Elemento(void);

	void setHijosPermitidos(set<char*>* hijosPermitidos);
	void setAtributosPermitidos(set<char*>* atributosPermitidos);

	void agregarAtributo(char* clave, char* valor);
	char* getAtributo(char* clave);
	map<char*,char*>* getAtributos();
	
	void setTexto(char* texto);
	char* getTexto();

	char* getNombre();

	Elemento* getPadre();
	bool isRaiz();

	Elemento* agregarHijo(char* nombreHijo);
	list<Elemento*>* getHijos();

};

#endif
