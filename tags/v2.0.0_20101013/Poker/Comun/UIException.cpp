#include "UIException.h"

UIException::UIException(string mensaje) : PokerException(mensaje)
{
}

UIException::UIException(string mensaje, string idError) 
		: PokerException(mensaje, idError){
}

UIException::UIException(Error& error) : PokerException(error)
{
}

UIException::~UIException() throw()
{
}
