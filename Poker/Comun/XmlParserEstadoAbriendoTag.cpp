
#include "XmlParserEstadoAbriendoTag.h"



XmlParserEstadoAbriendoTag::XmlParserEstadoAbriendoTag(deque<string*>* nodosProcesados) 
	: XmlParserEstado(nodosProcesados)
{
	this->cerrandoInline = NULL;
	this->dentroTag = NULL;
	this->procesandoAtt = NULL;
}

XmlParserEstadoAbriendoTag::~XmlParserEstadoAbriendoTag(void)
{
	if (this->cerrandoInline != NULL) {
		delete(this->cerrandoInline);
	}

	if (this->dentroTag != NULL) {
		delete(this->dentroTag);
	}

	if (this->procesandoAtt != NULL) {
		delete(this->procesandoAtt);
	}
}

XmlParserEstado* XmlParserEstadoAbriendoTag::procesarFragmento() {

	// busco primer caracter distinto de espacio
	unsigned int indiceInicial = this->getTextoAProcesar().find_first_not_of(
		" ",this->getInicioTexto());

	if (indiceInicial < this->getTextoAProcesar().size()) {
		// busco proximo espacio
		unsigned int indiceFinal = this->getTextoAProcesar().find(" ",indiceInicial);

		unsigned int indClose = this->getTextoAProcesar().find(XML_CLOSE, indiceInicial);
		unsigned int indCloseInline = this->getTextoAProcesar().find(
				XML_CLOSE_TAG_INLINE, indiceInicial);

		if (indClose < indiceFinal) {
			indiceFinal = indClose;
		}

		if (indCloseInline < indiceFinal) {
			indiceFinal = indCloseInline;
		}

		if (indiceFinal > this->getTextoAProcesar().size()) {
			indiceFinal = this->getTextoAProcesar().size();
		}

		string nombreElemento = this->getTextoAProcesar().substr(indiceInicial, indiceFinal);
		nombreElemento.erase(indiceFinal - indiceInicial);

		try {
			this->setElementoActual(this->getElementoActual()->agregarHijo(nombreElemento));
			this->getNodosProcesados()->push_back(new string(nombreElemento));
			this->getElementoActual()->setNumeroDeLinea(this->getNumeroLinea());

			XmlParserEstado* siguienteEstado = this->getProcesandoAtt();
			this->setInicioTexto(indiceFinal);

			if (!this->terminado()) {

				unsigned int indAnyChar = this->getTextoAProcesar().find_first_not_of(
					" ", this->getInicioTexto());			

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
			}

			siguienteEstado->setElementoActual(this->getElementoActual());
			siguienteEstado->setTextoAProcesar(this->getTextoAProcesar());
			siguienteEstado->setNumeroLinea(this->getNumeroLinea());
			siguienteEstado->setInicioTexto(this->getInicioTexto());

			return siguienteEstado;

		} catch(ParserException& e) {
			throw ParserException("Error en linea " 
				+ MensajesUtil::intToString(this->getNumeroLinea()) + ". " + e.getMensaje(),
				e.getError().getId());
		}

	} else {
		//no encontre ningun caracter distinto de espacio
		this->setInicioTexto(this->getTextoAProcesar().size());
		return this;
	}
}

XmlParserEstadoCerrandoInline* XmlParserEstadoAbriendoTag::getCerrandoInline() {
	
	if (this->cerrandoInline == NULL) {
		this->cerrandoInline = new XmlParserEstadoCerrandoInline(this->getNodosProcesados());
	}

	return this->cerrandoInline;
}

XmlParserEstadoDentroTag* XmlParserEstadoAbriendoTag::getDentroTag() {
	
	if (this->dentroTag == NULL) {
		this->dentroTag = new XmlParserEstadoDentroTag(this->getNodosProcesados());
	}

	return this->dentroTag;
}

XmlParserEstadoProcesandoAtt* XmlParserEstadoAbriendoTag::getProcesandoAtt() {
	
	if (this->procesandoAtt == NULL) {
		this->procesandoAtt = new XmlParserEstadoProcesandoAtt(this->getNodosProcesados());
	}

	return this->procesandoAtt;
}


