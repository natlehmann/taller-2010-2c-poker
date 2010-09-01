#ifndef THRCLIENTE_H_
#define THRCLIENTE_H_
#include "common_General.h"
#include "common_Mensajes.h" 
#include "common_Socket.h"
#include "server_Thread.h"
//#include "server_Mutex.h" 

class ThrCliente: public Thread
{
	private:
		bool parar;
		bool aceptarConexion;
		Socket* sock;
		//Mutex clie_mutex;
		
	public:	
		ThrCliente(){};
				
		ThrCliente(Socket* sockCliente, const bool aceptarConexion)
		{
			this->sock = sockCliente;
			
			this->parar = false;
			
			this->aceptarConexion = aceptarConexion;
		};
		
		virtual ~ThrCliente(){delete this->sock;};
		
		void pararCliente()
		{
			this->parar = true;
			sock->shutdown();
		}; 
		
		virtual void Run()
		{	
			string msjBienvenida = "HOLA\n";
			string msjRecibido = "";
			string msjRetorno = "";
			bool recibidoOK;
			int idCliente;

			bool error = true;
			
			if (this->aceptarConexion)
			{
				// Se comienza el protocolo con el mensaje de bienvenida hacia el cliente
				sock->enviar(msjBienvenida, msjBienvenida.length());
			
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
			}
						
			// Se desconecta el socket
			sock->cerrar();
			//return NULL;
		};
		
		bool getParar(){return this->parar;};
};

#endif /*THRCLIENTE_H_*/
