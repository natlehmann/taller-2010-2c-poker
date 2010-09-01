#ifndef CLIENTE_H_
#define CLIENTE_H_
#include <iostream>
#include <sstream>
#include "common_Socket.h"

class Cliente
{
	private:
		int idCliente;
		int cantIngresos;
		int cantSalidas;
		bool conectado;
		
		string ipServidor;
		Socket* sock;
				
	public:
		Cliente(); 
		Cliente(const int idCliente);
		Cliente(const int idCliente, const int puerto, const string& ipServidor);
		virtual ~Cliente();
		
		void setIdCliente(const int idCliente) {this->idCliente = idCliente;};
								
		int getIdCliente()const {return this->idCliente;};
		int getCantIngresos()const {return this->cantIngresos;};
		int getCantSalidas()const {return this->cantSalidas;}
		
		bool conectar(); 
		void desconectar() {this->conectado = false;};
		
		void registrarIngreso(){this->cantIngresos = this->cantIngresos + 1;}
		void registrarSalida(){this->cantSalidas = this->cantSalidas + 1;}
				
		void imprimirDatosCliente();
		
		bool iniciarConexion();
		string recibirMsj();
		bool enviarMsj(const string msj);
		bool finalizarConexion();
};

#endif /*CLIENTE_H_*/
