
#include "XmlParser.h"
#include "DomTree.h"
#include "Elemento.h"
#include "XmlParserEstado.h"
#include "XmlParserEstadoInicial.h"
#include "XmlParserEstadoAbriendoTag.h"
#include "XmlParserEstadoCerrandoInline.h"
#include "XmlParserEstadoCerrandoTag.h"
#include "XmlParserEstadoDentroTag.h"
#include "XmlParserEstadoProcesandoAtt.h"
#include "XmlParserEstadoProcesandoTxt.h"
#include "ParserException.h"

XmlParser::XmlParser(void)
{
	this->nodosProcesados = new deque<string*>();

	this->estadoInicial = new XmlParserEstadoInicial(this->nodosProcesados);
	this->cerrandoInline = new XmlParserEstadoCerrandoInline(
		this->nodosProcesados, this->estadoInicial);
	this->cerrandoTag = new XmlParserEstadoCerrandoTag(this->nodosProcesados, 
		this->estadoInicial);
	this->procesandoTxt = new XmlParserEstadoProcesandoTxt(this->nodosProcesados, 
		this->estadoInicial, this->cerrandoTag);
	this->dentroTag = new XmlParserEstadoDentroTag(this->nodosProcesados,
		this->estadoInicial, this->procesandoTxt, this->cerrandoTag);
	this->procesandoAtt = new XmlParserEstadoProcesandoAtt(this->nodosProcesados,
		this->dentroTag, this->cerrandoInline);
	this->abriendoTag = new XmlParserEstadoAbriendoTag(this->nodosProcesados, 
		this->dentroTag, this->cerrandoInline, this->procesandoAtt);

	this->estadoInicial->setAbriendoTag(this->abriendoTag);
	this->estadoInicial->setCerrandoTag(this->cerrandoTag);
	

	this->estadoActual = this->estadoInicial;
}

XmlParser::~XmlParser(void)
{	
	for(deque<string*>::iterator it = this->nodosProcesados->begin();
		it != this->nodosProcesados->end(); it++) {
			delete (*it);
	}

	this->nodosProcesados->clear();
	delete(this->nodosProcesados);

	if (this->estadoInicial != NULL) {
		delete (this->estadoInicial);
		this->estadoInicial = NULL;
	}

	if (this->abriendoTag != NULL) {
		delete (this->abriendoTag);
		this->abriendoTag = NULL;
	}

	if (this->cerrandoInline != NULL) {
		delete (this->cerrandoInline);
		this->cerrandoInline = NULL;
	}

	if (this->cerrandoTag != NULL) {
		delete (this->cerrandoTag);
		this->cerrandoTag = NULL;
	}
	
	if (this->dentroTag != NULL) {
		delete (this->dentroTag);
		this->dentroTag = NULL;
	}

	if (this->procesandoAtt != NULL) {
		delete (this->procesandoAtt);
		this->procesandoAtt = NULL;
	}

	if (this->procesandoTxt != NULL) {
		delete (this->procesandoTxt);
		this->procesandoTxt = NULL;
	}
}

DomTree* XmlParser::toDom(string texto){
	return this->toDom(texto, "");
}

DomTree* XmlParser::toDom(string texto, string nombreConfiguracion) {

	DomTree* tree = NULL;
	if (nombreConfiguracion.empty()) {
		tree = new DomTree();

	} else {
		this->guardarNombreConfiguracion(nombreConfiguracion);
		tree = new DomTree(nombreConfiguracion);
	}

	this->estadoActual = this->estadoInicial;
	this->estadoActual->setElementoActual(tree->getRaiz());

	unsigned int contadorLinea = 1;
	unsigned int inicio = 0;

	try {
		procesarLineaALinea(texto, inicio, contadorLinea);
		validarFinal();

	} catch(ParserException& ex ) {

		delete(tree);

		for(deque<string*>::iterator it = this->nodosProcesados->begin();
			it != this->nodosProcesados->end(); it++) {
				delete (*it);
		}
		this->nodosProcesados->clear();

		throw ex;
	}

	return tree;
}


