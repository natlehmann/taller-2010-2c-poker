#ifndef THRACEPTCLIENTE_H_
#define THRACEPTCLIENTE_H_
#include <list>
#include "common_General.h"
#include "server_Thread.h"
#include "server_ThrCliente.h"

class ThrAceptCliente: public Thread
{
	private:
		int puerto;
		bool parar;
		Socket socket;
		
		list<ThrCliente*> listaThrClientes; // Lista con las referencias a los hilos clientes

	public:
		ThrAceptCliente(){}; 
		
		ThrAceptCliente(const int puerto): socket(CANTCLIENTES, puerto), listaThrClientes()
		{
			this->puerto = puerto;
			this->parar = false;
		};
		
		virtual ~ThrAceptCliente(){};
		
		void pararAceptaciones()
		{
			this->parar = true;
			this->socket.shutdown();
		};
		
		virtual void Run()
		{
			Socket* sockCliente;
			ThrCliente* nuevoThrCliente;
			bool aceptarConexion = true;
			
			if (this->socket.escuchar())	// Se comienza a escuchar los clientes entrantes
			{
				
				while(!this->parar)
				{
					sockCliente = this->socket.aceptar();	// Se conecta el cliente entrante
					
					if (listaThrClientes.size() < 10)
						aceptarConexion = true;
					else
						aceptarConexion = false;
						
					if ((sockCliente != NULL) && (!this->parar))
					{
						nuevoThrCliente = new ThrCliente(sockCliente, aceptarConexion); 
						// Se inserta la referencia del hilo en la lista
						listaThrClientes.push_back(nuevoThrCliente); 
						// Se lanza el hilo para la conversacion con el cliente
						nuevoThrCliente->CreateNewThread(); 
						
						// Se libera los hilos de los clientes finalizados
						liberarThreadsFinalizados();
					}

				} 
				
				// Se decidio finalizar las aceptaciones --> se debe finalizar las conexiones y liberar los hilos de la lista
				liberarThreads();
			}
			
			// Se cierra el socket
			socket.cerrar();
			
			//return NULL;
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
