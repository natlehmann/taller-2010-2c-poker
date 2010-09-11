#ifndef SOCKET_H_
#define SOCKET_H_

#include <string>
#include <winsock.h>
#include <winerror.h>
#include <stdio.h>
#include <string.h>

const int MAXRECV = 100;

using namespace std;

class Socket
{
	private:
		int sockfd;
		int cantConexiones;
		int puerto;
		bool valido;
		string msgError;
		
		Socket(const int sockfd); // constructor privado
		
		bool abrir();
		bool bindear();
		string generarMensajeError();
		bool cvtLPW2stdstring(std::string& s, const LPWSTR pw, UINT codepage);


	public:
		Socket();
		Socket(const int cantConexiones, const int puerto);
		virtual ~Socket();
				
		// Metodos exclusivos para Servidor
		bool escuchar();
		Socket* aceptar();
		
		// Metodo exclusivo para Cliente
		bool conectar(const string& host);
		
		// Metodos para Servidor y Cliente
		bool enviar(const string msg, const int longMsg);
		bool recibir(string& msg);		
		bool cerrar();
						
		bool shutdown();
		bool inicializarConexiones();
		bool limpiarConexiones();
		bool esValido();

		
};

#endif /*SOCKET_H_*/
