#include "DatosInvalidosException.h"

DatosInvalidosException::DatosInvalidosException(string mensaje) : PokerException(mensaje)
{
}

DatosInvalidosException::DatosInvalidosException(string mensaje, string idError) 
		: PokerException(mensaje, idError){
}

DatosInvalidosException::DatosInvalidosException(Error& error) : PokerException(error)
{
}

DatosInvalidosException::~DatosInvalidosException() throw()
{
}
