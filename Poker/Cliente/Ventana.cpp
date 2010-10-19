#include "Ventana.h"
#include "RecursosAplicacion.h"
#include "MensajesUtil.h"
#include "DatosInvalidosException.h"
#include "UtilTiposDatos.h"
#include "UIException.h"
#include "Timer.h"
#include "Boton.h"
#include "FabricaOperacionesCliente.h"
#include <typeinfo.h>

Ventana::Ventana(void) {

	this->superficie = NULL;
	this->posX = 0;
	this->posY = 0;
	this->offset = new SDL_Rect();
	this->contorno = new SDL_Rect();
	this->hayCambios = true;
	this->id = "";
	this->posicion = -1;

	string configPantalla = RecursosAplicacion::getClienteConfigProperties()->get(
		"cliente.configuracion.pantalla");
	list<string> medidas = MensajesUtil::split(configPantalla, "x");

	if (medidas.size() != 2) {
		throw DatosInvalidosException(
			"La configuracion de pantalla esta incorrectamente seteada en el archivo 'config.ini'.", "V");
	}

	int ancho = UtilTiposDatos::getEntero(medidas.front());
	int alto = UtilTiposDatos::getEntero(medidas.back());

	if (ancho < 0 || alto < 0) {
		throw DatosInvalidosException(
			"El ancho o el alto de la configuracion de pantalla en el archivo 'config.ini' no es un numero entero.", "V");
	}

	this->setAncho(ancho);
	this->setAlto(alto);

	this->pantalla = SDL_SetVideoMode(this->ancho, this->alto, RESOLUCION_PANTALLA, SDL_SWSURFACE);

	if (this->pantalla == NULL) {
		throw UIException("No se pudo inicializar la ventana de la aplicacion.","E");
	}

	SDL_WM_SetCaption(RecursosAplicacion::getClienteConfigProperties()->get(
		"cliente.configuracion.mensaje").c_str(), NULL); 

	this->panelComando = NULL;
	this->mesa = NULL;
}

Ventana::~Ventana(void)
{
	if (this->panelComando != NULL) {
		delete(this->panelComando);
	}

	for (list<ElementoGrafico*>::iterator it = this->elementos.begin();
		it != this->elementos.end(); it++) {
			delete(*it);
	}
	this->elementos.clear();

	if (this->superficie != NULL) {
		SDL_FreeSurface(this->superficie);
		this->superficie = NULL;
	}
	delete (this->offset);
	delete (this->contorno);

}

void Ventana::agregarElementoGrafico(ElementoGrafico* elemento) {
	this->elementos.push_back(elemento);

	if (MensajesUtil::sonIguales(typeid(*elemento).name(), "class Mesa")){
		this->mesa = (Mesa*)elemento;
	}

	this->hayCambios = true;
	elemento->setVentana(this);
}

void Ventana::limpiar() {

	for (list<ElementoGrafico*>::iterator it = this->elementos.begin();
		it != this->elementos.end(); it++) {
			delete(*it);
	}
	this->elementos.clear();

	delete(this->panelComando);
	this->panelComando = NULL;
}


void Ventana::borrarElemento(ElementoGrafico* elemento){
	if (this->mesa != NULL && this->mesa->getFondo() != NULL) {

		this->mesa->getFondo()->generarSuperficie();

		//si algo salio mal
		if (this->mesa->getFondo()->getSuperficie() == NULL) {
			throw UIException(
				"No se pudo borrar la region de un elemento porque no se pudo cargar la imagen de la mesa.", "E");
		}

		SDL_Rect region;
		region.h = elemento->getAlto();
		region.w = elemento->getAncho();
		region.x = elemento->getPosX();
		region.y = elemento->getPosY();

		SDL_BlitSurface(this->mesa->getFondo()->getSuperficie(), &region, 
			this->pantalla, &region); 
	}
}


