#include "Cliente.h"
#include "UtilTiposDatos.h"
#include "DomTree.h"
#include "XmlParser.h"
#include <fstream>

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

bool Cliente::finalizarConexion()
{
	return sock->cerrar();
}

bool Cliente::estaConectado()
{
	return this->conectado;
}

bool Cliente::recibirMsj(string& msjRecibido)
{
	return sock->recibir(msjRecibido);
}

bool Cliente::recibirMsj(string& msjRecibido, int size)
{
	return sock->recibir(msjRecibido, size);
}

bool Cliente::enviarMsj(const string msj)
{
	return sock->enviar(msj);
}

string Cliente::getSocketError()
{
	return Cliente::sock->getError();
}
