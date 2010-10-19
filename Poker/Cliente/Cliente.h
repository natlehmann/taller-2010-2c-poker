#ifndef CLIENTE_H_
#define CLIENTE_H_
#include <iostream>
#include <sstream>
#include "Socket.h"
#include "SDL_Thread.h"

class Cliente
{
	private:
		bool conectado;
		string ipServidor;
		Socket* sock;
		SDL_sem* semaforo;

		string getSocketError();
		bool enviarMsj(const string msj);
		bool recibirMsj(string& msjRecibido);
		bool recibirMsj(string& msjRecibido, int size);

	public:
		Cliente(); 
		Cliente(const int puerto, const string& ipServidor);
		virtual ~Cliente();
		
		/**
		* Este metodo no esta sincronizado y nunca debería ser llamado desde mas de un thread.
		*/
		bool iniciarConexion();

		/**
		* Este metodo no esta sincronizado y nunca debería ser llamado desde mas de un thread.
		*/
		bool finalizarConexion();

		/**
		* Este metodo no esta sincronizado y nunca debería ser llamado desde mas de un thread.
		*/
		bool estaConectado(); 

		/**
		* Envia un mensaje al servidor y espera su respuesta.
		* Devuelve un bool indicando si la operacion resulto bien o no.
		* En caso de error, se loggean las excepciones.
		* Este es un metodo sincronizado.
		*/
		bool enviarRecibir(const string mensajeEnviado, string& mensajeRecibido);

		/**
		* Envia un mensaje al servidor y espera una respuesta de un determinado tamanio.
		* Devuelve un bool indicando si la operacion resulto bien o no.
		* En caso de error, se loggean las excepciones.
		* Este es un metodo sincronizado.
		*/
		bool enviarRecibir(const string mensajeEnviado, string& mensajeRecibido, int tamanio);
		
		
};

#endif /*CLIENTE_H_*/
