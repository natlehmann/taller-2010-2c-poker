
#include "Elemento.h"
#include "ParserException.h"
#include "MensajesUtil.h"
#include "DomTreeFactory.h"


Elemento::Elemento(string nombre)
{
	this->nombre = nombre;
	this->atributos = new map<string,string>();
	this->hijos = new list<Elemento*>();
	this->texto = "";
	this->numeroDeLinea = -1;
}

Elemento::~Elemento(void)
{
	this->atributos->clear();
	delete(this->atributos);

	if (this->atributosPermitidos != NULL) {;
		for (set<string*>::iterator it = this->atributosPermitidos->begin(); 
			it != this->atributosPermitidos->end(); it++) {
				delete(*it);
		}
		this->atributosPermitidos->clear();
		delete(this->atributosPermitidos);
	}

	if (this->hijosPermitidos != NULL) {
		for (set<string*>::iterator it = this->hijosPermitidos->begin(); 
			it != this->hijosPermitidos->end(); it++) {
				delete(*it);
		}
		this->hijosPermitidos->clear();
		delete(this->hijosPermitidos);
	}

	for (list<Elemento*>::iterator it = this->hijos->begin(); it != this->hijos->end(); it++) {
		delete(*it);
	}
	delete(this->hijos);
}

void Elemento::setAtributosPermitidos(set<string*>* atributosPermitidos) {
	this->atributosPermitidos = atributosPermitidos;
}

void Elemento::setHijosPermitidos(set<string*>* hijosPermitidos) {
	this->hijosPermitidos = hijosPermitidos;
}

string Elemento::getNombre(){
	return this->nombre;
}

map<string,string>* Elemento::getAtributos(){
	return this->atributos;
}

void Elemento::agregarAtributo(string clave, string valor){	

	// si la clave existe en el conjunto de atributos permitidos
	if (esAtributoPermitido(clave)) {

		map<string,string>::iterator itMapa = this->atributos->find(clave);

		// si ya existia la clave, borramos su valor anterior
		if (itMapa != this->atributos->end()) {
			this->atributos->erase(itMapa);
		}
		this->atributos->insert(pair<string,string>(clave, valor));
	
	} else {
		string msg = "El atributo " + clave + " no esta permitido en el elemento " + this->nombre;
		throw ParserException(msg, "V");
	}
}

string Elemento::getAtributo(string clave) {
	map<string,string>::iterator it = this->atributos->find(clave);

	if (it != this->atributos->end()) {
		return it->second;

	} else {
		return "";
	}
}

void Elemento::setTexto(string texto){
	this->texto = texto;
}

string Elemento::getTexto(){
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

Elemento* Elemento::agregarHijo(string nombreHijo) {
	return this->agregarHijo(nombreHijo, "");
}

Elemento* Elemento::agregarHijo(string nombreHijo, string nombreConfiguracion) {

	// si el hijo esta permitido
	if (esHijoPermitido(nombreHijo)) {

		Elemento* hijo = NULL;
		
		if (nombreConfiguracion.empty()) {
			hijo = DomTreeFactory::crearElemento(nombreHijo);

		} else {
			hijo = DomTreeFactory::config(nombreConfiguracion)->elemento(nombreHijo);
		}

		hijo->setPadre(this);
		this->hijos->insert(this->hijos->end(), hijo);

		return hijo;
	
	} else {
		string msg = "El elemento " + nombreHijo + 
			" no puede anidarse dentro del elemento " + this->nombre;
		throw ParserException(msg, "V");
	}
}

list<Elemento*>* Elemento::getHijos() {
	return this->hijos;
}

bool Elemento::esHijoPermitido(string nombreHijo) {
	return esPermitido(nombreHijo, this->hijosPermitidos);
}

bool Elemento::esAtributoPermitido(string atributo) {
	return esPermitido(atributo, this->atributosPermitidos);
}

bool Elemento::esPermitido(string nombre, set<string*>* conjunto) {
	bool encontrado = false;
	for (set<string*>::iterator it = conjunto->begin(); it != conjunto->end(); it++) {
		if (MensajesUtil::sonIguales(nombre, *(*it))) {
			encontrado = true;
		}
	}
	return encontrado;
}

int Elemento::getNumeroDeLinea() {
	return this->numeroDeLinea;
}

void Elemento::setNumeroDeLinea(int numero){
	this->numeroDeLinea = numero;
}
