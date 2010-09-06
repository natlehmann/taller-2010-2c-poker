
#include "XmlParserEstado.h"
#include "MensajesUtil.h"



XmlParserEstado::XmlParserEstado(deque<string*>* nodosProcesados)
{
	this->nodosProcesados = nodosProcesados;
	this->inicioTexto = 0;
	this->textoAProcesar = "\0";
}

XmlParserEstado::~XmlParserEstado(void)
{
}



void XmlParserEstado::setElementoActual(Elemento* elemento) {
	this->elementoActual = elemento;
}

Elemento* XmlParserEstado::getElementoActual() {
	return this->elementoActual;
}

void XmlParserEstado::setTextoAProcesar(string texto) {
	this->textoAProcesar = texto;
}

string XmlParserEstado::getTextoAProcesar() {
	return this->textoAProcesar;
}

void XmlParserEstado::setInicioTexto(unsigned int inicio) {
	this->inicioTexto = inicio;
}

unsigned int XmlParserEstado::getInicioTexto() {
	return this->inicioTexto;
}

void XmlParserEstado::setNumeroLinea(int numero) {
	this->numeroLinea = numero;
}

int XmlParserEstado::getNumeroLinea(){
	return this->numeroLinea;
}

bool XmlParserEstado::terminado() {
	bool terminado = true;
	if (this->getTextoAProcesar() != "\0") {	
		if (this->getInicioTexto() < this->getTextoAProcesar().size()) {
			if (!MensajesUtil::esVacio(this->getTextoAProcesar().substr(this->getInicioTexto()))) {
				terminado = false;
			}
		}
	}
	return terminado;
}

deque<string*>* XmlParserEstado::getNodosProcesados() {
	return this->nodosProcesados;
}



