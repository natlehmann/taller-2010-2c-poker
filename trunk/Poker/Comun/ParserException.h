#ifndef _PARSEREXCEPTION_H__
#define _PARSEREXCEPTION_H__

#include <iostream>
#include <cstdlib>
#include <exception>
 
using namespace std;
 
class ParserException : public exception
{
private:
	string mensaje;

public:
	ParserException(string mensaje);   
	virtual ~ParserException(void);
	const string getMensaje() const throw();
	virtual const char* what() const throw();

};

#endif

