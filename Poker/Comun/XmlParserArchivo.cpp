#include "XmlParserArchivo.h"
#include "ParserException.h"

XmlParserArchivo::XmlParserArchivo(string nombreArchivo) : XmlParser()
{
	this->setNombreArchivo(nombreArchivo);
	this->arbol = new DomTree();
	this->finArchivo = false;
	this->inicializado = false;
	this->validado = false;
}

XmlParserArchivo::~XmlParserArchivo(void)
{
	delete(this->archivo);
	delete(this->arbol);
}

void XmlParserArchivo::setNombreArchivo(string nombreArchivo) {
	this->nombreArchivo = nombreArchivo;
	this->archivo = new ifstream(this->nombreArchivo.c_str());

	if (!*this->archivo){
		throw ParserException("No se puede abrir el archivo " + this->nombreArchivo, "E");
	}
}

DomTree* XmlParserArchivo::toDom(string nombreArchivo) {
	if (!MensajesUtil::esVacio(nombreArchivo)) {
		this->setNombreArchivo(nombreArchivo);
	}

	// TODO falta implementar
	return NULL;
}


DomTree* XmlParserArchivo::getSiguiente(){
	
	if (this->arbol->getRaiz()->getHijos()->size() <= 1 && !this->finArchivo) {

		this->procesarArchivo();

	}

	if (this->arbol->getRaiz()->getHijos()->size() >= 1) {

		DomTree* nuevoArbol = new DomTree(this->arbol->getRaiz()->getHijos()->front());

		//sacamos el elemento del arbol original
		this->arbol->getRaiz()->getHijos()->pop_front();

		return nuevoArbol;

	} else {
		return NULL;
	}
}

void XmlParserArchivo::procesarArchivo(){

	if (!this->inicializado) {

		this->estadoActual = this->estadoInicial;
		this->estadoActual->setElementoActual(this->arbol->getRaiz());

		this->contadorLinea = 1;
		this->inicializado = true;
	}

	try {

		while (this->arbol->getRaiz()->getHijos()->size() <= 1 && !this->finArchivo) {

			string linea;
			getline(*this->archivo,linea);
			this->contadorLinea++;

			if (this->archivo->eof()) {
				this->finArchivo = true;
			}

			if (this->archivo->bad()) {
				throw ParserException("Se produjo un error de lectura en la linea " + this->contadorLinea, "E");
			}

		
			this->procesarLinea(linea);
		}

		if (this->finArchivo && !this->validado) {
			validarFinal();
			this->validado = true;
		}

		} catch(ParserException& ex ) {
			for(deque<string*>::iterator it = this->nodosProcesados->begin();
				it != this->nodosProcesados->end(); it++) {
					delete (*it);
			}
			this->nodosProcesados->clear();

			throw ex;
		}
}


void XmlParserArchivo::procesarLinea(string linea) {

	this->estadoActual->setNumeroLinea(this->contadorLinea);
	this->estadoActual->setTextoAProcesar(linea);
	this->estadoActual->setInicioTexto(0);

	while (!this->estadoActual->terminado()) {
		try {
			this->estadoActual = this->estadoActual->procesarFragmento();
		} catch(ParserException& ex ) {
				throw ex;
		}
	}
}
