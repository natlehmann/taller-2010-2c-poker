#include "DatosInvalidosException.h"

DatosInvalidosException::DatosInvalidosException(string mensaje) : PokerException(mensaje)
{
}

DatosInvalidosException::DatosInvalidosException(Resultado& resultado) : PokerException(resultado.getValor())
{
	this->resultado = resultado;
}

DatosInvalidosException::~DatosInvalidosException() throw()
{
}
