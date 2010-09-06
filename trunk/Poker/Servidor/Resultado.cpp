#include "Resultado.h"

Resultado::Resultado() {}

Resultado::Resultado(string id, string valor, bool error, string idOperacion)
{
	this->id = id;
	this->valor = valor;
	this->error = error;
	this->idOperacion = idOperacion;
}

Resultado::~Resultado() {}
