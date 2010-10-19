#include "VentanaProxy.h"

VentanaProxy::VentanaProxy(void) : Ventana()
{
	this->semaforo = SDL_CreateSemaphore(1);
	this->bloqueada = false;
	this->bloqueoExterno = false;
}

VentanaProxy::~VentanaProxy(void)
{
	SDL_DestroySemaphore(this->semaforo);
}

void VentanaProxy::chequearBloquear(){
	if (!this->bloqueoExterno) {
		SDL_SemWait(this->semaforo);
	}
}

void VentanaProxy::chequearDesbloquear(){
	if (!this->bloqueoExterno) {
		SDL_SemPost(this->semaforo);
	}
}

void VentanaProxy::bloquear(){
	SDL_SemWait(this->semaforo);
	this->bloqueoExterno = true;
}

void VentanaProxy::desbloquear(){
	SDL_SemPost(this->semaforo);
	this->bloqueoExterno = false;
}

void VentanaProxy::iniciar(){
	this->chequearBloquear();
	Ventana::iniciar();
	this->chequearDesbloquear();
}

void VentanaProxy::limpiar(){
	this->chequearBloquear();
	Ventana::limpiar();
	this->chequearDesbloquear();
}

Panel* VentanaProxy::getPanelComando(){
	this->chequearBloquear();
	Panel* result = Ventana::getPanelComando();
	this->chequearDesbloquear();

	return result;
}
void VentanaProxy::setPanelComando(Panel* panel){
	this->chequearBloquear();
	Ventana::setPanelComando(panel);
	this->chequearDesbloquear();
}

void VentanaProxy::agregarElementoGrafico(ElementoGrafico* elemento){
	this->chequearBloquear();
	Ventana::agregarElementoGrafico(elemento);
	this->chequearDesbloquear();
}

void VentanaProxy::borrarElementoPorId(string id) {
	this->chequearBloquear();
	Ventana::borrarElementoPorId(id);
	this->chequearDesbloquear();
}

int VentanaProxy::getAncho(){
	this->chequearBloquear();
	int ancho = Ventana::getAncho();
	this->chequearDesbloquear();

	return ancho;
}

int VentanaProxy::getAlto(){
	this->chequearBloquear();
	int alto = Ventana::getAlto();
	this->chequearDesbloquear();

	return alto;
}

ElementoGrafico* VentanaProxy::getElementoPorId(string id){
	this->chequearBloquear();
	ElementoGrafico* result = Ventana::getElementoPorId(id);
	this->chequearDesbloquear();

	return result;
}

void VentanaProxy::borrarElemento(ElementoGrafico* elemento){
	this->chequearBloquear();
	Ventana::borrarElemento(elemento);
	this->chequearDesbloquear();
}