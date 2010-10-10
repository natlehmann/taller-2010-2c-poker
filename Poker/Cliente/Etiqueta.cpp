#include "Etiqueta.h"
#include "RecursosAplicacion.h"

Etiqueta::Etiqueta(void) {
	this->fondo = new Color(
		RecursosAplicacion::getClienteConfigProperties()->get(
		"cliente.tema.default.etiquetas.fondo"));
}

Etiqueta::Etiqueta(string mensaje){
	this->fondo = new Color(
		RecursosAplicacion::getClienteConfigProperties()->get(
		"cliente.tema.default.etiquetas.fondo"));
	this->mensaje = mensaje;
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

	//SDL_FillRect(superficie, offset, this->fondo->toUint32(superficie));

	string color = RecursosAplicacion::getClienteConfigProperties()->get("cliente.tema.default.etiquetas.fuente.color");
	
	int tamanio = UtilTiposDatos::getEntero(RecursosAplicacion::getClienteConfigProperties()->get("cliente.tema.default.etiquetas.fuente.tamanio"));
	
	string estilo = RecursosAplicacion::getClienteConfigProperties()->get("cliente.configuracion.fuentes") +
					RecursosAplicacion::getClienteConfigProperties()->get("cliente.tema.default.etiquetas.fuente.estilo") + ".ttf";
	
	Fuente* fuente = new Fuente(color, tamanio, estilo);
		
	SDL_Surface* superficieTexto = fuente->obtenerSuperficieTexto(this->mensaje, this->fondo);

	SDL_BlitSurface(superficieTexto, NULL, superficie, offset);

	SDL_FreeSurface(superficieTexto);
	delete (fuente);
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
