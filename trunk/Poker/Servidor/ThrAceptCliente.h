#ifndef THRACEPTCLIENTE_H_
#define THRACEPTCLIENTE_H_
#include <list>
#include "Thread.h"
#include "ThrCliente.h"


class ThrAceptCliente: public Thread
{
	private:
		int puerto;
		bool parar;
		Socket socket;
		
		list<ThrCliente*> listaThrClientes; // Lista con las referencias a los hilos clientes

	public:
		ThrAceptCliente(){}; 
		
		ThrAceptCliente(const int puerto): socket(100, puerto), listaThrClientes()
		{
			this->puerto = puerto;
			this->parar = false;
		};
		
		virtual ~ThrAceptCliente(){};
		
		void pararAceptaciones()
		{
			this->parar = true;
			//this->socket.shutdown();
			this->socket.cerrar();
		};
		
		virtual void Run()
		{
			Socket* sockCliente;
			ThrCliente* nuevoThrCliente;
					
			if (this->socket.inicializarConexiones())	// Se inicializa el winsock del programa y define la versión a utilizar
			{
				if (this->socket.escuchar())			// Se comienza a escuchar los clientes entrantes
				{
					while(!this->parar)
					{
						sockCliente = this->socket.aceptar();	// Se conecta el cliente entrante
										
						if ((sockCliente != NULL) && (!this->parar))
						{
							nuevoThrCliente = new ThrCliente(sockCliente); 
							// Se inserta la referencia del hilo en la lista
							listaThrClientes.push_back(nuevoThrCliente); 
							// Se lanza el hilo para la conversacion con el cliente
							nuevoThrCliente->CreateNewThread(); 
							
							// Se libera los hilos de los clientes finalizados
							liberarThreadsFinalizados();
						}
					} 
				
					// Se decidio finalizar las aceptaciones 
					// --> se debe finalizar las conexiones y liberar los hilos de la lista
					liberarThreads();
				}
			
				// Se cierra el socket
				//socket.cerrar();
				socket.limpiarConexiones();

			}
			else
			{
			
			}
		};
		
		void liberarThreadsFinalizados()
		{
			ThrCliente* thrCliente;
			list<ThrCliente*>::iterator iter;
						
			iter = listaThrClientes.begin();
				
			while (iter != listaThrClientes.end())
			{
				thrCliente = (*iter);
						
				if ((thrCliente != NULL) && (thrCliente->getParar()))
				{
					thrCliente->Wait();
					delete thrCliente;
					iter = listaThrClientes.erase(iter);		
				}
				else
				{
					iter++;
				}	
			}
		};
		
		void liberarThreads()
		{
			ThrCliente* thrCliente;
			
			list<ThrCliente*>::iterator iter;
			
			// Se desconecta los clientes y se libera la memoria del puntero a los hilos
			for (iter = listaThrClientes.begin(); iter != listaThrClientes.end(); iter++)
			{
				thrCliente = (*iter);
				
				if (thrCliente != NULL)
				{
					thrCliente->pararCliente();
					thrCliente->Wait();
					delete thrCliente;
				}
			}
			// Se libera la memoria de la lista
			listaThrClientes.clear();
		};
};

#endif /*THRACEPTCLIENTE_H_*/
