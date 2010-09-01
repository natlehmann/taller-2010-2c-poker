
#include "Elemento.h"
#include "ParserException.h"
#include "MensajesUtil.h"
#include "DomTreeFactory.h"


Elemento::Elemento(char* nombre)
{
	this->nombre = nombre;
	this->atributos = new map<char*,char*>();
	this->hijos = new list<Elemento*>();
	this->texto = "";
}

Elemento::~Elemento(void)
{
	this->atributos->clear();
	delete(this->atributos);

	if (this->atributosPermitidos != NULL) {
		this->atributosPermitidos->clear();
		delete(this->atributosPermitidos);
	}

	if (this->hijosPermitidos != NULL) {
		this->hijosPermitidos->clear();
		delete(this->hijosPermitidos);
	}

	for (list<Elemento*>::iterator it = this->hijos->begin(); it != this->hijos->end(); it++) {
		delete(*it);
	}
	delete(this->hijos);
}

void Elemento::setAtributosPermitidos(set<char*>* atributosPermitidos) {
	this->atributosPermitidos = atributosPermitidos;
}

void Elemento::setHijosPermitidos(set<char*>* hijosPermitidos) {
	this->hijosPermitidos = hijosPermitidos;
}

char* Elemento::getNombre(){
	return this->nombre;
}

map<char*,char*>* Elemento::getAtributos(){
	return this->atributos;
}

void Elemento::agregarAtributo(char* clave, char* valor){	
	
	set<char*>::iterator it = atributosPermitidos->find(clave);

	// si la clave existe en el conjunto de atributos permitidos
	if (it != this->atributosPermitidos->end()) {

		map<char*,char*>::iterator itMapa = this->atributos->find(clave);

		// si ya existia la clave, borramos su valor anterior
		if (itMapa != this->atributos->end()) {
			this->atributos->erase(itMapa);
		}
		this->atributos->insert(pair<char*,char*>(clave, valor));
	
	} else {
		char* partes [] = {"El atributo ", clave, " no esta permitido en el elemento ", this->nombre, "\0"};
		char* msg = MensajesUtil::concatMensaje(partes);
		throw ParserException(msg);
	}
}

char* Elemento::getAtributo(char* clave) {
	map<char*,char*>::iterator it = this->atributos->find(clave);

	if (it != this->atributos->end()) {
		return it->second;

	} else {
		return "";
	}
}

void Elemento::setTexto(char* texto){
	this->texto = texto;
}

char* Elemento::getTexto(){
	return this->texto;
}

Elemento* Elemento::getPadre() {
	return this->padre;
}

void Elemento::setPadre(Elemento* padre) {
	this->padre = padre;
}

bool Elemento::isRaiz() {
	return (this->padre != NULL);
}

Elemento* Elemento::agregarHijo(char* nombreHijo) {

	set<char*>::iterator it = hijosPermitidos->find(nombreHijo);

	// si el hijo esta permitido
	if (it != this->hijosPermitidos->end()) {

		Elemento* hijo = DomTreeFactory::crearElemento(nombreHijo);
		hijo->setPadre(this);
		this->hijos->insert(this->hijos->end(), hijo);

		return hijo;
	
	} else {
		char* partes [] = {"El elemento ", nombreHijo, 
			" no puede anidarse dentro del elemento ", this->nombre, "\0"};
		char* msg = MensajesUtil::concatMensaje(partes);
		throw ParserException(msg);
	}
}

list<Elemento*>* Elemento::getHijos() {
	return this->hijos;
}

