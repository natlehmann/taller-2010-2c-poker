#include "Etiqueta.h"
#include "RecursosCliente.h"
#include "MensajesUtil.h"
#include "ServiciosGraficos.h"
#include "Ventana.h"

Etiqueta::Etiqueta(void) {
	this->fondo = new Color(
		RecursosCliente::getConfig()->get(
		"cliente.tema.default.etiquetas.fondo"));
	this->alineacionHorizontal = ALINEACION_HORIZ_IZQUIERDA;
	this->alineacionVertical = ALINEACION_VERT_CENTRO;
	this->borde = NULL;

	this->setearFuente();
}

Etiqueta::Etiqueta(string mensaje){
	this->fondo = new Color(
		RecursosCliente::getConfig()->get(
		"cliente.tema.default.etiquetas.fondo"));
	this->mensaje = mensaje;
	this->alineacionHorizontal = ALINEACION_HORIZ_IZQUIERDA;
	this->alineacionVertical = ALINEACION_VERT_CENTRO;
	this->borde = NULL;

	this->setearFuente();
}

Etiqueta::~Etiqueta(void) {
	if (this->fondo != NULL) {
		delete(this->fondo);
		this->fondo = NULL;
	}
	if (this->borde != NULL) {
		delete(this->borde);
		this->borde = NULL;
	}
	if (this->fuente != NULL) {
		delete (this->fuente);
		this->fuente = NULL;
	}
}

void Etiqueta::setearFuente() {

	string color = RecursosCliente::getConfig()->get(
		"cliente.tema.default.etiquetas.fuente.color");
	
	int anchoPantalla = ServiciosGraficos::getAnchoVentana();

	int tamanioMax = UtilTiposDatos::getEntero(RecursosCliente::getConfig()->get(
		"cliente.tema.default.etiquetas.fuente.tamanio.maximo"));

	int tamanio = tamanioMax;
	if (anchoPantalla < MAXIMO_ANCHO_PANTALLA_PROP_TXT) {
		tamanio = (int)(anchoPantalla * tamanioMax / MAXIMO_ANCHO_PANTALLA_PROP_TXT);
	}
	
	string estilo = RecursosCliente::getConfig()->get("cliente.configuracion.fuentes") +
					RecursosCliente::getConfig()->get("cliente.tema.default.etiquetas.fuente.estilo") + ".ttf";
	
	this->fuente = new Fuente(color, tamanio, estilo);
}

void Etiqueta::dibujarSobreSup(SDL_Surface* superficie){ 

	//this->setearFuente();
	SDL_Rect* offset = this->getContornoConOffset();

	if (this->fondo != NULL) {
		SDL_FillRect(superficie, offset, this->fondo->toUint32(superficie));
	
	} else {
		this->getVentana()->borrarElemento(this);
	}

	if (this->borde != NULL) {
		ServiciosGraficos::dibujarContorno(superficie, offset, this->borde);
	}
	
		
	SDL_Surface* superficieTexto = this->fuente->obtenerSuperficieTexto(this->mensaje, NULL);

	this->ajustarOffset(offset, superficieTexto);

	SDL_BlitSurface(superficieTexto, NULL, superficie, offset);

	SDL_FreeSurface(superficieTexto);

}


void Etiqueta::ajustarOffset(SDL_Rect* offset, SDL_Surface* superficie) {

	switch(this->alineacionHorizontal) {

		case ALINEACION_HORIZ_DERECHA:
			offset->x = offset->x + offset->w - superficie->w;
			break;

		case ALINEACION_HORIZ_CENTRO:
			offset->x = (int)(offset->x + (offset->w - superficie->w) / 2);
			break;

		// en caso de alineacion izquierda, no cambia nada
	}

	switch (this->alineacionVertical) {

		case ALINEACION_VERT_ABAJO:
			offset->y = offset->y + offset->h - superficie->h;
			break;

		case ALINEACION_VERT_CENTRO:
			offset->y = (int)(offset->y + (offset->h - superficie->h) / 2);
			break;

		// en caso de alineacion arriba, no cambia nada
	}
}

void Etiqueta::setMensaje(string mensaje) {
	if (!MensajesUtil::sonIguales(this->mensaje, mensaje)) {
		this->mensaje = mensaje;
		this->hayCambios = true;
	}
}

string Etiqueta::getMensaje() {
	return this->mensaje;
}

void Etiqueta::setFondo(Color* color){
	if (this->fondo != NULL) {
		delete(this->fondo);
	}
	//if (color != NULL)
	//	this->fondo = new Color(color->getRed(), color->getGreen(), color->getBlue());
	//else
	//	this->fondo = color;
	this->fondo = color;
	this->hayCambios = true;
}

Color* Etiqueta::getFondo() {
	return this->fondo;
}

void Etiqueta::setFuente(Fuente* fuente){
	if (this->fuente != NULL) {
		delete(this->fuente);
	}
	this->fuente = fuente;
	this->hayCambios = true;
}

Fuente* Etiqueta::getFuente() {
	return this->fuente;
}

void Etiqueta::setBorde(Color* color){
	if (this->borde != NULL) {
		delete (this->borde);
	}
	this->borde = color;
	this->hayCambios = true;
}
Color* Etiqueta::getBorde(){
	return this->borde;
}

void Etiqueta::setAlineacionHorizontal(int alineacion) {
	this->alineacionHorizontal = alineacion;
	this->hayCambios = true;
}

int Etiqueta::getAlineacionHorizontal(){
	return this->alineacionHorizontal;
}

void Etiqueta::setAlineacionVertical(int alineacion){
	this->alineacionVertical = alineacion;
	this->hayCambios = true;
}

int Etiqueta::getAlineacionVertical(){
	return this->alineacionVertical;
}
