#ifndef SERVIDOR_H_
#define SERVIDOR_H_
#include <iostream>
#include "common_General.h"
#include "server_ThrAceptCliente.h"
#include "server_ThrCliente.h"

class Servidor
{
	private:
		int puerto;
		ThrAceptCliente* tAcepCliente;
			
	public:
		Servidor();
		Servidor(const int port);
		virtual ~Servidor();
		
		void iniciarConexion();
		void escucharEntradaStandard();
		void finalizarConexion();
};

#endif /*SERVIDOR_H_*/
