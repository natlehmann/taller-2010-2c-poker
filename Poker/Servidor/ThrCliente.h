#ifndef THRCLIENTE_H_
#define THRCLIENTE_H_
#include "Socket.h"
#include "Thread.h"

#include "Parser.h"
#include "XmlParser.h"
#include "DomTree.h"
#include "FabricaOperaciones.h"
#include "Operacion.h"


class ThrCliente: public Thread
{
	private:
		bool parar;
		Socket* sock;
		FabricaOperaciones* fabricaOperaciones;
		
	public:	
		ThrCliente(){
			this->fabricaOperaciones = new FabricaOperaciones();
		};
				
		ThrCliente(Socket* sockCliente)
		{
			this->sock = sockCliente;
			this->parar = false;
			this->fabricaOperaciones = new FabricaOperaciones();

		};
		
		virtual ~ThrCliente(){
			delete (this->sock);
			delete (this->fabricaOperaciones);
		};
		
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
			
			string msjAcumulado = "";

			// Comienza la entrada y salida de personas
			while (!this->parar)
			{
				// Se espera el envio del cliente
				recibidoOK = sock->recibir(msjRecibido);

				msjAcumulado = msjAcumulado + msjRecibido;

				if (!recibidoOK) {
					this->parar = true;
				}
			}

			cout << "VA MENSAJE TOTAL = " << endl << msjAcumulado << endl;
			try {
				Parser* parser = new XmlParser();
				DomTree* arbol = parser->toDom(msjAcumulado);

				Operacion* operacion = this->fabricaOperaciones->newOperacion(arbol);

				// TODO : enviar operacion e generador de respuestas
				// eso tiene que generar tanto resultado como error
				cout << operacion->getId() << " " << endl;



			} catch (PokerException& e) {
				// TODO 
				//////
				cout << e.what() << endl;
			}


				// Se envia la respuesta correspondiente
				msjRecibido = "Respuesta de " + msjRecibido;
				
				/*
				if(!sock->enviar(msjRecibido, msjRecibido.length()))
				{
					this->pararCliente();
				}
				*/

				

						
			// Se desconecta el socket
			sock->cerrar();
		};
		
		bool getParar(){return this->parar;};
};

#endif /*THRCLIENTE_H_*/
