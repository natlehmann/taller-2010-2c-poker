#include "Servidor.h"

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

void Servidor::finalizarConexion()
{
	this->tAcepCliente->pararAceptaciones();
	this->tAcepCliente->Wait();
	delete this->tAcepCliente;
}

