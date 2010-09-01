
#include "ParserException.h"

ParserException::ParserException(char* mensaje){
	this->mensaje = mensaje;
}

ParserException::~ParserException(void){
	delete(this->mensaje);
}

const char* ParserException::getMensaje() const throw() {
	return this->mensaje;
}
