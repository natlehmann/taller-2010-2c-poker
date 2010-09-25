#include "RecursosAplicacion.h"

Properties RecursosAplicacion::parserConfigProperties("..\\Comun\\parserConfig.properties");

RecursosAplicacion::RecursosAplicacion(void)
{
}

RecursosAplicacion::~RecursosAplicacion(void)
{
}


Properties* RecursosAplicacion::getParserConfigProperties(){
	return &parserConfigProperties;
}



