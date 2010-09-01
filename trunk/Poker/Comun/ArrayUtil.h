#ifndef _ARRAYUTIL_H__
#define _ARRAYUTIL_H__

#define _CRT_SECURE_NO_DEPRECATE 1

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <set>

using namespace std;

class ArrayUtil
{
public:
	static set<char*>* charArrayToSet(char* charArray[]);
	static char* stringToCharArray(string texto);
};

#endif