void Ventana::iniciar() {

	// se dibuja inicialmente
	this->dibujar(NULL);

	Timer timer;

	bool listo = false;
	SDL_Event event;

	while(!listo) {

		timer.iniciar();
		while(SDL_PollEvent(&event)) {

			this->manejarEventos(&event);

			if( (event.type == SDL_QUIT)
				|| (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) ){
                listo = true;
            }
		}

		// dibuja solo si hubo cambios en los elementos
		this->dibujarSobreSup(this->pantalla);

		// dormir el tiempo que falta para cumplir con la tasa de cuadros por segundo
		int msPorFrame = (int)(1000 / FRAMES_PER_SECOND);
		if(timer.getMs() < msPorFrame) {
            SDL_Delay( msPorFrame - timer.getMs() );
        }
	}

}

void Ventana::manejarEventos(SDL_Event* event){

	list<Boton*> botones = this->getPanelComando()->getBotones();

	switch (event->type){	

		case (SDL_MOUSEMOTION):
			for (list<Boton*>::iterator it = botones.begin(); it != botones.end(); it++) {
				this->hayCambios = this->hayCambios || (*it)->checkOver(this->pantalla);
			}

			/*
			this->hayCambios = this->hayCambios || this->panelComando->getBotonDejarMesa()->checkOver(this->pantalla);
			this->hayCambios = this->hayCambios || this->panelComando->getBotonIgualar()->checkOver(this->pantalla);
			this->hayCambios = this->hayCambios || this->panelComando->getBotonNoIr()->checkOver(this->pantalla);
			this->hayCambios = this->hayCambios || this->panelComando->getBotonSubir()->checkOver(this->pantalla);
			*/
			this->panelComando->getTextBox()->checkOver(this->pantalla);
			break;

		case (SDL_MOUSEBUTTONDOWN):

			for (list<Boton*>::iterator it = botones.begin(); it != botones.end(); it++) {
				if ((*it)->checkClick(this->pantalla)) {

					this->hayCambios = true;

					// TODO: VER SI ESTO NO DEBERIA LANZARSE EN OTRO HILO 
					// CONSIDERAR SINCRONIZACION DE VENTANA
					FabricaOperacionesCliente fab;
					OperacionUICliente* operacion = fab.newOperacion((*it)->getIdOperacion());
					operacion->ejecutar(this);
				}
			}


			/*
			if(this->panelComando->getBotonDejarMesa()->checkClick(this->pantalla))
			{
				this->hayCambios = true;
				//accion a realizar
			}
			else if(this->panelComando->getBotonIgualar()->checkClick(this->pantalla))
			{
				this->hayCambios = true;
				//accion a realizar
			}
			else if(this->panelComando->getBotonNoIr()->checkClick(this->pantalla))
			{
				this->hayCambios = true;
				//accion a realizar
			}				
			else if(this->panelComando->getBotonSubir()->checkClick(this->pantalla))
			{
				this->hayCambios = true;
				//accion a realizar
			}
			*/
			break;		

		case (SDL_MOUSEBUTTONUP):
			for (list<Boton*>::iterator it = botones.begin(); it != botones.end(); it++) {
				this->hayCambios = this->hayCambios || (*it)->checkOver(this->pantalla);
			}
			/*
			this->hayCambios = this->hayCambios || this->panelComando->getBotonDejarMesa()->checkOver(this->pantalla);
			this->hayCambios = this->hayCambios || this->panelComando->getBotonIgualar()->checkOver(this->pantalla);
			this->hayCambios = this->hayCambios || this->panelComando->getBotonNoIr()->checkOver(this->pantalla);
			this->hayCambios = this->hayCambios || this->panelComando->getBotonSubir()->checkOver(this->pantalla);
			*/
			break;		
		}
}

