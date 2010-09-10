
#include "ParserEntradaTeclado.h"
#include "DomTree.h"
#include "Elemento.h"

ParserEntradaTeclado::ParserEntradaTeclado(string tipoOperacion, list<string>* lstOperandos)
{
	this->_tipoOperacion = tipoOperacion;
	this->_lstOperandos = lstOperandos;
}

ParserEntradaTeclado::~ParserEntradaTeclado(void)
{	
	
}

DomTree* ParserEntradaTeclado::toDom() {

	DomTree* domTree = new DomTree();

	//try {

			Elemento* elementoPedido = domTree->agregarElemento("pedido");
			Elemento* elementoOperacion = elementoPedido->agregarHijo("operacion");
			elementoOperacion->agregarAtributo("id",this->_tipoOperacion);
			Elemento* elementoParametros = elementoPedido->agregarHijo("parametros");

			Elemento* elementoParametro;
			for (list<string>::iterator it = this->_lstOperandos->begin(); it != this->_lstOperandos->end(); it++) {
				elementoParametro = elementoParametros->agregarHijo("parametro");
				elementoParametro->agregarAtributo("nombre","dividendo");
				//elementoParametro->setTexto(it);
			}

	//} catch(Exception ex ) {

	//	delete(domTree);
	//	throw ex;
	//}

	return domTree;
}

string ParserEntradaTeclado::toString(DomTree* domTree) {

	string resultado = "";

	Elemento* raiz = domTree->getRaiz();

	// para evitar procesar el elemento raiz
	for(list<Elemento*>::iterator it = raiz->getHijos()->begin(); it != raiz->getHijos()->end(); it++) {
		resultado += procesarNodo(*it, "");		
	}

	return resultado;
}


string ParserEntradaTeclado::abrirNodo(Elemento* elemento, string indent) {

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

string ParserEntradaTeclado::procesarNodo(Elemento* elemento, string indent) {

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

string ParserEntradaTeclado::cerrarNodo(Elemento* elemento, string indent) {

	// cierre de tag
	string resultado = "";
	indent = indent.substr(0, indent.size() - string(XML_INDENT).size());

	if (!(elemento->getHijos()->empty()) || (elemento->getTexto() != "")) {
		resultado += indent + XML_CLOSE_TAG + string(elemento->getNombre()) + XML_CLOSE + "\n";
	}

	return resultado;
}
