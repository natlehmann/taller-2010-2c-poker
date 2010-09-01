#include "common_Cliente.h"

Cliente::Cliente()
{
}

Cliente::Cliente(const int idCliente)
{
	this->idCliente = idCliente;
	this->cantIngresos = 0;
	this->cantSalidas = 0;
	
	this->conectado = false;
	this->ipServidor = "";
	this->sock = NULL;
}

Cliente::Cliente(const int idCliente, const int puerto, const string& ipServidor)
{
	this->idCliente = idCliente;
	this->cantIngresos = -1;
	this->cantSalidas = -1;
	
	this->conectado = false;
	this->ipServidor = ipServidor;
	this->sock = new Socket(1,puerto);
}

Cliente::~Cliente()
{
	if (this->sock!=NULL)
		delete this->sock;
}

void Cliente::imprimirDatosCliente()
{
	stringstream ss;
	ss << "Puesto[" << this->getIdCliente() << "]: entraron " << this->getCantIngresos() << " salieron " << this->getCantSalidas();
	cout << ss.str();
	cout << endl;
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

string Cliente::recibirMsj()
{
	string msj;
	sock->recibir(msj);
	return msj;
}

bool Cliente::enviarMsj(const string msj)
{
	return sock->enviar(msj, msj.length());
}

bool Cliente::finalizarConexion()
{
	return sock->cerrar();
}
