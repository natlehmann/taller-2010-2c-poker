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
				string msjRetorno = "";
				bool recibidoOK;
				bool error = true;
				
				recibidoOK = sock->recibir(msjRecibido);

				if (recibidoOK)
				{
					GeneradorRespuesta* generador = new GeneradorRespuesta();
					Operacion* operacion = NULL;

					try 
					{
						Parser* parser = new XmlParser();
						DomTree* arbol = parser->toDom(msjRecibido);

						operacion = this->fabricaOperaciones->newOperacion(arbol);
						generador->agregarRespuestas(operacion->ejecutar());

						if (_DEBUG) {
							cout << "Procesando operacion id " << operacion->getId() << endl;
						}

					} 
					catch (PokerException& e) 
					{
						if (operacion != NULL) {
							e.getError().setIdOperacion(operacion->getId());
						}

						generador->agregarRespuesta(&e.getError());

						if (_DEBUG) {
							cout << "Operacion finalizo con errores." << endl;
						}
					}

					string respuesta = generador->obtenerRespuesta();
					delete(generador);

					// Se envia la respuesta correspondiente				
					if(!sock->enviar(respuesta, respuesta.length()))
					{
						this->pararCliente();
					}
				}

			}
			
			// Se desconecta el socket
			sock->cerrar();
		};
		
		bool getParar(){return this->parar;};
};

#endif /*THRCLIENTE_H_*/
