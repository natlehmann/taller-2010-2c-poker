
#include "XmlParserEstadoProcesandoAtt.h"


XmlParserEstadoProcesandoAtt::XmlParserEstadoProcesandoAtt(deque<string*>* nodosProcesados) 
	: XmlParserEstado(nodosProcesados)
{
	this->cerrandoInline = new XmlParserEstadoCerrandoInline(nodosProcesados);
	this->dentroTag = new XmlParserEstadoDentroTag(nodosProcesados);
}

XmlParserEstadoProcesandoAtt::~XmlParserEstadoProcesandoAtt(void)
{
	delete(this->cerrandoInline);
	delete(this->dentroTag);
}

XmlParserEstado* XmlParserEstadoProcesandoAtt::procesarFragmento() {
	
	// busco primer caracter distinto de espacio
	unsigned int indiceInicial = this->getTextoAProcesar().find_first_not_of(
		" ",this->getInicioTexto());

	if (indiceInicial < this->getTextoAProcesar().size()) {
		// busco signo igual
		unsigned int indiceIgual = this->getTextoAProcesar().find(
			XML_OPEN_ATTR, indiceInicial);

		if (indiceIgual == string::npos) {
			throw ParserException(
				"Error en linea XX. Se esperaba el signo '=' y comillas en el valor de un atributo.");
		}

		unsigned int indiceFinal = this->getTextoAProcesar().find(
			XML_CLOSE_ATTR,indiceIgual + string(XML_OPEN_ATTR).size());

		if (indiceFinal == string::npos) {
			throw ParserException(
				"Error en linea XX. Faltan comillas de cierre en el valor de un atributo.");
		}

		string clave = this->getTextoAProcesar().substr(indiceInicial);
		clave.erase(indiceIgual - indiceInicial);
		clave = MensajesUtil::trim(clave);

		string valor = this->getTextoAProcesar().substr(
			indiceIgual + string(XML_OPEN_ATTR).size(), indiceFinal);
		valor.erase(indiceFinal - (indiceIgual + string(XML_OPEN_ATTR).size()));


		try {
			this->getElementoActual()->agregarAtributo(clave, valor);

			XmlParserEstado* siguienteEstado = this;

			this->setInicioTexto(indiceFinal + string(XML_CLOSE_ATTR).size());

			if (!this->terminado()) {

				unsigned int indAnyChar = this->getTextoAProcesar().find_first_not_of(
					" ", this->getInicioTexto());
				unsigned int indClose = this->getTextoAProcesar().find(
					XML_CLOSE, this->getInicioTexto());
				unsigned int indCloseInline = this->getTextoAProcesar().find(
				XML_CLOSE_TAG_INLINE, this->getInicioTexto());

				if ((indClose < indCloseInline) && (indClose <= indAnyChar) 
					&& (indClose < this->getTextoAProcesar().size())) {
					siguienteEstado = this->dentroTag;

				} else {

					if ((indCloseInline < indClose) && (indCloseInline <= indAnyChar)
						&& (indCloseInline < this->getTextoAProcesar().size())) {
						siguienteEstado = this->cerrandoInline;				
					} 
				}
			}

			siguienteEstado->setElementoActual(this->getElementoActual());
			siguienteEstado->setTextoAProcesar(this->getTextoAProcesar());
			siguienteEstado->setNumeroLinea(this->getNumeroLinea());
			siguienteEstado->setInicioTexto(this->getInicioTexto());

			return siguienteEstado;

		} catch(ParserException& e) {
			throw ParserException("Error en linea XX. " + e.getMensaje());
		}

	} else {
		//no encontre ningun caracter distinto de espacio
		this->setInicioTexto(this->getTextoAProcesar().size());
		return this;
	}
}


