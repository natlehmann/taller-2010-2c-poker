
#include "XmlParserEstadoProcesandoTxt.h"

XmlParserEstadoProcesandoTxt::XmlParserEstadoProcesandoTxt(deque<string*>* nodosProcesados) 
	: XmlParserEstado(nodosProcesados)
{
}

XmlParserEstadoProcesandoTxt::~XmlParserEstadoProcesandoTxt(void)
{
}

XmlParserEstado* XmlParserEstadoProcesandoTxt::procesarFragmento() {

	this->setInicioTexto(this->getTextoAProcesar().size());
	return this;
}
