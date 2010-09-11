#include "Error.h"

Error::Error(void){
}

Error::Error(string id, string valor, string idOperacion) : Respuesta(id, valor, idOperacion){
}

Error::~Error(void)
{
}

bool Error::isError(){
	return true;
}
