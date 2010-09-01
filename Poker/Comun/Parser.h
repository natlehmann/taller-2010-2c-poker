#ifndef _PARSER_H__
#define _PARSER_H__

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "DomTree.h"

using namespace std;

class Parser {

public:

	virtual DomTree* toDom(string texto) = 0;
	virtual string toString(DomTree* domTree) = 0;
};

#endif
