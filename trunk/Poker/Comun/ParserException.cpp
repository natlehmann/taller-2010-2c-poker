
#include "ParserException.h"

ParserException::ParserException(string mensaje) : PokerException(mensaje) {
}

ParserException::ParserException(string mensaje, string idError) : PokerException(mensaje, idError){
}

ParserException::~ParserException(void) throw(){
}


