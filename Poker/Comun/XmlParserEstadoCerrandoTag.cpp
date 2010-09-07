
#include "XmlParserEstadoCerrandoTag.h"

XmlParserEstadoCerrandoTag::XmlParserEstadoCerrandoTag(deque<string*>* nodosProcesados) 
	: XmlParserEstado(nodosProcesados)
{
	
}

XmlParserEstadoCerrandoTag::~XmlParserEstadoCerrandoTag(void)
{
}

XmlParserEstado* XmlParserEstadoCerrandoTag::procesarFragmento() {

	this->setInicioTexto(this->getTextoAProcesar().size());
	return this;
}
