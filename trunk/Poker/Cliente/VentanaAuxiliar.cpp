#include "VentanaAuxiliar.h"
#include "RecursosCliente.h"
#include "MensajesUtil.h"
#include "DatosInvalidosException.h"
#include "UtilTiposDatos.h"
#include "UIException.h"
#include "Timer.h"
#include "ComponentePanel.h"
#include "FabricaOperacionesCliente.h"
#include <typeinfo.h>
#include <cstdlib>

VentanaAuxiliar::VentanaAuxiliar(void) {

	this->superficie = NULL;
	this->offset = new SDL_Rect();
	this->contorno = new SDL_Rect();
	this->hayCambios = true;
	this->id = "";
	this->posicion = -1;

	this->panelComando = NULL;
	this->mesa = NULL;
	this->mensaje = NULL;
}

VentanaAuxiliar::~VentanaAuxiliar(void)
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

void VentanaAuxiliar::agregarElementoGrafico(ElementoGrafico* elemento) {
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

void VentanaAuxiliar::limpiar() {

	for (list<ElementoGrafico*>::iterator it = this->elementos.begin();
		it != this->elementos.end(); it++) {
			delete(*it);
	}
	this->elementos.clear();

	delete(this->panelComando);
	this->panelComando = NULL;
}

void VentanaAuxiliar::limpiarFotosJugadores() {
	// limpieza de las imagenes de los jugadores, para que se refresquen la proxima vez que levante
	string path = RecursosCliente::getConfig()->get("cliente.configuracion.imagenes.path");
	for(set<string>::iterator it = this->nombresJugadores.begin(); it != this->nombresJugadores.end(); it++) {
		string instruccion = string("del ") + path + (*it) + ".bmp";
		system(instruccion.c_str());
	}
	this->nombresJugadores.clear();
}


void VentanaAuxiliar::borrarElemento(ElementoGrafico* elemento){
	if (this->mesa != NULL && this->mesa->getFondo() != NULL) {

		this->mesa->getFondo()->generarSuperficie();

		//si algo salio mal
		if (this->mesa->getFondo()->getSuperficie() == NULL) {
			throw UIException(
				"No se pudo borrar la region de un elemento porque no se pudo cargar la imagen de la mesa.", "E");
		}

		SDL_Rect* region = elemento->getContornoConOffset();

		SDL_BlitSurface(this->mesa->getFondo()->getSuperficie(), region, 
			this->superficie, region); 
	}
}


void VentanaAuxiliar::dibujarSobreSup(SDL_Surface* superficie){

	//if (this->hayCambios) {

		for (list<ElementoGrafico*>::iterator it = this->elementos.begin();
			it != this->elementos.end(); it++) {

				(*it)->dibujar(superficie);
		}

		//se fuerza el redibujo del panel de comando
		if (this->panelComando != NULL){
			this->panelComando->setHayCambios(true);
			this->panelComando->dibujar(superficie);
		}

	//	this->hayCambios = false;
	//}
}

void VentanaAuxiliar::forzarRefresh(ElementoGrafico* elemento) {
	for (list<ElementoGrafico*>::iterator it = this->elementos.begin(); it != this->elementos.end(); it++) {
		if ((*it)->hayInterseccion(elemento)) {
			(*it)->setHayCambios(true);
		}
	}
	this->hayCambios = true;
}


Panel* VentanaAuxiliar::getPanelComando(){
	return this->panelComando;
}

void VentanaAuxiliar::setPanelComando(Panel* panel){
	if (this->panelComando != NULL) {
		delete (this->panelComando);
	}
	this->panelComando = panel;
	this->hayCambios = true;
}


ElementoGrafico* VentanaAuxiliar::getElementoPorId(string id){

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

void VentanaAuxiliar::borrarElementoPorId(string id){

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
SDL_Surface* VentanaAuxiliar::getSuperficie() {
	return this->superficie;
}

SDL_Rect* VentanaAuxiliar::getOffsetRect() {
	this->offset->x = this->getPosX();
	this->offset->y = this->getPosY();

	return this->offset;
}

SDL_Rect* VentanaAuxiliar::getContornoRect() {
	this->contorno->x = 0;
	this->contorno->y = 0;
	this->contorno->w = this->getAncho();
	this->contorno->h = this->getAlto();

	return this->contorno;
}

void VentanaAuxiliar::dibujar(SDL_Surface* superficie){

	//if (this->hayCambios) {
		if (superficie != NULL) {
			this->dibujarSobreSup(superficie);

		} else {
			this->dibujarSobreSup(this->superficie);
		}
		this->hayCambios = false;
	//}
}

int VentanaAuxiliar::getPosX() {
	return this->posX;
}
void VentanaAuxiliar::setPosX(int posX) {
	this->posX = posX;
	this->hayCambios = true;
}
int VentanaAuxiliar::getPosY() {
	return this->posY;
}
void VentanaAuxiliar::setPosY(int posY) {
	this->posY = posY;
	this->hayCambios = true;
}
int VentanaAuxiliar::getAncho() {
	return this->ancho;
}
void VentanaAuxiliar::setAncho(int ancho) {
	this->ancho = ancho;
	this->hayCambios = true;
}
int VentanaAuxiliar::getAlto() {
	return this->alto;
}
void VentanaAuxiliar::setAlto(int alto) {
	this->alto = alto;
	this->hayCambios = true;
}

void VentanaAuxiliar::setHayCambios(bool hayCambios){
	this->hayCambios = hayCambios;
}

string VentanaAuxiliar::getId(){
	return this->id;
}

void VentanaAuxiliar::setId(string id){
	this->id = id;
	this->hayCambios = true;
}

int VentanaAuxiliar::getPosicion() {
	return this->posicion;
}

void VentanaAuxiliar::setPosicion(int posicion) {
	this->posicion = posicion;
	this->hayCambios = true;
}
/* Fin metodos ElementoGrafico */



void VentanaAuxiliar::setSuperficie(SDL_Surface* superficie){
	this->superficie = superficie;
}


void VentanaAuxiliar::iniciar(){
}

int VentanaAuxiliar::PushEvent(SDL_Event *event){
	return -1;
}

void VentanaAuxiliar::merge(SDL_Surface* superficie){
}

void VentanaAuxiliar::mostrarMensaje(string mensaje){
	if (this->mensaje != NULL) {
		this->mensaje->setTexto(mensaje);
		this->mensaje->setVisible(true);
	}
}

void VentanaAuxiliar::registrarNombreJugador(string nombre){
	this->nombresJugadores.insert(nombre);
}
