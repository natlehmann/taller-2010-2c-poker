#include "FileException.h"

FileException::FileException(string mensaje) : PokerException(mensaje) {
}

FileException::FileException(string mensaje, string idError) : PokerException(mensaje, idError){
}

FileException::~FileException(void) throw(){
}
