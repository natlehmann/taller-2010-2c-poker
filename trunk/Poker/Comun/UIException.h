#ifndef _UI_EXCEPTION_H_
#define _UI_EXCEPTION_H_

#include "PokerException.h"
#include "Error.h"

class UIException : public PokerException
{
public:
	UIException(string mensaje);
	UIException(string mensaje, string idError);
	UIException(Error& error);
	virtual ~UIException(void) throw();
};

#endif //_UI_EXCEPTION_H_

