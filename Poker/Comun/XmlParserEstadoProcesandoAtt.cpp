
#include "XmlParserEstadoProcesandoAtt.h"

XmlParserEstadoProcesandoAtt::XmlParserEstadoProcesandoAtt(deque<string*>* nodosProcesados) 
	: XmlParserEstado(nodosProcesados)
{
}

XmlParserEstadoProcesandoAtt::~XmlParserEstadoProcesandoAtt(void)
{
}

XmlParserEstado* XmlParserEstadoProcesandoAtt::procesarFragmento() {
	this->setInicioTexto(this->getTextoAProcesar().size());
	return this;
}