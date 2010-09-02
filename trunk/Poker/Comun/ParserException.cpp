
#include "ParserException.h"

ParserException::ParserException(string mensaje){
	this->mensaje = mensaje;
}

ParserException::~ParserException(void){
	//delete(this->mensaje);
}

const string ParserException::getMensaje() const throw() {
	return this->mensaje;
}

const char* ParserException::what() const throw() {
	return this->mensaje.c_str();
}
