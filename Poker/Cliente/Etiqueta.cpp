#include "Etiqueta.h"
#include "RecursosAplicacion.h"
#include "MensajesUtil.h"
#include "ServiciosGraficos.h"

Etiqueta::Etiqueta(void) {
	this->fondo = new Color(
		RecursosAplicacion::getClienteConfigProperties()->get(
		"cliente.tema.default.etiquetas.fondo"));
	this->alineacionHorizontal = ALINEACION_HORIZ_IZQUIERDA;
	this->alineacionVertical = ALINEACION_VERT_CENTRO;
}

Etiqueta::Etiqueta(string mensaje){
	this->fondo = new Color(
		RecursosAplicacion::getClienteConfigProperties()->get(
		"cliente.tema.default.etiquetas.fondo"));
	this->mensaje = mensaje;
	this->alineacionHorizontal = ALINEACION_HORIZ_IZQUIERDA;
	this->alineacionVertical = ALINEACION_VERT_CENTRO;
}

Etiqueta::~Etiqueta(void) {
	if (this->fondo != NULL) {
		delete(this->fondo);
	}
}

void Etiqueta::dibujarSobreSup(SDL_Surface* superficie){ 

	SDL_Rect* offset = this->getOffsetRect();
	offset->w = this->getAncho();
	offset->h = this->getAlto();

	//if (this->borde != NULL) {
	//	SDL_FillRect(superficie, offset, this->borde->toUint32(superficie));
	//}
	if (this->fondo != NULL) {
		SDL_FillRect(superficie, offset, this->fondo->toUint32(superficie));
	}

	string color = RecursosAplicacion::getClienteConfigProperties()->get(
		"cliente.tema.default.etiquetas.fuente.color");
	
	int anchoPantalla = ServiciosGraficos::getAnchoVentana();

	int tamanioMax = UtilTiposDatos::getEntero(RecursosAplicacion::getClienteConfigProperties()->get(
		"cliente.tema.default.etiquetas.fuente.tamanio.maximo"));

	int tamanio = tamanioMax;
	if (anchoPantalla < MAXIMO_ANCHO_PANTALLA_PROP_TXT) {
		tamanio = (int)(anchoPantalla * tamanioMax / MAXIMO_ANCHO_PANTALLA_PROP_TXT);
	}

	
	string estilo = RecursosAplicacion::getClienteConfigProperties()->get("cliente.configuracion.fuentes") +
					RecursosAplicacion::getClienteConfigProperties()->get("cliente.tema.default.etiquetas.fuente.estilo") + ".ttf";
	
	Fuente* fuente = new Fuente(color, tamanio, estilo);
		
	SDL_Surface* superficieTexto = fuente->obtenerSuperficieTexto(this->mensaje, NULL);

	this->ajustarOffset(offset, superficieTexto);

	SDL_BlitSurface(superficieTexto, NULL, superficie, offset);

	SDL_FreeSurface(superficieTexto);
	delete (fuente);
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
	this->mensaje = mensaje;
}

string Etiqueta::getMensaje() {
	return this->mensaje;
}

void Etiqueta::setFondo(Color* color){
	if (this->fondo != NULL) {
		delete(this->fondo);
	}
	this->fondo = color;
}

Color* Etiqueta::getFondo() {
	return this->fondo;
}

void Etiqueta::setAlineacionHorizontal(int alineacion) {
	this->alineacionHorizontal = alineacion;
}

int Etiqueta::getAlineacionHorizontal(){
	return this->alineacionHorizontal;
}

void Etiqueta::setAlineacionVertical(int alineacion){
	this->alineacionVertical = alineacion;
}

int Etiqueta::getAlineacionVertical(){
	return this->alineacionVertical;
}
