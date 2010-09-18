
#include "XmlParserEstadoCerrandoTag.h"
#include "XmlParserEstadoInicial.h"

XmlParserEstadoCerrandoTag::XmlParserEstadoCerrandoTag(deque<string*>* nodosProcesados) 
	: XmlParserEstado(nodosProcesados)
{
	this->inicial = NULL;	
}

XmlParserEstadoCerrandoTag::XmlParserEstadoCerrandoTag(
	deque<string*>* nodosProcesados, XmlParserEstadoInicial* inicial)
		: XmlParserEstado(nodosProcesados)
{
	this->inicial = inicial;	
}

XmlParserEstadoCerrandoTag::~XmlParserEstadoCerrandoTag(void)
{
}

XmlParserEstado* XmlParserEstadoCerrandoTag::procesarFragmento() {

	unsigned int indiceFinal = this->getTextoAProcesar().find(XML_CLOSE, this->getInicioTexto());

	if (indiceFinal < this->getTextoAProcesar().size()) {

		string tag = this->getTextoAProcesar().substr(this->getInicioTexto(), indiceFinal);
		tag.erase(indiceFinal - this->getInicioTexto());
		tag = MensajesUtil::trim(tag);

		if (!this->getNodosProcesados()->empty()) {

			// control
			string* ultimoProcesado = this->getNodosProcesados()->back();
			this->getNodosProcesados()->pop_back();

			if (!MensajesUtil::sonIguales(tag, *ultimoProcesado)) {
				string msg = "Error en linea " + MensajesUtil::intToString(this->getNumeroLinea())
					+ ". Se esperaba el cierre del tag " + *ultimoProcesado + " y se encontro '" + tag 
					+ "'.";
				delete(ultimoProcesado);
				throw ParserException(msg);
			}

			
			delete(ultimoProcesado);

		} else {
			throw ParserException("Error en linea " + MensajesUtil::intToString(this->getNumeroLinea())
				+ ". Se encontro el cierre de un tag que nunca se abrio: " + tag);
		}

		// subo un nivel en el arbol
		this->setElementoActual(this->getElementoActual()->getPadre());

		this->setInicioTexto(indiceFinal + string(XML_CLOSE).size());

		this->getInicial()->setElementoActual(this->getElementoActual());
		this->getInicial()->setTextoAProcesar(this->getTextoAProcesar());
		this->getInicial()->setNumeroLinea(this->getNumeroLinea());
		this->getInicial()->setInicioTexto(this->getInicioTexto());

		return this->getInicial();
	
	} else {
		throw ParserException("Error en la linea " + MensajesUtil::intToString(this->getNumeroLinea())
			+ ". Se esperaba caracter de fin de tag.");
	}	
}


XmlParserEstadoInicial* XmlParserEstadoCerrandoTag::getInicial() {
	return this->inicial;
}
