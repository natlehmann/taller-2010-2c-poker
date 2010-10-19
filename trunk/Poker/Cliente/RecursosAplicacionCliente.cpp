#include "RecursosAplicacionCliente.h"

// inicializacion de miembros estaticos
Properties RecursosAplicacionCliente::parserConfig("..\\Comun\\parserConfig.properties");
Properties RecursosAplicacionCliente::config("..\\Cliente\\config.ini");
Log RecursosAplicacionCliente::log("..\\logs\\errores.err");

RecursosAplicacionCliente::RecursosAplicacionCliente(void)
{
}

RecursosAplicacionCliente::~RecursosAplicacionCliente(void)
{
}


Properties* RecursosAplicacionCliente::getParserConfig(){
	return &parserConfig;
}

Properties* RecursosAplicacionCliente::getConfig(){
	return &config;
}

Log* RecursosAplicacionCliente::getLog(){
	return &log;
}



