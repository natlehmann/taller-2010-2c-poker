
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

Elemento* DomTreeFactory::crearElemento(char* nombre) {

	Elemento* elemento;
	char* nombreMin = _strlwr(nombre);

	//TODO: Se podrìa reemplazar por configuraciòn de un archivo
	if (nombreMin == "raiz") {
		char* hijos[] = {"pedido","respuesta","\0"};
		char* atributos[] = {"\0"};
		elemento = configurarNodo(nombreMin, hijos, atributos);
	}

	if (nombreMin == "pedido") {
		char* hijos[] = {"operacion","parametros","\0"};
		char* atributos[] = {"\0"};
		elemento = configurarNodo(nombreMin, hijos, atributos);
	}

	if (nombreMin == "operacion") {
		char* hijos[] = {"\0"};
		char* atributos[] = {"id","\0"};
		elemento = configurarNodo(nombreMin, hijos, atributos);
	}

	if (nombreMin == "parametros") {
		char* hijos[] = {"parametro", "\0"};
		char* atributos[] = {"\0"};
		elemento = configurarNodo(nombreMin, hijos, atributos);
	}

	if (nombreMin == "parametro") {
		char* hijos[] = {"\0"};
		char* atributos[] = {"nombre", "\0"};
		elemento = configurarNodo(nombreMin, hijos, atributos);
	}

	if (nombreMin == "respuesta") {
		char* hijos[] = {"operacion", "resultados", "errores", "\0"};
		char* atributos[] = {"\0"};
		elemento = configurarNodo(nombreMin, hijos, atributos);
	}

	if (nombreMin == "resultados") {
		char* hijos[] = {"resultado", "\0"};
		char* atributos[] = {"\0"};
		elemento = configurarNodo(nombreMin, hijos, atributos);
	}

	if (nombreMin == "resultado") {
		char* hijos[] = {"\0"};
		char* atributos[] = {"nombre", "\0"};
		elemento = configurarNodo(nombreMin, hijos, atributos);
	}

	if (nombreMin == "errores") {
		char* hijos[] = {"error", "\0"};
		char* atributos[] = {"\0"};
		elemento = configurarNodo(nombreMin, hijos, atributos);
	}

	if (nombreMin == "error") {
		char* hijos[] = {"\0"};
		char* atributos[] = {"tipo", "\0"};
		elemento = configurarNodo(nombreMin, hijos, atributos);
	}

	if (elemento!= NULL) {		
		return elemento;

	} else {
		char* partes [] = {"El elemento ", nombre, " no esta permitido.", "\0"};
		char* msg = MensajesUtil::concatMensaje(partes);
		throw ParserException(msg);
	}
	
}

Elemento* DomTreeFactory::configurarNodo(char* nombre, char* hijos[], char* atributos[]){

	Elemento* elemento = new Elemento(nombre);
	elemento->setHijosPermitidos(ArrayUtil::charArrayToSet(hijos));
	elemento->setAtributosPermitidos(ArrayUtil::charArrayToSet(atributos));
	return elemento;
}
