
#include "XmlParserEstadoProcesandoTxt.h"
#include "XmlParserEstadoInicial.h"

XmlParserEstadoProcesandoTxt::XmlParserEstadoProcesandoTxt(deque<string*>* nodosProcesados) 
	: XmlParserEstado(nodosProcesados)
{
	this->inicial = NULL;
	this->cerrandoTag = NULL;
}

XmlParserEstadoProcesandoTxt::~XmlParserEstadoProcesandoTxt(void)
{
	if (this->inicial != NULL) {
		delete (this->inicial);
	}
	if (this->cerrandoTag != NULL) {
		delete(this->cerrandoTag);
	}
}

XmlParserEstado* XmlParserEstadoProcesandoTxt::procesarFragmento() {

	// se inicializa el buffer
	if (!this->enProceso) {
		this->enProceso = true;
		this->textoAcumulado = "";
	}

	XmlParserEstado* siguienteEstado = this;

	if (!this->terminado()) {

		unsigned int indOpen = this->getTextoAProcesar().find(
			XML_OPEN, this->getInicioTexto());
		unsigned int indCloseTag = this->getTextoAProcesar().find(
			XML_CLOSE_TAG, this->getInicioTexto());

		// si llego a este punto, es porque inicioTexto esta apuntando a un
		// caracter valido distinto de espacio
		if ((indOpen < indCloseTag) && (indOpen <= this->getInicioTexto())) {
			siguienteEstado = this->getInicial();

		} else {

			// si son iguales los indices, gana indCloseTag (<=)
			if ((indCloseTag <= indOpen) && (indCloseTag <= this->getInicioTexto())) {
				siguienteEstado = this->getCerrandoTag();
			} 
		}

		unsigned int indiceFinal = this->getTextoAProcesar().size();
		if (indOpen < indiceFinal) {
			indiceFinal = indOpen;
		}
		if (indCloseTag < indiceFinal) {
			indiceFinal = indCloseTag;
		}

		string nuevoTexto = this->getTextoAProcesar().substr(this->getInicioTexto(), indiceFinal);
		nuevoTexto.erase(indiceFinal - this->getInicioTexto());
		nuevoTexto = MensajesUtil::trim(nuevoTexto);
		// TODO: si el texto fuesen palabras no se esta contemplando dejar
		// un espacio adicional al final de la linea para que no se pegue con la siguiente

		this->textoAcumulado += nuevoTexto;
		this->setInicioTexto(indiceFinal);

		// si setee el siguiente estado, llegue al final del texto
		if (siguienteEstado != this) {

			this->getElementoActual()->setTexto(this->textoAcumulado);
			this->enProceso = false;

			// correccion del puntero
			if (siguienteEstado == this->getCerrandoTag()) {
				this->setInicioTexto(indCloseTag + string(XML_CLOSE_TAG).size());
			}

			siguienteEstado->setElementoActual(this->getElementoActual());
			siguienteEstado->setTextoAProcesar(this->getTextoAProcesar());
			siguienteEstado->setNumeroLinea(this->getNumeroLinea());
			siguienteEstado->setInicioTexto(this->getInicioTexto());
		}
	}

	return siguienteEstado;
}


XmlParserEstadoInicial* XmlParserEstadoProcesandoTxt::getInicial() {
	if (this->inicial == NULL) {
		this->inicial = new XmlParserEstadoInicial(this->getNodosProcesados());
	}

	return this->inicial;
}

XmlParserEstadoCerrandoTag* XmlParserEstadoProcesandoTxt::getCerrandoTag() {
	if (this->cerrandoTag == NULL) {
		this->cerrandoTag = new XmlParserEstadoCerrandoTag(this->getNodosProcesados());
	}

	return this->cerrandoTag;
}