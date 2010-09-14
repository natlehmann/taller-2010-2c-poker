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
	ParserException(string mensaje, string idError);  
	virtual ~ParserException(void) throw();

};

#endif

