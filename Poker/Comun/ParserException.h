#ifndef _PARSEREXCEPTION_H__
#define _PARSEREXCEPTION_H__

#include <iostream>
#include <cstdlib>
#include <exception>

#include "PokerException.h"
 
using namespace std;
 
class ParserException : public PokerException
{

public:
	ParserException(string mensaje);   
	virtual ~ParserException(void);

};

#endif

