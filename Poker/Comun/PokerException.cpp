
#include "PokerException.h"

PokerException::PokerException(string mensaje)
{
	this->mensaje = mensaje;
}

PokerException::~PokerException(void)
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
