#ifndef _FILEEXCEPTION_H__
#define _FILEEXCEPTION_H__

#include <iostream>
#include <cstdlib>
#include <exception>

#include "PokerException.h"
 
using namespace std;

class FileException : public PokerException
{
public:
	FileException(string mensaje);   
	FileException(string mensaje, string idError); 
	virtual ~FileException(void) throw();
};

#endif
