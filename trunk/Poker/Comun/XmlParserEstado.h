#ifndef _XMLPARSERESTADO_H__
#define _XMLPARSERESTADO_H__

#define _CRT_SECURE_NO_DEPRECATE 1

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include <deque>

#include "Elemento.h"
#include "MensajesUtil.h"
#include "PokerException.h"

using namespace std;

class XmlParserEstado
{

private:
	deque<string*>* nodosProcesados;
	Elemento* elementoActual;
	string textoAProcesar;
	unsigned int inicioTexto;
	int numeroLinea;

public:
	XmlParserEstado(deque<string*>* nodosProcesados);
	virtual ~XmlParserEstado(void);

	void setElementoActual(Elemento* elemento);
	Elemento* getElementoActual();

	void setTextoAProcesar(string texto);
	string getTextoAProcesar();

	void setInicioTexto(unsigned int inicio);
	unsigned int getInicioTexto();

	void setNumeroLinea(int numero);
	int getNumeroLinea();

	deque<string*>* getNodosProcesados();

	virtual XmlParserEstado* procesarFragmento() = 0;

	bool terminado();

};

#endif