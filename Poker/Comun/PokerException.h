#ifndef _POKEREXCEPTION_H__
#define _POKEREXCEPTION_H__

#include <iostream>
#include <cstdlib>
#include <exception>
 
using namespace std;

class PokerException : public exception
{
private:
	string mensaje;

public:
	PokerException(string mensaje);   
	virtual ~PokerException(void);
	virtual const string getMensaje() const throw();
	virtual const char* what() const throw();
};

#endif
