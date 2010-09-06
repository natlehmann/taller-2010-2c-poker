
#include "XmlParserEstadoCerrandoInline.h"


XmlParserEstadoCerrandoInline::XmlParserEstadoCerrandoInline(deque<string*>* nodosProcesados) 
	: XmlParserEstado(nodosProcesados)
{
	//this->inicial = new XmlParserEstadoInicial(nodosProcesados);
}

XmlParserEstadoCerrandoInline::~XmlParserEstadoCerrandoInline(void)
{
	//delete(this->inicial);
}

XmlParserEstado* XmlParserEstadoCerrandoInline::procesarFragmento() {
	this->setInicioTexto(this->getTextoAProcesar().size());
	return this;
}
