
#include "ArrayUtil.h"

set<char*>* ArrayUtil::charArrayToSet(char* charArray[]){
	
	set<char*>* conjunto = new set<char*>();
	bool terminado = false;
	int i = 0;

	while (!terminado) {
		if (charArray[i] != "\0"){
			conjunto->insert(charArray[i]);
			i++;

		} else {
			terminado = true;
		}
	}

	return conjunto;
	
}

char* ArrayUtil::stringToCharArray(string texto) {
	char* buffer = new char[texto.size()];
	strcpy(buffer, texto.c_str());

	return buffer;
}
