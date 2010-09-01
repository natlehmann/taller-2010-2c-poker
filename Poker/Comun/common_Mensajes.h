#ifndef MENSAJES_H_
#define MENSAJES_H_
// Mensajes recibidos por el Servidor
#define SOY   "SOY"
#define ENTRA "ENTRA"
#define SALE  "SALE"
#define FIN   "FIN"
// Mensajes recibidos por el Cliente
#define SI 	  "SI"
#define NO    "NO"
#define ERRORS "ERROR"

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include "common_General.h"

using namespace std;

class Mensajes
{
	public:
		Mensajes();
		virtual ~Mensajes();
		
		// Mensajes enviados por el servidor
		static string msjBienvenida() {return "HOLA\n";};
		static string msjSI() {return "SI\n";};
		static string msjNO() {return "NO\n";};
		static string msjFIN() {return "FIN\n";};
		static string msjERROR() {return "ERROR\n";};
		
		// Mensajes enviados por el cliente
		static string msjSOY(const int idCliente);
				
		// Metodos utilizados por el servidor
		static int identificarCliente(string& msjCli); // Mensaje del Cliente: "SOY i\n"
		static string responderMsjClie(string &msjCli, string &cmd, int &idPersona);
	
		// Metodos utilizados por el cliente
		static bool validarBienvenida(const string& msjSrv);
		static bool validarMsjServ(const string& msjSrv);
		
	private:
	
		static void parsearMsj(string &msj, string &cmd, int &id);
	 	 
}; 

#endif /*MENSAJES_H_*/
