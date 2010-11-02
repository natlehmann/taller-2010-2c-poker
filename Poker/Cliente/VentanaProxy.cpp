#include "VentanaProxy.h"

VentanaProxy::VentanaProxy(void) : VentanaImpl()
{
	this->semaforo = SDL_CreateSemaphore(1);
	this->bloqueada = false;
	this->bloqueoExterno = false;
	this->ventanaMutex = SDL_CreateMutex();
}

VentanaProxy::~VentanaProxy(void)
{
	SDL_DestroySemaphore(this->semaforo);
	SDL_DestroyMutex(this->ventanaMutex);
}
/*
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
*/

void VentanaProxy::bloquear(){
	if (!this->bloqueoExterno) {
		//SDL_SemWait(this->semaforo);
		//Ventana::bloquear();
		SDL_LockMutex(this->ventanaMutex);
		this->bloqueoExterno = true;
	}
}

void VentanaProxy::desbloquear(){
	this->bloqueoExterno = false;
	//SDL_SemPost(this->semaforo);
	//Ventana::desbloquear();
	SDL_UnlockMutex(this->ventanaMutex);
}
/*
void VentanaProxy::iniciar(){
	this->bloquear();
	Ventana::dibujar(NULL);
	this->desbloquear();

	//this->chequearBloquear();
	Ventana::iniciar();
	//this->chequearDesbloquear();
}

void VentanaProxy::limpiar(){
	this->chequearBloquear();
	Ventana::limpiar();
	this->chequearDesbloquear();
}

void VentanaProxy::forzarRefresh(ElementoGrafico* elemento) {
	this->chequearBloquear();
	Ventana::forzarRefresh(elemento);
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

void VentanaProxy::dibujar(SDL_Surface* superficie){
	this->chequearBloquear();
	Ventana::dibujar(superficie);
	this->chequearDesbloquear();
}

void VentanaProxy::dibujarSobreSup(SDL_Surface* superficie){
	//this->chequearBloquear();
	Ventana::dibujarSobreSup(superficie);
	//this->chequearDesbloquear();
}
*/