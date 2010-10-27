#include "RecursosServidor.h"

Properties RecursosServidor::config("..\\Servidor\\config.ini");
Log RecursosServidor::log("..\\logs\\serv-errores.err");

RecursosServidor::RecursosServidor(void)
{
}

RecursosServidor::~RecursosServidor(void)
{
}

Properties* RecursosServidor::getConfig(){
	RecursosServidor::config.setNombreArchivo("..\\Servidor\\config.ini");
	return &RecursosServidor::config;
}

Log* RecursosServidor::getLog(){
	RecursosServidor::log.setNombreArchivo("..\\logs\\serv-errores.err");
	return &RecursosServidor::log;
}
