#include "DatosInvalidosException.h"

DatosInvalidosException::DatosInvalidosException(string mensaje) : PokerException(mensaje)
{
}

DatosInvalidosException::DatosInvalidosException(Error& error) : PokerException(error)
{
}

DatosInvalidosException::~DatosInvalidosException() throw()
{
}
