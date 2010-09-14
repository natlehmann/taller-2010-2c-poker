#include "Respuesta.h"

Respuesta::Respuesta() {}

Respuesta::Respuesta(string id, string valor, string idOperacion) {
	this->id = id;
	this->valor = valor;
	this->idOperacion = idOperacion;
}

Respuesta::~Respuesta() {
}


bool Respuesta::isError(){
	return false;
}
