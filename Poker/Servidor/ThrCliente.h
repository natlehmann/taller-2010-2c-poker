#ifndef THRCLIENTE_H_
#define THRCLIENTE_H_
#include "Socket.h"
#include "Thread.h"


class ThrCliente: public Thread
{
	private:
		bool parar;
		Socket* sock;
		
	public:	
		ThrCliente(){};
				
		ThrCliente(Socket* sockCliente)
		{
			this->sock = sockCliente;
			this->parar = false;

		};
		
		virtual ~ThrCliente(){delete this->sock;};
		
		void pararCliente()
		{
			this->parar = true;
			sock->shutdown();
		}; 
		
		virtual void Run()
		{	
			string msjRecibido = "";
			string msjRetorno = "";
			bool recibidoOK;
			bool error = true;
			
			// Comienza la entrada y salida de personas
			while (!this->parar)
			{
				// Se espera el envio del cliente
				recibidoOK = sock->recibir(msjRecibido);
				cout << msjRecibido;
				// Se envia la respuesta correspondiente
				msjRecibido = "Respuesta de " + msjRecibido;
				sock->enviar(msjRecibido, msjRecibido.length());
			}
						
			// Se desconecta el socket
			sock->cerrar();
		};
		
		bool getParar(){return this->parar;};
};

#endif /*THRCLIENTE_H_*/
