
#include "PokerException.h"

PokerException::PokerException(string mensaje)
{
	this->mensaje = mensaje;

	// Si no se conoce el tipo de error, por default se asume de Sintaxis
	this->error = Error("S", mensaje, "");
}

PokerException::PokerException(string mensaje, string idError){
	this->mensaje = mensaje;
	this->error = Error(idError, mensaje, "");
}

PokerException::~PokerException(void) throw()
{
}

PokerException::PokerException(Error& error){
	this->error = error;
}

const string PokerException::getMensaje() const throw() {
	return this->mensaje;
}

const char* PokerException::what() const throw() {
	return this->mensaje.c_str();
}
