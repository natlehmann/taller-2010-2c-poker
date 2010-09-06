
#include "XmlParserEstadoDentroTag.h"

XmlParserEstadoDentroTag::XmlParserEstadoDentroTag(deque<string*>* nodosProcesados) 
	: XmlParserEstado(nodosProcesados)
{
}

XmlParserEstadoDentroTag::~XmlParserEstadoDentroTag(void)
{
}

XmlParserEstado* XmlParserEstadoDentroTag::procesarFragmento() {
	this->setInicioTexto(this->getTextoAProcesar().size());
	return this;
}
