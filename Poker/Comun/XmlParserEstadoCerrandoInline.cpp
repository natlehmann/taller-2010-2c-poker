
#include "XmlParserEstadoCerrandoInline.h"

XmlParserEstadoCerrandoInline::XmlParserEstadoCerrandoInline(deque<string*>* nodosProcesados) 
	: XmlParserEstado(nodosProcesados)
{
}

XmlParserEstadoCerrandoInline::~XmlParserEstadoCerrandoInline(void)
{
}

XmlParserEstado* XmlParserEstadoCerrandoInline::procesarFragmento() {
	this->setInicioTexto(this->getTextoAProcesar().size());
	return this;
}
