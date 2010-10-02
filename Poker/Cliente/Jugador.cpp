#include "Jugador.h"
#include "ServiciosGraficos.h"
#include "UIException.h"
#include "MensajesUtil.h"
#include "Color.h"
#include "ImagenRecortada.h"

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

void Jugador::dibujarSobreSup(SDL_Surface* superficie){

	if (this->posicion < 1) {
		throw UIException("No se puede dibujar al jugador porque no se ha seteado su posicion.","E");
	}

	// TODO: Ver SI HABILITAMOS UNA IMAGEN DEFAULT EN CASO DE NO TENER NINGUNA
	if (this->imagen != NULL) {

		// se procesa la foto del jugador en una superficie
		SDL_Surface* supImagen = ServiciosGraficos::crearSuperficie(
			this->imagen->getAncho(), this->imagen->getAlto());
		this->imagen->dibujarSobreSup(supImagen, this->imagen->getContornoRect());

		// se crea una superficie de igual tamaño y se pinta como la mascara
		ImagenRecortada* supCirculo = new ImagenRecortada(
			this->imagen->getAncho(), this->imagen->getAlto());

		// se dibuja el circulo sobre esa superficie
		SDL_Rect* offset = this->imagen->getContornoRect();	

		Color colorCirculo(255,0,0);		// TODO: DEFINIR COLOR
		ServiciosGraficos::dibujarElipse(
			supCirculo->getSuperficie(), offset, &colorCirculo); 

		// se funde la imagen de la foto y la del circulo
		ServiciosGraficos::copiarDentro(supImagen, supCirculo->getSuperficie(), &colorCirculo);


		// se dibuja el circulo con la foto dentro sobre la superficie recibida
		supCirculo->setPosX(this->imagen->getPosX());
		supCirculo->setPosY(this->imagen->getPosY());
		supCirculo->dibujar(superficie);

		delete(supCirculo);
		SDL_FreeSurface(supImagen);
		delete(supImagen);
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
			this->posX = ServiciosGraficos::getBordeIzquierdo() + ServiciosGraficos::getTamanioCeldaHoriz();
			this->posY = ServiciosGraficos::getBordeSuperior();
			this->setearDisposicionAIzq();
			break;

		case 2:
			this->posX = ServiciosGraficos::getAnchoVentana() - ServiciosGraficos::getBordeDerecho()
							- ServiciosGraficos::getTamanioCeldaHoriz() * 2;
			this->posY = ServiciosGraficos::getBordeSuperior();
			this->setearDisposicionADer();
			break;

		case 3:
			this->posX = ServiciosGraficos::getBordeIzquierdo();
			this->posY = ServiciosGraficos::getTamanioCeldaVert() + ServiciosGraficos::getBordeSuperior();
			this->setearDisposicionAIzq();
			break;

		case 4:
			this->posX = ServiciosGraficos::getAnchoVentana() - ServiciosGraficos::getBordeDerecho()
							- ServiciosGraficos::getTamanioCeldaHoriz();
			this->posY = ServiciosGraficos::getTamanioCeldaVert() + ServiciosGraficos::getBordeSuperior();
			this->setearDisposicionADer();
			break;

		case 5:
			this->posX = ServiciosGraficos::getTamanioCeldaHoriz() + ServiciosGraficos::getBordeIzquierdo();
			this->posY =ServiciosGraficos::getAltoVentana() - ServiciosGraficos::getBordeInferior()
							- ServiciosGraficos::getTamanioCeldaVert();
			this->setearDisposicionAIzq();
			break;

		case 6:
			this->posX = ServiciosGraficos::getAnchoVentana() - ServiciosGraficos::getBordeDerecho()
							- ServiciosGraficos::getTamanioCeldaHoriz() * 2;
			this->posY = ServiciosGraficos::getAltoVentana() - ServiciosGraficos::getBordeInferior()
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
	this->imagen->setPosX(this->getPosX());
	this->imagen->setPosY(this->getPosY());

	// TODO: HABILITAR ESTO, REVISAR SIGNOS Y HACER QUE TODOS LOS VALORES SEAN RELATIVOS A LA VENTANA TOTAL

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
	this->imagen->setPosX(this->getPosX() + this->getAncho() - rectFoto->w);
	this->imagen->setPosY(this->getPosY());

	// TODO: HABILITAR ESTO, REVISAR SIGNOS Y HACER QUE TODOS LOS VALORES SEAN RELATIVOS A LA VENTANA TOTAL

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

	return this->imagen->getContornoRect();
}

Imagen* Jugador::getImagen() {
	return this->imagen;
}

void Jugador::setImagen(Imagen* imagen) {
	this->imagen = imagen;

	// TODO: VER SI ACA SE CARGA LA IMAGEN
	
}
