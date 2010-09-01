#include "DomTree.h"
#include "MensajesUtil.h"
#include "ParserException.h"
#include "DomTreeFactory.h"

DomTree::DomTree(void)
{
	this->raiz = DomTreeFactory::crearElemento("raiz");
}

DomTree::~DomTree(void)
{
	delete(this->raiz);
}

Elemento* DomTree::agregarElemento(char* nombre){
	Elemento* hijo = this->raiz->agregarHijo(nombre);
	return hijo;
}

Elemento* DomTree::getRaiz() {
	return this->raiz;
}
