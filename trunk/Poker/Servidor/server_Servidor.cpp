#include "server_Servidor.h"

Servidor::Servidor()
{
}

Servidor::Servidor(const int puerto)
{
	this->puerto = puerto;
}

Servidor::~Servidor()
{
}

void Servidor::iniciarConexion()
{
	tAcepCliente = new ThrAceptCliente(puerto);
	tAcepCliente->CreateNewThread();
}

void Servidor::escucharEntradaStandard()
{
	bool fin = false;
	string entrada;
	
	while (!fin)
	{
		cin >> entrada;
		
		if (entrada.compare("x")==0 || entrada.compare("X") ==0)
			fin = true;
	}
}

void Servidor::finalizarConexion()
{
	this->tAcepCliente->pararAceptaciones();
	this->tAcepCliente->Wait();
	delete this->tAcepCliente;
}

