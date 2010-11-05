#include "VentanaImpl.h"
#include "RecursosCliente.h"
#include "MensajesUtil.h"
#include "DatosInvalidosException.h"
#include "UtilTiposDatos.h"
#include "UIException.h"
#include "Timer.h"
#include "ComponentePanel.h"
#include "FabricaOperacionesCliente.h"
#include "ServiciosGraficos.h"
#include <typeinfo.h>
#include <cstdlib>

VentanaImpl::VentanaImpl(void) {

	this->eventLock = SDL_CreateMutex();
	if (this->eventLock == NULL){
		RecursosCliente::getLog()->escribir("No se puede instanciar el mutex de la ventana.");
		exit(1);
	}

	this->eventWait = SDL_CreateCond();
	if (this->eventWait == NULL){
		RecursosCliente::getLog()->escribir("No se puede instanciar la variable condicional de la ventana.");
		exit(1);
	}

	this->contornoConOffset = new SDL_Rect();

	this->posX = 0;
	this->posY = 0;
	this->offset = new SDL_Rect();
	this->contorno = new SDL_Rect();
	this->hayCambios = true;
	this->id = "";
	this->posicion = -1;

	string configPantalla = RecursosCliente::getConfig()->get(
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

	SDL_WM_SetCaption(RecursosCliente::getConfig()->get(
		"cliente.configuracion.mensaje").c_str(), NULL); 

	this->panelComando = NULL;
	this->mesa = NULL;
	this->mensaje = NULL;
}

VentanaImpl::~VentanaImpl(void)
{
	/*
	if (this->panelComando != NULL) {
		delete(this->panelComando);
	}
	*/

	for (list<ElementoGrafico*>::iterator it = this->elementos.begin();
		it != this->elementos.end(); it++) {
			delete(*it);
	}
	this->elementos.clear();

	delete (this->offset);
	delete (this->contorno);

	SDL_DestroyMutex(this->eventLock);
	eventLock = NULL;

	SDL_DestroyCond(this->eventWait);
	eventWait = NULL;
}

void VentanaImpl::agregarElementoGrafico(ElementoGrafico* elemento) {
	this->elementos.push_back(elemento);

	if (MensajesUtil::sonIguales(typeid(*elemento).name(), "class Mesa")){
		this->mesa = (Mesa*)elemento;
	}

	if (MensajesUtil::sonIguales(typeid(*elemento).name(), "class Mensaje")){
		this->mensaje = (Mensaje*)elemento;
	}

	this->hayCambios = true;
	elemento->setVentana(this);
}

void VentanaImpl::limpiar() {

	for (list<ElementoGrafico*>::iterator it = this->elementos.begin();
		it != this->elementos.end(); it++) {
			delete(*it);
	}
	this->elementos.clear();

	delete(this->panelComando);
	this->panelComando = NULL;
}


void VentanaImpl::borrarElemento(ElementoGrafico* elemento){
	if (this->mesa != NULL && this->mesa->getFondo() != NULL) {

		this->mesa->getFondo()->generarSuperficie();

		//si algo salio mal
		if (this->mesa->getFondo()->getSuperficie() == NULL) {
			throw UIException(
				"No se pudo borrar la region de un elemento porque no se pudo cargar la imagen de la mesa.", "E");
		}

		SDL_Rect* region = elemento->getContornoConOffset();

		SDL_BlitSurface(this->mesa->getFondo()->getSuperficie(), region, 
			this->pantalla, region); 
	}
}


void VentanaImpl::iniciar() {

	// se dibuja inicialmente
	/*
	this->bloquear();
	this->dibujar(NULL);
	this->desbloquear();
	*/
//this->dibujar(NULL);
	Timer timer;

	bool listo = false;
	SDL_Event event;

	while(!listo) {

		timer.iniciar();
		/*
		SDL_WaitEvent
			SDL_UserEvent
			SDL_UnlockMutex
		while(SDL_PollEvent(&event)) {
		*/

		//while(this->WaitEvent(&event) && !listo) {
		while(this->PollEvent(&event) && !listo) {

			this->manejarEventos(&event);

			if( (event.type == SDL_QUIT)
				|| (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) ){
                listo = true;
            }

		}

		

		
		// dormir el tiempo que falta para cumplir con la tasa de cuadros por segundo
		int msPorFrame = (int)(1000 / FRAMES_PER_SECOND);
		if(timer.getMs() < msPorFrame && !listo) {
            SDL_Delay( msPorFrame - timer.getMs() );
        }
		
	
	}

}

void VentanaImpl::manejarEventos(SDL_Event* event){

	if (this->getPanelComando() != NULL) {

		ComponentePanel** componentes = this->getPanelComando()->getComponentes();
		this->hayCambios = false;

		for (int i = 0; i < MAX_CANT_COMPONENTES; i++) {
			if (componentes[i] != NULL) {
				this->hayCambios = componentes[i]->checkWrite(this->pantalla, event, 1) || this->hayCambios;
			}
			if (this->hayCambios) {
				this->refrescar(this->pantalla);
				this->hayCambios = false;
			}
		}

		switch (event->type){	

			case (SDL_MOUSEMOTION):
				/*
				for (int i = 0; i < MAX_CANT_COMPONENTES; i++) {
					if (componentes[i] != NULL) {
						this->hayCambios = this->hayCambios || componentes[i]->checkOver(this->pantalla);
					}
				}
				*/
				break;

			case (SDL_MOUSEBUTTONDOWN):

				for (int i = 0; i < MAX_CANT_COMPONENTES; i++) {
					if (componentes[i] != NULL) {

						if (componentes[i]->checkClick(this->pantalla)) {

							this->hayCambios = true;
							componentes[i]->dibujarDown(this->pantalla);
							this->refrescar(this->pantalla);

							// TODO: VER SI ESTO NO DEBERIA LANZARSE EN OTRO HILO 
							FabricaOperacionesCliente fab;
							vector<string> parametros;
							if (!MensajesUtil::esVacio(componentes[i]->getIdComponentePanelRelacionado())) {
								parametros.push_back(componentes[i]->getIdComponentePanelRelacionado());
							}

							OperacionUICliente* operacion = fab.newOperacion(
									componentes[i]->getIdOperacion(), parametros);
							operacion->ejecutar(this);
							delete(operacion);

							componentes[i]->dibujarUp(this->pantalla);
							this->refrescar(this->pantalla);
						}
					}
				}
				break;		

			/*
			case (SDL_MOUSEBUTTONUP):
				this->hayCambios = false;
				for (int i = 0; i < MAX_CANT_COMPONENTES; i++) {
					if (componentes[i] != NULL) {
						this->hayCambios = componentes[i]->checkOver(this->pantalla) ||  this->hayCambios;
					}
				}
				if (this->hayCambios) {
					this->refrescar(this->pantalla);
					this->hayCambios = false;
				}
				break;	
			*/

		}
	}

}

void VentanaImpl::dibujarSobreSup(SDL_Surface* superficie){

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

void VentanaImpl::forzarRefresh(ElementoGrafico* elemento) {
	for (list<ElementoGrafico*>::iterator it = this->elementos.begin(); it != this->elementos.end(); it++) {
		if ((*it)->hayInterseccion(elemento)) {
			(*it)->setHayCambios(true);
		}
	}
	this->hayCambios = true;
}

void VentanaImpl::refrescar(SDL_Surface* superficie)
{
	if(SDL_Flip(superficie) == -1) { 
		throw UIException("Error al redibujar la pantalla completa.","E");
	} 
}

Panel* VentanaImpl::getPanelComando(){
	return this->panelComando;
}

void VentanaImpl::setPanelComando(Panel* panel){
	/*
	if (this->panelComando != NULL) {
		delete (this->panelComando);
	}
	*/
	this->panelComando = panel;
	this->hayCambios = true;
}


ElementoGrafico* VentanaImpl::getElementoPorId(string id){

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

void VentanaImpl::borrarElementoPorId(string id){

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
SDL_Surface* VentanaImpl::getSuperficie() {
	return this->pantalla;
}

SDL_Rect* VentanaImpl::getOffsetRect() {
	this->offset->x = this->getPosX();
	this->offset->y = this->getPosY();

	return this->offset;
}

SDL_Rect* VentanaImpl::getContornoRect() {
	this->contorno->x = 0;
	this->contorno->y = 0;
	this->contorno->w = this->getAncho();
	this->contorno->h = this->getAlto();

	return this->contorno;
}

void VentanaImpl::dibujar(SDL_Surface* superficie){

	if (this->hayCambios) {
		if (superficie != NULL) {
			this->dibujarSobreSup(superficie);

		} else {
			this->dibujarSobreSup(this->pantalla);
		}
		this->hayCambios = false;
	}
}

int VentanaImpl::getPosX() {
	return this->posX;
}
void VentanaImpl::setPosX(int posX) {
	this->posX = posX;
	this->hayCambios = true;
}
int VentanaImpl::getPosY() {
	return this->posY;
}
void VentanaImpl::setPosY(int posY) {
	this->posY = posY;
	this->hayCambios = true;
}
int VentanaImpl::getAncho() {
	return this->ancho;
}
void VentanaImpl::setAncho(int ancho) {
	this->ancho = ancho;
	this->hayCambios = true;
}
int VentanaImpl::getAlto() {
	return this->alto;
}
void VentanaImpl::setAlto(int alto) {
	this->alto = alto;
	this->hayCambios = true;
}

void VentanaImpl::setHayCambios(bool hayCambios){
	this->hayCambios = hayCambios;
}

string VentanaImpl::getId(){
	return this->id;
}

void VentanaImpl::setId(string id){
	this->id = id;
	this->hayCambios = true;
}

int VentanaImpl::getPosicion() {
	return this->posicion;
}

void VentanaImpl::setPosicion(int posicion) {
	this->posicion = posicion;
	this->hayCambios = true;
}
/* Fin metodos ElementoGrafico */


// Sincronizacion
int VentanaImpl::WaitEvent(SDL_Event *event)
{
  int val = 0;

  SDL_LockMutex(this->eventLock);
  while (0 >= (val = SDL_PollEvent(event)))
  {
    SDL_CondWait(this->eventWait, this->eventLock);
  }
  SDL_UnlockMutex(this->eventLock);
  SDL_CondSignal(this->eventWait);

  return val;
}

int VentanaImpl::PollEvent(SDL_Event *event)
{
  int val = 0;

  SDL_LockMutex(this->eventLock);
  val = SDL_PollEvent(event);
  SDL_UnlockMutex(this->eventLock);

  if (0 < val)
  {
    SDL_CondSignal(this->eventWait);
  }

  return val;
}

int VentanaImpl::PushEvent(SDL_Event *event)
{
  SDL_LockMutex(this->eventLock);
  while (-1 == SDL_PushEvent(event))
  {
    SDL_CondWait(this->eventWait, this->eventLock);
  }
  SDL_UnlockMutex(this->eventLock);
  SDL_CondSignal(this->eventWait);

  return 1;
}

SDL_Rect* VentanaImpl::getContornoConOffset() {
	this->contornoConOffset->x = this->getPosX();
	this->contornoConOffset->y = this->getPosY();
	this->contornoConOffset->w = this->getAncho();
	this->contornoConOffset->h = this->getAlto();

	return this->contornoConOffset;
}

void VentanaImpl::merge(SDL_Surface* superficie){

	SDL_BlitSurface(superficie, this->getContornoConOffset(), this->pantalla, this->getContornoConOffset());
	this->refrescar(this->pantalla);
}

void VentanaImpl::mostrarMensaje(string mensaje){
	if (this->mensaje != NULL) {
		this->mensaje->setTexto(mensaje);
		this->mensaje->setVisible(true);
	}
}