
#include "XmlParserEstadoProcesandoAtt.h"


XmlParserEstadoProcesandoAtt::XmlParserEstadoProcesandoAtt(deque<string*>* nodosProcesados) 
	: XmlParserEstado(nodosProcesados)
{
	this->cerrandoInline = NULL;
	this->dentroTag = NULL;
}

XmlParserEstadoProcesandoAtt::XmlParserEstadoProcesandoAtt(
	deque<string*>* nodosProcesados, XmlParserEstadoDentroTag* dentroTag, 
	XmlParserEstadoCerrandoInline* cerrandoInline) : XmlParserEstado(nodosProcesados)
{
	this->cerrandoInline = cerrandoInline;
	this->dentroTag = dentroTag;
}

XmlParserEstadoProcesandoAtt::~XmlParserEstadoProcesandoAtt(void)
{
}

XmlParserEstado* XmlParserEstadoProcesandoAtt::procesarFragmento() {
	
	if (!this->terminado()) {

		XmlParserEstado* siguienteEstado = this;

		// busco primer caracter distinto de espacio
		unsigned int indAnyChar = this->getTextoAProcesar().find_first_not_of(
			" ", this->getInicioTexto());

		unsigned int indClose = this->getTextoAProcesar().find(
			XML_CLOSE, this->getInicioTexto());

		unsigned int indCloseInline = this->getTextoAProcesar().find(
		XML_CLOSE_TAG_INLINE, this->getInicioTexto());

		if ((indClose < indCloseInline) && (indClose <= indAnyChar) 
			&& (indClose < this->getTextoAProcesar().size())) {
			siguienteEstado = this->getDentroTag();
			this->setInicioTexto(indClose + string(XML_CLOSE).size());

		} else {

			if ((indCloseInline < indClose) && (indCloseInline <= indAnyChar)
				&& (indCloseInline < this->getTextoAProcesar().size())) {
				siguienteEstado = this->getCerrandoInline();
				this->setInicioTexto(indCloseInline + string(XML_CLOSE_TAG_INLINE).size());
			} 
		}

		// si estamos procesando atributos
		if (indAnyChar < indClose && indAnyChar < indCloseInline) {

			// busco signo igual
			unsigned int indiceIgual = this->getTextoAProcesar().find(
				XML_OPEN_ATTR, indAnyChar);

			if (indiceIgual == string::npos) {
				throw ParserException(
					"Error en linea " + MensajesUtil::intToString(this->getNumeroLinea()) 
					+ ". Se esperaba el signo '=' y comillas en el valor de un atributo.");
			}

			unsigned int indiceFinal = this->getTextoAProcesar().find(
				XML_CLOSE_ATTR, indiceIgual + string(XML_OPEN_ATTR).size());

			if (indiceFinal == string::npos) {
				throw ParserException(
					"Error en linea " + MensajesUtil::intToString(this->getNumeroLinea()) 
					+ ". Faltan comillas de cierre en el valor de un atributo.");
			}

			string clave = this->getTextoAProcesar().substr(indAnyChar);
			clave.erase(indiceIgual - indAnyChar);
			clave = MensajesUtil::trim(clave);

			string valor = this->getTextoAProcesar().substr(
				indiceIgual + string(XML_OPEN_ATTR).size(), indiceFinal);
			valor.erase(indiceFinal - (indiceIgual + string(XML_OPEN_ATTR).size()));

			try {
				this->getElementoActual()->agregarAtributo(clave, valor);
				this->setInicioTexto(indiceFinal + string(XML_CLOSE_ATTR).size());

			} catch(ParserException& e) {
				throw ParserException("Error en linea " + MensajesUtil::intToString(this->getNumeroLinea()) 
					+ ". " + e.getMensaje(), e.getError().getId());
			}
		}

		siguienteEstado->setElementoActual(this->getElementoActual());
		siguienteEstado->setTextoAProcesar(this->getTextoAProcesar());
		siguienteEstado->setNumeroLinea(this->getNumeroLinea());
		siguienteEstado->setInicioTexto(this->getInicioTexto());

		return siguienteEstado;

		
	} else {
		//la linea esta vacia
		this->setInicioTexto(this->getTextoAProcesar().size());
		return this;
	}
}


XmlParserEstadoCerrandoInline* XmlParserEstadoProcesandoAtt::getCerrandoInline() {
	return this->cerrandoInline;
}

XmlParserEstadoDentroTag* XmlParserEstadoProcesandoAtt::getDentroTag() {
	return this->dentroTag;
}
