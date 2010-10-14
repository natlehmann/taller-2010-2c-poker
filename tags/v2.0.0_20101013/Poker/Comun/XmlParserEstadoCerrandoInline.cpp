
#include "XmlParserEstadoCerrandoInline.h"
#include "XmlParserEstadoInicial.h"


XmlParserEstadoCerrandoInline::XmlParserEstadoCerrandoInline(deque<string*>* nodosProcesados) 
	: XmlParserEstado(nodosProcesados)
{
	this->inicial = NULL;
}

XmlParserEstadoCerrandoInline::XmlParserEstadoCerrandoInline(
	deque<string*>* nodosProcesados, XmlParserEstadoInicial* inicial)
	: XmlParserEstado(nodosProcesados)
{
	this->inicial = inicial;
}

XmlParserEstadoCerrandoInline::~XmlParserEstadoCerrandoInline(void)
{
}

XmlParserEstado* XmlParserEstadoCerrandoInline::procesarFragmento() {

	if (!this->getNodosProcesados()->empty()) {

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

	} else {
		throw ParserException("Error en linea " + MensajesUtil::intToString(this->getNumeroLinea())
			+ ". Se encontro el cierre de un tag que nunca se abrio.");
	}
}

void XmlParserEstadoCerrandoInline::setInicioTexto(unsigned int inicio) {
	XmlParserEstado::setInicioTexto(inicio);
	this->faltaProcesar = true;
}

bool XmlParserEstadoCerrandoInline::terminado() {
	return !this->faltaProcesar;
}

XmlParserEstadoInicial* XmlParserEstadoCerrandoInline::getInicial() {
	return this->inicial;
}
