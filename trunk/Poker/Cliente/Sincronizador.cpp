#include "Sincronizador.h"
#include "ServiciosGraficos.h"

Sincronizador* Sincronizador::instancia = new Sincronizador();

Sincronizador::Sincronizador(void)
{
	this->ventanaAuxiliar = NULL;
	this->ventana = NULL;
	this->superficie = NULL;
	this->syncMutex = SDL_CreateMutex();
}

Sincronizador::~Sincronizador(void)
{
	SDL_DestroyMutex(this->syncMutex);
	this->syncMutex = NULL;

	if (this->ventanaAuxiliar != NULL) {
		delete (this->ventanaAuxiliar);
		this->ventanaAuxiliar = NULL;
	}

	/*
	if (this->superficie != NULL) {
		SDL_FreeSurface(this->superficie);
	}
	*/
}

Sincronizador* Sincronizador::getInstancia(){
	return Sincronizador::instancia;
}

VentanaAuxiliar* Sincronizador::getVentanaAuxiliar(){

	SDL_LockMutex(this->syncMutex);

	if (this->ventanaAuxiliar == NULL){
		this->ventanaAuxiliar = new VentanaAuxiliar();
		this->ventanaAuxiliar->setAncho(ServiciosGraficos::getAnchoVentana());
		this->ventanaAuxiliar->setAlto(ServiciosGraficos::getAltoVentana());
		this->ventanaAuxiliar->setPosX(0);
		this->ventanaAuxiliar->setPosY(0);
	}

	return this->ventanaAuxiliar;
}

void Sincronizador::notificarCambio(){

	if (this->ventanaAuxiliar != NULL) {

		if (this->superficie == NULL) {
			this->superficie = ServiciosGraficos::crearSuperficie(
				this->ventanaAuxiliar->getAncho(), this->ventanaAuxiliar->getAlto());
		}

		this->ventanaAuxiliar->setSuperficie(this->superficie);
		this->ventanaAuxiliar->dibujar(this->superficie);

		ventana->merge(this->superficie);

		ventana->setPanelComando(this->ventanaAuxiliar->getPanelComando());
	}

	if (this->syncMutex != NULL) {
		SDL_UnlockMutex(this->syncMutex);
	}
}

void Sincronizador::registrarVentana(Ventana* ventana){
	this->ventana = ventana;
}

void Sincronizador::limpiar() {
	this->ventanaAuxiliar->limpiarFotosJugadores();
	if (this->ventanaAuxiliar != NULL) {
		delete (this->ventanaAuxiliar);
		this->ventanaAuxiliar = NULL;
		this->superficie = NULL;
	}
}

