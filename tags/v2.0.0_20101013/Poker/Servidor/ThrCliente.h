#ifndef THRCLIENTE_H_
#define THRCLIENTE_H_
#include "Socket.h"
#include "Thread.h"

#include "Parser.h"
#include "XmlParser.h"
#include "DomTree.h"
#include "FabricaOperacionesServidor.h"
#include "Operacion.h"
#include "DatosInvalidosException.h"
#include "GeneradorRespuesta.h"
#include <vector>


class ThrCliente: public Thread
{
	private:
		bool parar;
		Socket* sock;
		FabricaOperacionesServidor* fabricaOperaciones;
		
	public:	
		ThrCliente(){
			this->fabricaOperaciones = new FabricaOperacionesServidor();
		};
				
		ThrCliente(Socket* sockCliente)
		{
			this->sock = sockCliente;
			this->parar = false;
			this->fabricaOperaciones = new FabricaOperacionesServidor();

		};
		
		virtual ~ThrCliente(){
			delete (this->sock);
			delete (this->fabricaOperaciones);
		};
		
		void pararCliente()
		{
			this->parar = true;
			//sock->shutdown();
			sock->cerrar();
		}; 
		
		virtual void Run()
		{	
			while (!this->parar) 
			{
				string msjRecibido = "";
				bool recibidoOK;
				
				recibidoOK = sock->recibir(msjRecibido);

				if ((recibidoOK)&&(msjRecibido!=""))
				{
					Operacion* operacion = NULL;
					Parser* parser = NULL;
					DomTree* arbol = NULL;

					try 
					{
						parser = new XmlParser();
						arbol = parser->toDom(msjRecibido);

						operacion = this->fabricaOperaciones->newOperacion(arbol);
						if (operacion->ejecutar(sock))
							this->pararCliente();

					} 
					catch (PokerException& e) 
					{
						GeneradorRespuesta* generador = new GeneradorRespuesta();
						generador->agregarRespuesta(&e.getError());
						string respuesta = generador->obtenerRespuesta();

						// Se envia la respuesta correspondiente				
						if(!sock->enviar(respuesta))
							this->pararCliente();

						delete(generador);
					}

					if (parser != NULL) {
						delete(parser);
					}

					if (arbol != NULL) {
						delete(arbol);
					}

					if (operacion != NULL) {
						delete(operacion);
					}

				}
				else
				{
					this->pararCliente();
				}
			}
			
			// Se desconecta el socket
			sock->cerrar();
		};
		
		bool getParar(){return this->parar;};
};

#endif /*THRCLIENTE_H_*/
