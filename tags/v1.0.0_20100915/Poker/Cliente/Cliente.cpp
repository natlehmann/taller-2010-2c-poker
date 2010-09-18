#include "Cliente.h"

Cliente::Cliente()
{
}

Cliente::Cliente(const int puerto, const string& ipServidor)
{
	this->conectado = false;
	this->ipServidor = ipServidor;
	this->sock = new Socket(1,puerto);
}

Cliente::~Cliente()
{
	if (this->sock!=NULL)
		delete this->sock;
}

bool Cliente::iniciarConexion()
{
	return sock->conectar(this->ipServidor);
}

bool Cliente::conectar()
{
	if (!this->conectado)
	{
		this->conectado = true;
		return true;
	}
	else
		return false;
}

bool Cliente::recibirMsj(string& msjRecibido)
{
	return sock->recibir(msjRecibido);
}

bool Cliente::enviarMsj(const string msj)
{
	return sock->enviar(msj, msj.length());
}

bool Cliente::finalizarConexion()
{
	return sock->cerrar();
}

string Cliente::getSocketError()
{
	return sock->getError();
}
