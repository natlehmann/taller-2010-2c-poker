#ifndef SERVIDOR_H_
#define SERVIDOR_H_
#include <iostream>
#include "ThrAceptCliente.h"
#include "ThrCliente.h"

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
		//void escucharEntradaStandard();
		void finalizarConexion();
};

#endif /*SERVIDOR_H_*/
