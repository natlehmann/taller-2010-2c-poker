
#include "DomTreeFactory.h"
#include "DomTree.h"
#include "Elemento.h"
#include "ArrayUtil.h"
#include "MensajesUtil.h"
#include "ParserException.h"

DomTreeFactory::DomTreeFactory(void)
{
}

DomTreeFactory::~DomTreeFactory(void)
{
}

Elemento* DomTreeFactory::crearElemento(string nombre) {

	Elemento* elemento;

	//TODO: Se podrìa reemplazar por configuraciòn de un archivo
	if (MensajesUtil::sonIguales(nombre, string("raiz"))) {
		char* hijos[] = {"pedido","respuesta","\0"};
		char* atributos[] = {"\0"};
		elemento = configurarNodo(nombre, hijos, atributos);
	}

	if (MensajesUtil::sonIguales(nombre, string("pedido"))) {
		char* hijos[] = {"operacion","parametros","\0"};
		char* atributos[] = {"\0"};
		elemento = configurarNodo(nombre, hijos, atributos);
	}

	if (MensajesUtil::sonIguales(nombre, string("operacion"))) {
		char* hijos[] = {"\0"};
		char* atributos[] = {"id","\0"};
		elemento = configurarNodo(nombre, hijos, atributos);
	}

	if (MensajesUtil::sonIguales(nombre, string("parametros"))) {
		char* hijos[] = {"parametro", "\0"};
		char* atributos[] = {"\0"};
		elemento = configurarNodo(nombre, hijos, atributos);
	}

	if (MensajesUtil::sonIguales(nombre, string("parametro"))) {
		char* hijos[] = {"\0"};
		char* atributos[] = {"nombre", "\0"};
		elemento = configurarNodo(nombre, hijos, atributos);
	}

	if (MensajesUtil::sonIguales(nombre, string("respuesta"))) {
		char* hijos[] = {"operacion", "resultados", "errores", "\0"};
		char* atributos[] = {"\0"};
		elemento = configurarNodo(nombre, hijos, atributos);
	}

	if (MensajesUtil::sonIguales(nombre, string("resultados"))) {
		char* hijos[] = {"resultado", "\0"};
		char* atributos[] = {"\0"};
		elemento = configurarNodo(nombre, hijos, atributos);
	}

	if (MensajesUtil::sonIguales(nombre, string("resultado"))) {
		char* hijos[] = {"\0"};
		char* atributos[] = {"nombre", "\0"};
		elemento = configurarNodo(nombre, hijos, atributos);
	}

	if (MensajesUtil::sonIguales(nombre, string("errores"))) {
		char* hijos[] = {"error", "\0"};
		char* atributos[] = {"\0"};
		elemento = configurarNodo(nombre, hijos, atributos);
	}

	if (MensajesUtil::sonIguales(nombre, string("error"))) {
		char* hijos[] = {"\0"};
		char* atributos[] = {"tipo", "\0"};
		elemento = configurarNodo(nombre, hijos, atributos);
	}

	if (elemento != NULL) {		
		return elemento;

	} else {
		string msg = "El elemento " + nombre + " no esta permitido.";
		throw ParserException(msg);
	}
	
}

Elemento* DomTreeFactory::configurarNodo(string nombre, char* hijos[], char* atributos[]){

	Elemento* elemento = new Elemento(nombre);
	elemento->setHijosPermitidos(ArrayUtil::charArrayToSet(hijos));
	elemento->setAtributosPermitidos(ArrayUtil::charArrayToSet(atributos));
	return elemento;
}