void XmlParser::guardarNombreConfiguracion(string nombreConfiguracion){

	this->estadoInicial->setNombreConfiguracion(nombreConfiguracion);
	this->cerrandoInline->setNombreConfiguracion(nombreConfiguracion);
	this->cerrandoTag->setNombreConfiguracion(nombreConfiguracion);
	this->procesandoTxt->setNombreConfiguracion(nombreConfiguracion);
	this->dentroTag->setNombreConfiguracion(nombreConfiguracion);
	this->procesandoAtt->setNombreConfiguracion(nombreConfiguracion);
	this->abriendoTag->setNombreConfiguracion(nombreConfiguracion);
}


void XmlParser::procesarLineaALinea(string textoAProcesar, 
						 unsigned int inicio, unsigned int contadorLinea) {

	unsigned int fin = textoAProcesar.find("\n",inicio);
	// si no se encuentra un retorno de linea pero todavia 
	// no llegue al fin del string
	if (fin == string::npos) {
		if (inicio < (textoAProcesar.size() - 1)){
			fin = textoAProcesar.size();
		}
	} else {
		fin += string("\n").size();
	}

	if (fin <= textoAProcesar.size() && fin > inicio) {
		string linea = textoAProcesar.substr(inicio, fin);
		linea.erase(fin - inicio);
		linea = MensajesUtil::trim(linea);

		this->estadoActual->setNumeroLinea(contadorLinea);
		this->estadoActual->setTextoAProcesar(linea);
		this->estadoActual->setInicioTexto(0);

		while (!this->estadoActual->terminado()) {
			try {
				this->estadoActual = this->estadoActual->procesarFragmento();
			} catch(ParserException& ex ) {
					throw ex;
			}
		}

		inicio = fin;
		contadorLinea++;

		procesarLineaALinea(textoAProcesar, inicio, contadorLinea);
	}
}

void XmlParser::validarFinal() {
	
	if (!this->nodosProcesados->empty()) {

		string nodosInvalidos = "";
		for (deque<string*>::iterator it = this->nodosProcesados->begin();
			it != this->nodosProcesados->end(); it++) {
				nodosInvalidos = nodosInvalidos + *(*it) + " ";
		}

		throw ParserException(
			"Error de validacion en archivo. Los siguientes tags nunca fueron cerrados: " 
			+ nodosInvalidos);
	}
}


string XmlParser::toString(DomTree* domTree) {

	string resultado = "";

	Elemento* raiz = domTree->getRaiz();

	// para evitar procesar el elemento raiz
	for(list<Elemento*>::iterator it = raiz->getHijos()->begin(); it != raiz->getHijos()->end(); it++) {
		resultado += procesarNodo(*it, "");		
	}

	return resultado;
}

string XmlParser::abrirNodo(Elemento* elemento, string indent) {

	// apertura de tag
	string resultado = indent + XML_OPEN + string(elemento->getNombre());

	// procesar atributos
	for(map<string,string>::iterator itAtt = elemento->getAtributos()->begin();
		itAtt != elemento->getAtributos()->end(); itAtt++) {
			resultado += " " + string(itAtt->first) + XML_OPEN_ATTR 
				+ string(itAtt->second) + XML_CLOSE_ATTR;
	}

	// cierre de tag
	if ((elemento->getHijos()->empty()) && (elemento->getTexto() == "")) {
		resultado += XML_CLOSE_TAG_INLINE;

	} else {
		resultado += XML_CLOSE;
	}
	resultado += "\n";

	return resultado;
}

string XmlParser::procesarNodo(Elemento* elemento, string indent) {

	string resultado = abrirNodo(elemento, indent);	
	indent += XML_INDENT;

	// escribir texto del nodo
	if (elemento->getTexto() != "") {
		resultado += indent + string(elemento->getTexto()) + "\n";
	}

	// procesar hijos
	for(list<Elemento*>::iterator it = elemento->getHijos()->begin(); 
		it != elemento->getHijos()->end(); it++) {

			resultado += procesarNodo(*it, indent);
	}

	// cerrar tag
	resultado += cerrarNodo(elemento, indent);

	return resultado;
}

string XmlParser::cerrarNodo(Elemento* elemento, string indent) {

	// cierre de tag
	string resultado = "";
	indent = indent.substr(0, indent.size() - string(XML_INDENT).size());

	if (!(elemento->getHijos()->empty()) || (elemento->getTexto() != "")) {
		resultado += indent + XML_CLOSE_TAG + string(elemento->getNombre()) + XML_CLOSE + "\n";
	}

	return resultado;
}
