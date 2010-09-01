#ifndef _PARSEREXCEPTION_H__
#define _PARSEREXCEPTION_H__

#include <iostream>
#include <cstdlib>
#include <exception>
 
using namespace std;
 
class ParserException : public exception
{
private:
	char* mensaje;

public:
	ParserException(char* mensaje);   
	virtual ~ParserException(void);
	const char* getMensaje() const throw();
};

#endif

