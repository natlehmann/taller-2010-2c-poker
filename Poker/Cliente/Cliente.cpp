#include "Cliente.h"
#include "UtilTiposDatos.h"
#include "DomTree.h"
#include "XmlParser.h"
#include "RecursosAplicacion.h"
#include <fstream>

Cliente::Cliente()
{
	this->semaforo = SDL_CreateSemaphore(1); 
}

Cliente::Cliente(const int puerto, const string& ipServidor)
{
	this->conectado = false;
	this->ipServidor = ipServidor;
	this->sock = new Socket(1,puerto);

	this->semaforo = SDL_CreateSemaphore(1); 
}

Cliente::~Cliente()
{
	if (this->sock!=NULL){
		delete this->sock;
	}
	if (this->semaforo != NULL) {
		SDL_DestroySemaphore(this->semaforo);
	}
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

bool Cliente::enviarRecibir(const string mensajeEnviado, string& mensajeRecibido){

	bool enviado = false;
	bool recibido = false;

	SDL_SemWait(this->semaforo);
	try {

		enviado = this->enviarMsj(mensajeEnviado);
		recibido = this->recibirMsj(mensajeRecibido);
	
	} catch (...) {
		RecursosAplicacion::getLogErroresCliente()->escribir(
			"Error al enviar el siguiente mensaje al servidor: " + mensajeEnviado);
	}

	SDL_SemPost(this->semaforo);

	return enviado && recibido;
}

bool Cliente::enviarRecibir(const string mensajeEnviado, string& mensajeRecibido, int tamanio){

	bool enviado = false;
	bool recibido = false;

	SDL_SemWait(this->semaforo);
	try {

		enviado = this->enviarMsj(mensajeEnviado);
		recibido = this->recibirMsj(mensajeRecibido, tamanio);
	
	} catch (...) {
		RecursosAplicacion::getLogErroresCliente()->escribir(
			"Error al enviar el siguiente mensaje al servidor: " + mensajeEnviado);
	}

	SDL_SemPost(this->semaforo);

	return enviado && recibido;
}

string Cliente::getSocketError()
{
	return Cliente::sock->getError();
}
