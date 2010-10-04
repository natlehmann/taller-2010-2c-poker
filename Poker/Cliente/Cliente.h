#ifndef CLIENTE_H_
#define CLIENTE_H_
#include <iostream>
#include <sstream>
#include "Socket.h"

class Cliente
{
	private:
		static bool conectado;
		static string ipServidor;
		static Socket* sock;
		
		Cliente(); 
		virtual ~Cliente();

	public:
		static bool iniciarConexion(const int puerto, const string& ipServidor);
		static bool finalizarConexion();
		static bool estaConectado(); 
		static bool recibirMsj(string& msjRecibido);
		static bool enviarMsj(const string msj);
		static bool solicitarArchivo(string& nombreArchivo, string& pathDestino);
		static string getSocketError();
};

#endif /*CLIENTE_H_*/
