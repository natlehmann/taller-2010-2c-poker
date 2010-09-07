
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

	this->setInicioTexto(this->getInicioTexto() + string(XML_CLOSE_TAG_INLINE).size());

	// sacamos el elemento de la pila de control
	this->getNodosProcesados()->pop_back();

	// subo un nivel en el arbol
	this->setElementoActual(this->getElementoActual()->getPadre());

	this->getInicial()->setElementoActual(this->getElementoActual());
	this->getInicial()->setTextoAProcesar(this->getTextoAProcesar());
	this->getInicial()->setNumeroLinea(this->getNumeroLinea());
	this->getInicial()->setInicioTexto(this->getInicioTexto());

	return this->getInicial();
}

XmlParserEstadoInicial* XmlParserEstadoCerrandoInline::getInicial() {
	if (this->inicial == NULL) {
		this->inicial = new XmlParserEstadoInicial(this->getNodosProcesados());
	}

	return this->inicial;
}
