#ifndef THRCLIENTE_H_
#define THRCLIENTE_H_
#include "Socket.h"
#include "Thread.h"

#include "Parser.h"
#include "XmlParser.h"
#include "DomTree.h"
#include "FabricaOperaciones.h"
#include "Operacion.h"
#include "DatosInvalidosException.h"
#include "GeneradorRespuesta.h"
#include <vector>


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
					string respuesta;
					GeneradorRespuesta* generador = new GeneradorRespuesta();
					Operacion* operacion = NULL;
					Parser* parser = NULL;
					DomTree* arbol = NULL;

					try 
					{
						parser = new XmlParser();
						arbol = parser->toDom(msjRecibido);

						operacion = this->fabricaOperaciones->newOperacion(arbol);
						generador->agregarRespuestas(operacion->ejecutar());
						respuesta = generador->obtenerRespuesta();

						if (_DEBUG) {
							cout << "Procesando operacion " << operacion->getId() << " - Resultado Ok" << endl;
						}
					} 
					catch (PokerException& e) 
					{
						generador->agregarRespuesta(&e.getError());
						respuesta = generador->obtenerRespuesta();

						if (_DEBUG) {
							cout << "Procesando operacion - Resultado Error" << endl;
						}
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

					delete(generador);

					// Se envia la respuesta correspondiente				
					if(!sock->enviar(respuesta, respuesta.length()))
					{
						this->pararCliente();
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