void Ventana::dibujarSobreSup(SDL_Surface* superficie){

	if (this->hayCambios) {

		for (list<ElementoGrafico*>::iterator it = this->elementos.begin();
			it != this->elementos.end(); it++) {

				(*it)->dibujar(this->pantalla);
		}

		//se genera el panel de comando
		if (this->panelComando != NULL){
			panelComando->dibujar(this->pantalla);
		}

		//refresca la pantalla
		this->refrescar(this->pantalla);

		this->hayCambios = false;
	}
}

void Ventana::refrescar(SDL_Surface* superficie)
{
	if(SDL_Flip(superficie) == -1) { 
		throw UIException("Error al redibujar la pantalla completa.","E");
	} 
}

Panel* Ventana::getPanelComando(){
	return this->panelComando;
}

void Ventana::setPanelComando(Panel* panel){
	if (this->panelComando != NULL) {
		delete (this->panelComando);
	}
	this->panelComando = panel;
	this->hayCambios = true;
}

// metodos vacios, pensados para ser redefinidos
void Ventana::bloquear(){ }
void Ventana::desbloquear(){ }


ElementoGrafico* Ventana::getElementoPorId(string id){

	list<ElementoGrafico*>::iterator it = this->elementos.begin();
	ElementoGrafico* resultado = NULL;
	while(it != this->elementos.end() && resultado == NULL) {

		if( MensajesUtil::sonIguales((*it)->getId(), id) ){
			resultado = (*it);
		}

		it++;
	}

	return resultado;
}

void Ventana::borrarElementoPorId(string id){

	list<ElementoGrafico*>::iterator it = this->elementos.begin();
	bool encontrado = false;

	while(it != this->elementos.end() && !encontrado) {

		if( MensajesUtil::sonIguales((*it)->getId(), id) ){
			this->elementos.erase(it);
			encontrado = true;
		}

		it++;
	}

	if(encontrado){
		this->hayCambios = true;
	}
}


/* Metodos de ElementoGrafico */
SDL_Surface* Ventana::getSuperficie() {
	return this->superficie;
}

SDL_Rect* Ventana::getOffsetRect() {
	this->offset->x = this->getPosX();
	this->offset->y = this->getPosY();

	return this->offset;
}

SDL_Rect* Ventana::getContornoRect() {
	this->contorno->x = 0;
	this->contorno->y = 0;
	this->contorno->w = this->getAncho();
	this->contorno->h = this->getAlto();

	return this->contorno;
}

void Ventana::dibujar(SDL_Surface* superficie){

	if (this->hayCambios) {
		if (superficie != NULL) {
			this->dibujarSobreSup(superficie);

		} else {
			this->dibujarSobreSup(this->superficie);
		}
		this->hayCambios = false;
	}
}

int Ventana::getPosX() {
	return this->posX;
}
void Ventana::setPosX(int posX) {
	this->posX = posX;
	this->hayCambios = true;
}
int Ventana::getPosY() {
	return this->posY;
}
void Ventana::setPosY(int posY) {
	this->posY = posY;
	this->hayCambios = true;
}
int Ventana::getAncho() {
	return this->ancho;
}
void Ventana::setAncho(int ancho) {
	this->ancho = ancho;
	this->hayCambios = true;
}
int Ventana::getAlto() {
	return this->alto;
}
void Ventana::setAlto(int alto) {
	this->alto = alto;
	this->hayCambios = true;
}

void Ventana::setHayCambios(bool hayCambios){
	this->hayCambios = hayCambios;
}

string Ventana::getId(){
	return this->id;
}

void Ventana::setId(string id){
	this->id = id;
	this->hayCambios = true;
}

bool Ventana::equals(Ventana* otro){
	return (otro != NULL && MensajesUtil::sonIguales(this->getId(), otro->getId()));
}

int Ventana::getPosicion() {
	return this->posicion;
}

void Ventana::setPosicion(int posicion) {
	this->posicion = posicion;
	this->hayCambios = true;
}
/* Fin metodos ElementoGrafico */
