
#include "XmlParser.h"
#include "DomTree.h"
#include "Elemento.h"

XmlParser::XmlParser(void)
{
}

XmlParser::~XmlParser(void)
{
}

DomTree* XmlParser::toDom(string texto) {
	DomTree* tree = new DomTree();
/*
	int contadorLinea = 1;
	char* indice = strstr(texto,"\n");

	if (indice) {
		linea = texto.substr(0
*/
	return tree;
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
	for(map<char*,char*>::iterator itAtt = elemento->getAtributos()->begin();
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
