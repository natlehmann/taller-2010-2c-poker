
#include "XmlParserEstadoCerrandoInline.h"
#include "XmlParserEstadoInicial.h"


XmlParserEstadoCerrandoInline::XmlParserEstadoCerrandoInline(deque<string*>* nodosProcesados) 
	: XmlParserEstado(nodosProcesados)
{
	this->inicial = NULL;
}

XmlParserEstadoCerrandoInline::~XmlParserEstadoCerrandoInline(void)
{
	if (this->inicial != NULL) {
		delete(this->inicial);
	}
}

XmlParserEstado* XmlParserEstadoCerrandoInline::procesarFragmento() {

	this->faltaProcesar = false;

	// sacamos el elemento de la pila de control
	delete(this->getNodosProcesados()->back());
	this->getNodosProcesados()->pop_back();

	// subo un nivel en el arbol
	this->setElementoActual(this->getElementoActual()->getPadre());

	this->getInicial()->setElementoActual(this->getElementoActual());
	this->getInicial()->setTextoAProcesar(this->getTextoAProcesar());
	this->getInicial()->setNumeroLinea(this->getNumeroLinea());
	this->getInicial()->setInicioTexto(this->getInicioTexto());

	return this->getInicial();
}

void XmlParserEstadoCerrandoInline::setInicioTexto(unsigned int inicio) {
	XmlParserEstado::setInicioTexto(inicio);
	this->faltaProcesar = true;
}

bool XmlParserEstadoCerrandoInline::terminado() {
	return this->faltaProcesar;
}

XmlParserEstadoInicial* XmlParserEstadoCerrandoInline::getInicial() {
	if (this->inicial == NULL) {
		this->inicial = new XmlParserEstadoInicial(this->getNodosProcesados());
	}

	return this->inicial;
}
