
#include "XmlParserEstadoInicial.h"
#include "MensajesUtil.h"


XmlParserEstadoInicial::XmlParserEstadoInicial(deque<string*>* nodosProcesados) 
	: XmlParserEstado(nodosProcesados)
{
	this->abriendoTag = NULL;
	this->cerrandoTag = NULL;
}

XmlParserEstadoInicial::~XmlParserEstadoInicial(void)
{
	if (this->abriendoTag != NULL) {
		delete(this->abriendoTag);
	}
	if (this->cerrandoTag != NULL) {
		delete(this->cerrandoTag);
	}
}

XmlParserEstado* XmlParserEstadoInicial::procesarFragmento() {

	unsigned int indice = this->getTextoAProcesar().find(XML_OPEN, this->getInicioTexto());
	unsigned int indiceClose = this->getTextoAProcesar().find(
		XML_CLOSE_TAG, this->getInicioTexto());

	XmlParserEstado* siguienteEstado = this->getAbriendoTag();

	if (indiceClose != string::npos && indiceClose <= indice) {
		siguienteEstado = this->getCerrandoTag();
		this->setInicioTexto(indiceClose + string(XML_CLOSE_TAG).size());

	} else {

		if (indice < this->getTextoAProcesar().size()) {
			// verifico si todo lo que hay antes del tag de apertura son espacios
			string textoAnterior = this->getTextoAProcesar().substr(this->getInicioTexto(),indice);
			textoAnterior.erase(indice - this->getInicioTexto());
			bool esVacio = MensajesUtil::esVacio(textoAnterior);

			if (!esVacio) {
				string msg = "Se encontraron caracteres invalidos antes del inicio de un tag en la linea " 
					+ MensajesUtil::intToString(this->getNumeroLinea()); 
				string invalido = this->getTextoAProcesar().substr(this->getInicioTexto(),indice);
				string msg2= msg + ". Caracteres: " + invalido;
				throw ParserException(msg2);
			}

			this->setInicioTexto(indice + string(XML_OPEN).size());

		} else {
			// si no encontre la apertura de tag y la linea no esta vacia
			bool esVacio = MensajesUtil::esVacio(
				this->getTextoAProcesar().substr(this->getInicioTexto()));

			if (!esVacio) {
				string msg = "Se encontraron caracteres invalidos en la linea " 
					+ MensajesUtil::intToString(this->getNumeroLinea());
				string msg2 = msg + ". Se esperaba inicio de tag.";
				throw ParserException(msg2);

			} else {
				this->setInicioTexto(this->getTextoAProcesar().size() + 1);
			}
		}


	}

	siguienteEstado->setInicioTexto(this->getInicioTexto());
	siguienteEstado->setTextoAProcesar(this->getTextoAProcesar());
	siguienteEstado->setNumeroLinea(this->getNumeroLinea());
	siguienteEstado->setElementoActual(this->getElementoActual());

	return siguienteEstado;

}


XmlParserEstadoAbriendoTag* XmlParserEstadoInicial::getAbriendoTag() {
	
	if (this->abriendoTag == NULL) {
		this->abriendoTag = new XmlParserEstadoAbriendoTag(this->getNodosProcesados());
	}

	return this->abriendoTag;
}


XmlParserEstadoCerrandoTag* XmlParserEstadoInicial::getCerrandoTag() {
	if (this->cerrandoTag == NULL) {
		this->cerrandoTag = new XmlParserEstadoCerrandoTag(this->getNodosProcesados());
	}

	return this->cerrandoTag;
}
