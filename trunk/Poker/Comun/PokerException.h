#ifndef _POKEREXCEPTION_H__
#define _POKEREXCEPTION_H__

#include <iostream>
#include <cstdlib>
#include <exception>

#include "Error.h"
 
using namespace std;

class PokerException : public exception
{
private:
	string mensaje;
	Error error;

public:
	PokerException(string mensaje); 
	PokerException(Error& error);
	virtual ~PokerException(void);

	virtual const string getMensaje() const throw();
	virtual const char* what() const throw();

	Error getError() const
    {
        return error;
    }
};

#endif
