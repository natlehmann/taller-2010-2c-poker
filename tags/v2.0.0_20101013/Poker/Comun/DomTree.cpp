#include "DomTree.h"
#include "MensajesUtil.h"
#include "ParserException.h"
#include "DomTreeFactory.h"

DomTree::DomTree(void){
	this->nombreConfiguracion = "";
	this->raiz = DomTreeFactory::crearElemento("raiz");
}

DomTree::DomTree(string nombreConfiguracion) {
	this->nombreConfiguracion = nombreConfiguracion;
	this->raiz = DomTreeFactory::config(nombreConfiguracion)->elemento("raiz");
}

DomTree::DomTree(Elemento* elemento){
	this->nombreConfiguracion = "";
	this->raiz = DomTreeFactory::crearElemento("raiz");
	this->raiz->getHijos()->push_back(elemento);
}

DomTree::DomTree(Elemento* elemento, string nombreConfiguracion){
	this->nombreConfiguracion = nombreConfiguracion;
	this->raiz = DomTreeFactory::config(nombreConfiguracion)->elemento("raiz");
	this->raiz->getHijos()->push_back(elemento);
}

DomTree::~DomTree(void)
{
	delete(this->raiz);
}

Elemento* DomTree::agregarElemento(string nombre){

	Elemento* hijo = NULL;

	if (this->nombreConfiguracion.empty()) {
		hijo = this->raiz->agregarHijo(nombre);

	} else {
		hijo = this->raiz->agregarHijo(nombre, this->nombreConfiguracion);
	}

	return hijo;
}

Elemento* DomTree::getRaiz() {
	return this->raiz;
}
