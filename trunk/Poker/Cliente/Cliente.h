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
								
		bool conectar(); 
		void desconectar() {this->conectado = false;};
		
		bool iniciarConexion();
		bool recibirMsj(string& msjRecibido);
		bool enviarMsj(const string msj);
		bool finalizarConexion();
		string getSocketError();
};

#endif /*CLIENTE_H_*/
