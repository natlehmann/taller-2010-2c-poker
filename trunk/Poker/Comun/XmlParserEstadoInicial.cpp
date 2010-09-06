
#include "XmlParserEstadoInicial.h"
#include "XmlParserEstado.h"
#include "XmlParser.h"
#include "MensajesUtil.h"
#include "ParserException.h"

XmlParserEstadoInicial::XmlParserEstadoInicial(deque<string*>* nodosProcesados) 
	: XmlParserEstado(nodosProcesados)
{
	this->abriendoTag = new XmlParserEstadoAbriendoTag(nodosProcesados);
}

XmlParserEstadoInicial::~XmlParserEstadoInicial(void)
{
	delete(this->abriendoTag);
}

XmlParserEstado* XmlParserEstadoInicial::procesarFragmento() {

	unsigned int indice = this->getTextoAProcesar().find(XML_OPEN, this->getInicioTexto());

	if (indice < this->getTextoAProcesar().size()) {
		// verifico si todo lo que hay antes del tag de apertura son espacios
		bool esVacio = MensajesUtil::esVacio(
			this->getTextoAProcesar().substr(this->getInicioTexto(),indice));

		if (!esVacio) {
			//string msg = "Se encontraron caracteres invalidos antes del inicio de un tag en la linea " 
			//	+ this->getNumeroLinea();
			string msg = "Se encontraron caracteres invalidos antes del inicio de un tag en la linea ";
			string invalido = this->getTextoAProcesar().substr(this->getInicioTexto(),indice);
			string msg2= msg + ". Caracteres: " + invalido;
			throw ParserException(msg2);
		}

		this->abriendoTag->setInicioTexto(indice + 1);
		this->abriendoTag->setTextoAProcesar(this->getTextoAProcesar());
		this->abriendoTag->setNumeroLinea(this->getNumeroLinea());
		this->abriendoTag->setElementoActual(this->getElementoActual());

		return this->abriendoTag;
	
	} else {
		// si no encontre la apertura de tag y la linea no esta vacia
		bool esVacio = MensajesUtil::esVacio(
			this->getTextoAProcesar().substr(this->getInicioTexto()));

		if (!esVacio) {
			string msg = "Se encontraron caracteres invalidos en la linea " ;
			string msg2 = msg + ". Se esperaba inicio de tag.";
			throw ParserException(msg2);
			//throw new ParserException(msg);

		} else {
			this->setInicioTexto(this->getTextoAProcesar().size() + 1);
		}
	}

	return this;

}
