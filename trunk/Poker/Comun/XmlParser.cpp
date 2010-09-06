
#include "XmlParser.h"
#include "DomTree.h"
#include "Elemento.h"
#include "XmlParserEstado.h"
#include "XmlParserEstadoInicial.h"
#include "ParserException.h"

XmlParser::XmlParser(void)
{
	this->nodosProcesados = new deque<string*>();
	this->estadoInicial = new XmlParserEstadoInicial(this->nodosProcesados);
	this->estadoActual = this->estadoInicial;
}

XmlParser::~XmlParser(void)
{	/*
	for(deque<string*>::iterator it = this->nodosProcesados->begin();
		it != this->nodosProcesados->end(); it++) {
			delete (*it);
	}
	*/

	this->nodosProcesados->clear();
	delete(this->nodosProcesados);

	delete (this->estadoInicial);
}

DomTree* XmlParser::toDom(string texto) {

	DomTree* tree = new DomTree();
	this->estadoActual->setElementoActual(tree->getRaiz());

	unsigned int contadorLinea = 1;
	unsigned int inicio = 0;

	try {
		procesarLineaALinea(texto, inicio, contadorLinea);

	} catch(ParserException& ex ) {
		delete(tree);
		throw ex;
	}

	return tree;
}


void XmlParser::procesarLineaALinea(string textoAProcesar, 
						 unsigned int inicio, unsigned int contadorLinea) {

	unsigned int fin = textoAProcesar.find("\n",inicio);
	// si no se encuentra un retorno de linea pero todavia 
	// no llegue al fin del string
	if (fin > textoAProcesar.size()) {
		if (inicio < (textoAProcesar.size() - 1)){
			fin = textoAProcesar.size();
		}
	} else {
		fin += string("\n").size();
	}

	if (fin <= textoAProcesar.size() && fin > inicio) {
		string linea = textoAProcesar.substr(inicio, fin);
cout << "Procesando LINEA " << contadorLinea << ": " << linea << endl;

		this->estadoActual->setNumeroLinea(contadorLinea);
		this->estadoActual->setTextoAProcesar(linea);
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
			resultado += " " + string(itAtt->first) + "=\"" + string(itAtt->second) + "\"";
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
