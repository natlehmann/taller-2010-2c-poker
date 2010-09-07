
#include "XmlParserEstadoInicial.h"
#include "MensajesUtil.h"


XmlParserEstadoInicial::XmlParserEstadoInicial(deque<string*>* nodosProcesados) 
	: XmlParserEstado(nodosProcesados)
{
	this->abriendoTag = NULL;
}

XmlParserEstadoInicial::~XmlParserEstadoInicial(void)
{
	if (this->abriendoTag != NULL) {
		delete(this->abriendoTag);
	}
}

XmlParserEstado* XmlParserEstadoInicial::procesarFragmento() {

	unsigned int indice = this->getTextoAProcesar().find(XML_OPEN, this->getInicioTexto());

	if (indice < this->getTextoAProcesar().size()) {
		// verifico si todo lo que hay antes del tag de apertura son espacios
		bool esVacio = MensajesUtil::esVacio(
			this->getTextoAProcesar().substr(this->getInicioTexto(),indice));

		if (!esVacio) {
			string msg = "Se encontraron caracteres invalidos antes del inicio de un tag en la linea " 
				+ MensajesUtil::intToString(this->getNumeroLinea()); 
			//string msg = "Se encontraron caracteres invalidos antes del inicio de un tag en la linea ";
			string invalido = this->getTextoAProcesar().substr(this->getInicioTexto(),indice);
			string msg2= msg + ". Caracteres: " + invalido;
			throw ParserException(msg2);
		}

		this->getAbriendoTag()->setInicioTexto(indice + 1);
		this->getAbriendoTag()->setTextoAProcesar(this->getTextoAProcesar());
		this->getAbriendoTag()->setNumeroLinea(this->getNumeroLinea());
		this->getAbriendoTag()->setElementoActual(this->getElementoActual());

		return this->getAbriendoTag();
	
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

	return this;

}


XmlParserEstadoAbriendoTag* XmlParserEstadoInicial::getAbriendoTag() {
	
	if (this->abriendoTag == NULL) {
		this->abriendoTag = new XmlParserEstadoAbriendoTag(this->getNodosProcesados());
	}

	return this->abriendoTag;
}
