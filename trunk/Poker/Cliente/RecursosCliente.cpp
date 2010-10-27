#include "RecursosCliente.h"

// inicializacion de miembros estaticos
Properties RecursosCliente::config("..\\Cliente\\config.ini");
Log RecursosCliente::log("..\\logs\\errores.err");

RecursosCliente::RecursosCliente(void)
{
}

RecursosCliente::~RecursosCliente(void)
{
}

Properties* RecursosCliente::getConfig(){
	RecursosCliente::config.setNombreArchivo("..\\Cliente\\config.ini");
	return &config;
}

Log* RecursosCliente::getLog(){
	RecursosCliente::log.setNombreArchivo("..\\logs\\errores.err");
	return &log;
}
