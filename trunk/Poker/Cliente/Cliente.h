#ifndef CLIENTE_H_
#define CLIENTE_H_
#include <iostream>
#include <sstream>
#include "Socket.h"

class Cliente
{
	private:
		bool conectado;
		string ipServidor;
		Socket* sock;

	public:
		Cliente(); 
		Cliente(const int puerto, const string& ipServidor);
		virtual ~Cliente();
		
		bool iniciarConexion();
		bool finalizarConexion();
		bool estaConectado(); 
		bool recibirMsj(string& msjRecibido);
		bool recibirMsj(string& msjRecibido, int size);
		bool enviarMsj(const string msj);
		string getSocketError();
};

#endif /*CLIENTE_H_*/
