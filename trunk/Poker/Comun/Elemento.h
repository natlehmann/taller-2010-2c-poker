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
	string nombre;
	string texto;
	map<string,string>* atributos;
	set<string*>* atributosPermitidos;
	set<string*>* hijosPermitidos;
	int numeroDeLinea;

	list<Elemento*>* hijos;
	Elemento* padre;

	void setPadre(Elemento* padre);
	bool esPermitido(string nombre, set<string*>* conjunto);

public:
	Elemento(string nombre);
	virtual ~Elemento(void);

	void setHijosPermitidos(set<string*>* hijosPermitidos);
	void setAtributosPermitidos(set<string*>* atributosPermitidos);

	void agregarAtributo(string clave, string valor);
	string getAtributo(string clave);
	map<string,string>* getAtributos();
	
	void setTexto(string texto);
	string getTexto();

	string getNombre();

	int getNumeroDeLinea();
	void setNumeroDeLinea(int numero);

	Elemento* getPadre();
	bool isRaiz();

	Elemento* agregarHijo(string nombreHijo);
	list<Elemento*>* getHijos();

	bool esHijoPermitido(string nombreHijo);
	bool esAtributoPermitido(string atributo);

};

#endif
