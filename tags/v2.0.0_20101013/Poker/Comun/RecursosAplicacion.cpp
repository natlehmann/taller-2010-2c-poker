#include "RecursosAplicacion.h"

// inicializacion de miembros estaticos
Properties RecursosAplicacion::parserConfigProperties("..\\Comun\\parserConfig.properties");
Properties RecursosAplicacion::clienteConfigProperties("..\\Cliente\\config.ini");
Properties RecursosAplicacion::servidorConfigProperties("..\\Servidor\\config.ini");

Log RecursosAplicacion::logErroresCliente("..\\logs\\errores.err");
Log RecursosAplicacion::logErroresServidor("..\\logs\\serv-errores.err");

RecursosAplicacion::RecursosAplicacion(void)
{
}

RecursosAplicacion::~RecursosAplicacion(void)
{
}


Properties* RecursosAplicacion::getParserConfigProperties(){
	return &parserConfigProperties;
}

Properties* RecursosAplicacion::getClienteConfigProperties(){
	return &clienteConfigProperties;
}

Properties* RecursosAplicacion::getServidorConfigProperties(){
	return &servidorConfigProperties;
}

Log* RecursosAplicacion::getLogErroresCliente(){
	return &logErroresCliente;
}

Log* RecursosAplicacion::getLogErroresServidor(){
	return &logErroresServidor;
}



