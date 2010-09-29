#include "Jugador.h"
#include "ServiciosGraficos.h"
#include "UIException.h"
#include "MensajesUtil.h"

Jugador::Jugador(void) {
	this->imagen = NULL;
	this->setAncho(ServiciosGraficos::getTamanioCeldaHoriz());
	this->setAlto(ServiciosGraficos::getTamanioCeldaVert());
	this->posicion = -1;
}

Jugador::~Jugador(void) {
	if (this->imagen != NULL) {
		delete(this->imagen);
	}
}

void Jugador::dibujar(){

	if (this->posicion < 1) {
		throw UIException("No se puede dibujar al jugador porque no se ha seteado su posicion.","E");
	}

	if (this->superficie != NULL) {
		SDL_FreeSurface(this->superficie);
		delete(this->superficie);
	}

	this->superficie = SDL_CreateRGBSurface (SDL_SWSURFACE, 
		this->getAncho(), this->getAlto(),
		ServiciosGraficos::getVideoInfo()->vfmt->BitsPerPixel, 
        ServiciosGraficos::getVideoInfo()->vfmt->Rmask, 
		ServiciosGraficos::getVideoInfo()->vfmt->Gmask,
        ServiciosGraficos::getVideoInfo()->vfmt->Bmask, 
		ServiciosGraficos::getVideoInfo()->vfmt->Amask);

	if (this->imagen != NULL) {
		this->imagen->dibujar();
		SDL_Rect* offset = this->imagen->getOffsetRect();
		ServiciosGraficos::dibujarElipse(this->getSuperficie(), offset, 255,0,0);  // TODO: DEFINIR COLOR
	}

	// TODO: FALTA DIBUJAR ETIQUETA, CARTAS Y FICHAS

}

int Jugador::getId() {
	return this->id;
}

void Jugador::setId(int id) {
	this->id = id;
}

string Jugador::getNombre() {
	return this->nombre;
}

void Jugador::setNombre(string nombre){
	this->nombre = nombre;
}

int Jugador::getPosicion() {
	return this->posicion;
}

void Jugador::setPosicion(int posicion) {
	this->posicion = posicion;

	switch(posicion) {
		case 1:
			this->posX = ServiciosGraficos::getTamanioCeldaHoriz();
			this->posY = 0;
			this->setearDisposicionAIzq();
			break;

		case 2:
			this->posX = ServiciosGraficos::getAnchoVentana() 
							- ServiciosGraficos::getTamanioCeldaHoriz() * 2;
			this->posY = 0;
			this->setearDisposicionADer();
			break;

		case 3:
			this->posX = 0;
			this->posY = ServiciosGraficos::getTamanioCeldaVert();
			this->setearDisposicionAIzq();
			break;

		case 4:
			this->posX = ServiciosGraficos::getAnchoVentana() 
							- ServiciosGraficos::getTamanioCeldaHoriz();
			this->posY = ServiciosGraficos::getTamanioCeldaVert();
			this->setearDisposicionADer();
			break;

		case 5:
			this->posX = ServiciosGraficos::getTamanioCeldaHoriz();
			this->posY = ServiciosGraficos::getAltoVentana() 
							- ServiciosGraficos::getTamanioCeldaVert();
			this->setearDisposicionAIzq();
			break;

		case 6:
			this->posX = ServiciosGraficos::getAnchoVentana() 
							- ServiciosGraficos::getTamanioCeldaHoriz() * 2;
			this->posY = ServiciosGraficos::getAltoVentana() 
							- ServiciosGraficos::getTamanioCeldaVert();
			this->setearDisposicionADer();
			break;

		default:
			throw UIException("La posicion del jugador " 
				+ MensajesUtil::intToString(posicion) + " no es valida.", "V");
	}
}

void Jugador::setearDisposicionAIzq(){
	SDL_Rect* rectFoto = this->calcularRectFoto();
	this->imagen->setPosX(0);
	this->imagen->setPosY(0);

	// TODO: HABILITAR ESTO

	//this->etiqueta->setPosX(0);
	//this->etiqueta->setPosY(rectFoto->h);
	//this->etiqueta->setAncho(rectFoto->w);
	//this->etiqueta->setAlto(this->getAlto() - rectFoto->h);

	//this->cartas->setPosX(rectFoto->w);
	//this->cartas->setPosY(0);
	//this->cartas->setAncho(this->getAncho() - rectFoto->w);
	//this->cartas->setAlto(rectFoto->h / 2);

	//this->fichas->setPosX(rectFoto->w);
	//this->fichas->setPosY(rectFoto->h / 2);
	//this->fichas->setAncho(this->getAncho() - rectFoto->w);
	//this->fichas->setAlto(rectFoto->h / 2);
}

void Jugador::setearDisposicionADer(){
	SDL_Rect* rectFoto = this->calcularRectFoto();
	this->imagen->setPosX(this->getAncho() - rectFoto->w);
	this->imagen->setPosY(0);

	// TODO: HABILITAR ESTO

	//this->etiqueta->setPosX(this->getAncho() - rectFoto->w);
	//this->etiqueta->setPosY(rectFoto->h);
	//this->etiqueta->setAncho(rectFoto->w);
	//this->etiqueta->setAlto(this->getAlto() - rectFoto->h);

	//this->cartas->setPosX(0);
	//this->cartas->setPosY(0);
	//this->cartas->setAncho(this->getAncho() - rectFoto->w);
	//this->cartas->setAlto(rectFoto->h / 2);

	//this->fichas->setPosX(0);
	//this->fichas->setPosY(rectFoto->h / 2);
	//this->fichas->setAncho(this->getAncho() - rectFoto->w);
	//this->fichas->setAlto(rectFoto->h / 2);
}

SDL_Rect* Jugador::calcularRectFoto(){

	int maxAltoFoto = this->getAlto() - (int)(this->getAlto() * ALTO_MIN_ETIQUETA);
	int maxAnchoFoto = this->getAncho() - (int)(this->getAncho() * ANCHO_MIN_CARTAS);

	int menor = maxAltoFoto;
	if (maxAnchoFoto < menor) {
		menor = maxAnchoFoto;
	}

	this->imagen->setAlto(menor);
	this->imagen->setAncho(menor);

	return this->imagen->getOffsetRect();
}

Imagen* Jugador::getImagen() {
	return this->imagen;
}

void Jugador::setImagen(Imagen* imagen) {
	this->imagen = imagen;

	// TODO: VER SI ACA SE CARGA LA IMAGEN
	
}
