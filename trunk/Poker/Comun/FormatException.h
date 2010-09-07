#ifndef _FORMATEXCEPTION_H__
#define _FORMATEXCEPTION_H__

#include <iostream>
#include <cstdlib>
#include <exception>

#include "PokerException.h"
 
using namespace std;

class FormatException : public PokerException
{
public:
	FormatException(string mensaje);
	~FormatException(void);
};

#endif
