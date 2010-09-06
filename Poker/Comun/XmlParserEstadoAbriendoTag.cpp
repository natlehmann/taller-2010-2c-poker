
#include "XmlParserEstadoAbriendoTag.h"



XmlParserEstadoAbriendoTag::XmlParserEstadoAbriendoTag(deque<string*>* nodosProcesados) 
	: XmlParserEstado(nodosProcesados)
{
	this->cerrandoInline = new XmlParserEstadoCerrandoInline(nodosProcesados);
	this->dentroTag = new XmlParserEstadoDentroTag(nodosProcesados);
	this->procesandoAtt = new XmlParserEstadoProcesandoAtt(nodosProcesados);
}

XmlParserEstadoAbriendoTag::~XmlParserEstadoAbriendoTag(void)
{
	delete(this->cerrandoInline);
	delete(this->dentroTag);
	delete(this->procesandoAtt);
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
			this->getNodosProcesados()->insert(
				this->getNodosProcesados()->end(), new string(nombreElemento));

			XmlParserEstado* siguienteEstado = this->procesandoAtt;

			this->setInicioTexto(indiceFinal + 1);

			if (!this->terminado()) {

				unsigned int indAnyChar = this->getTextoAProcesar().find_first_not_of(
					" ", indiceFinal + 1);			

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


