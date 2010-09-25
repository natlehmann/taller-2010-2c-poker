#include "DomTreeFactoryInstance.h"
#include "MensajesUtil.h"
#include "ParserException.h"

DomTreeFactoryInstance::DomTreeFactoryInstance(string nombreConfig){
	this->nombreConfig = nombreConfig;
}

DomTreeFactoryInstance::~DomTreeFactoryInstance(void)
{
}

Elemento* DomTreeFactoryInstance::elemento(string nombre){

	bool encontrado = false;
	list<string>::iterator it = this->elementos.begin();

	while (!encontrado && it != this->elementos.end()) {
		if (MensajesUtil::sonIguales(*it, nombre)) {
			encontrado = true;
		}
		it++;
	}

	if (!encontrado) {
		throw ParserException("El elemento " + nombre + " no esta permitido.", "V");
	}

	set<string*>* hijos = MensajesUtil::splitToSet(this->hijosPorElemento.find(nombre)->second);
	set<string*>* atributos = MensajesUtil::splitToSet(this->attPorElemento.find(nombre)->second);

	Elemento* elemento = new Elemento(nombre);
	elemento->setHijosPermitidos(hijos);
	elemento->setAtributosPermitidos(atributos);
	return elemento;

}

void DomTreeFactoryInstance::setElementos(list<string> elementos){
	this->elementos = elementos;
}

void DomTreeFactoryInstance::setHijosPorElemento(map<string,string> hijosPorElem) {
	this->hijosPorElemento = hijosPorElem;
}

void DomTreeFactoryInstance::setAttPorElemento(map<string,string> attPorElem){
	this->attPorElemento = attPorElem;
}
