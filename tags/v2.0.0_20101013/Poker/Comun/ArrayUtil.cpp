
#include "ArrayUtil.h"

set<string*>* ArrayUtil::charArrayToSet(char* charArray[]) {

	set<string*>* conjunto = new set<string*>();
	bool terminado = false;
	int i = 0;

	while (!terminado) {
		if (strcmp(charArray[i], "\0") != 0){
			string* elem = new string(charArray[i]);
			conjunto->insert(elem);
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
