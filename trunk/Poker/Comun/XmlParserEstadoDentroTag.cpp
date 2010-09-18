
#include "XmlParserEstadoDentroTag.h"
#include "XmlParserEstadoInicial.h"


XmlParserEstadoDentroTag::XmlParserEstadoDentroTag(deque<string*>* nodosProcesados) 
	: XmlParserEstado(nodosProcesados)
{
	this->procesandoTexto = NULL;
	this->cerrandoTag = NULL;
	this->inicial = NULL;
}

XmlParserEstadoDentroTag::XmlParserEstadoDentroTag(
	deque<string*>* nodosProcesados, XmlParserEstadoInicial* inicial,
		XmlParserEstadoProcesandoTxt* procesandoTexto, 
		XmlParserEstadoCerrandoTag* cerrandoTag) : XmlParserEstado(nodosProcesados)
{
	this->procesandoTexto = procesandoTexto;
	this->cerrandoTag = cerrandoTag;
	this->inicial = inicial;
}

XmlParserEstadoDentroTag::~XmlParserEstadoDentroTag(void)
{
}

XmlParserEstado* XmlParserEstadoDentroTag::procesarFragmento() {

	XmlParserEstado* siguienteEstado = this->getProcesandoTexto();
	
	if (!this->terminado()) {

		unsigned int indAnyChar = this->getTextoAProcesar().find_first_not_of(
			" ", this->getInicioTexto());
		unsigned int indOpen = this->getTextoAProcesar().find(
			XML_OPEN, this->getInicioTexto());
		unsigned int indCloseTag = this->getTextoAProcesar().find(
			XML_CLOSE_TAG, this->getInicioTexto());

		if ((indOpen < indCloseTag) && (indOpen <= indAnyChar) 
			&& (indOpen < this->getTextoAProcesar().size())) {
			siguienteEstado = this->getInicial();

		} else {

			// si son iguales los indices, gana indCloseTag (<=)
			if ((indCloseTag <= indOpen) && (indCloseTag <= indAnyChar)
				&& (indCloseTag < this->getTextoAProcesar().size())) {
				siguienteEstado = this->getCerrandoTag();	
				this->setInicioTexto(indCloseTag + string(XML_CLOSE_TAG).size());
			} 
		}
	
	} else {
		// si se acabo la linea, continuo en el mismo estado
		siguienteEstado = this;
	}


	siguienteEstado->setElementoActual(this->getElementoActual());
	siguienteEstado->setTextoAProcesar(this->getTextoAProcesar());
	siguienteEstado->setNumeroLinea(this->getNumeroLinea());
	siguienteEstado->setInicioTexto(this->getInicioTexto());

	return siguienteEstado;
}

XmlParserEstadoInicial* XmlParserEstadoDentroTag::getInicial() {
	return this->inicial;
}

XmlParserEstadoCerrandoTag* XmlParserEstadoDentroTag::getCerrandoTag() {
	return this->cerrandoTag;
}

XmlParserEstadoProcesandoTxt* XmlParserEstadoDentroTag::getProcesandoTexto() {
	return this->procesandoTexto;
}
