#include "Jugador.h"
#include "ServiciosGraficos.h"
#include "UIException.h"
#include "MensajesUtil.h"
#include "Color.h"
#include "ImagenRecortada.h"
#include "RecursosAplicacion.h"

Jugador::Jugador(void) {
	this->imagen = NULL;
	this->setAncho(ServiciosGraficos::getTamanioCeldaHoriz());
	this->setAlto(ServiciosGraficos::getTamanioCeldaVert());
	this->posicion = -1;
	this->carta1 = NULL;
	this->carta2 = NULL;
	this->etiquetaNombre = new Etiqueta();
	this->fichas = NULL;
}

Jugador::~Jugador(void) {
	if (this->imagen != NULL) {
		delete(this->imagen);
	}
	if (this->carta1 != NULL) {
		delete (this->carta1);
	}
	if (this->carta2 != NULL) {
		delete (this->carta2);
	}
	if (this->fichas != NULL) {
		delete (this->fichas);
	}
	if (this->etiquetaNombre != NULL) {
		delete (this->etiquetaNombre);
	}
}

void Jugador::dibujarSobreSup(SDL_Surface* superficie){

	if (this->posicion < 1) {
		throw UIException("No se puede dibujar al jugador porque no se ha seteado su posicion.","E");
	}

	// TODO: Ver SI HABILITAMOS UNA IMAGEN DEFAULT EN CASO DE NO TENER NINGUNA
	if (this->imagen != NULL) {
		this->dibujarJugador(superficie);
	}

	this->carta1->dibujar(superficie);
	this->carta2->dibujar(superficie);

	if (this->fichas != NULL) {
		this->fichas->dibujar(superficie);
	}

	this->etiquetaNombre->dibujar(superficie);

}

void Jugador::dibujarJugador(SDL_Surface* superficie) {

	// se procesa la foto del jugador en una superficie
	SDL_Surface* supImagen = ServiciosGraficos::crearSuperficie(
		this->imagen->getAncho(), this->imagen->getAlto());
	this->imagen->dibujarSobreSup(supImagen, this->imagen->getContornoRect());


	// se crea una superficie de igual tamaño y se pinta como la mascara
	ImagenRecortada* supCirculo = new ImagenRecortada(
		this->imagen->getAncho(), this->imagen->getAlto());

	// se dibuja el circulo sobre esa superficie
	SDL_Rect* offset = this->imagen->getContornoRect();

	Color* colorCirculo = new Color(RecursosAplicacion::getClienteConfigProperties()->get(
		"cliente.tema.default.jugador.color.borde"));
	ServiciosGraficos::dibujarElipse(
		supCirculo->getSuperficie(), offset, colorCirculo); 

	// se funde la imagen de la foto y la del circulo
	ServiciosGraficos::copiarDentro(supImagen, supCirculo->getSuperficie(), colorCirculo);


	// se dibuja el circulo con la foto dentro sobre la superficie recibida
	supCirculo->setPosX(this->imagen->getPosX());
	supCirculo->setPosY(this->imagen->getPosY());
	supCirculo->dibujar(superficie);

	// limpieza
	delete(colorCirculo);
	delete(supCirculo);
	SDL_FreeSurface(supImagen);
	delete(supImagen);

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
	this->etiquetaNombre->setMensaje(nombre);
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

	this->etiquetaNombre->setPosX(this->getPosX());
	this->etiquetaNombre->setPosY(this->getPosY() + rectFoto->h);
	this->etiquetaNombre->setAncho(rectFoto->w);
	if ((this->getAlto() - rectFoto->h) < ALTO_MAXIMO_ETIQ_NOMBRE) {
		this->etiquetaNombre->setAlto(this->getAlto() - rectFoto->h);

	} else {
		this->etiquetaNombre->setAlto(ALTO_MAXIMO_ETIQ_NOMBRE);
	}

	int anchoCarta = (int)((this->getAncho() - rectFoto->w - SEPARACION_ENTRE_CARTAS * 2) / 2);
	this->carta1->setPosX(this->getPosX() + rectFoto->w + SEPARACION_ENTRE_CARTAS);
	this->carta2->setPosX(this->getPosX() + this->getAncho() - anchoCarta);

	this->carta1->setPosY(this->getPosY());
	this->carta2->setPosY(this->getPosY());

	this->carta1->setAncho(anchoCarta);
	this->carta2->setAncho(anchoCarta);

	this->carta1->setAlto(rectFoto->h / 2);
	this->carta2->setAlto(rectFoto->h / 2);

	this->fichas->setPosX(this->getPosX() + rectFoto->w + SEPARACION_ENTRE_CARTAS);
	this->fichas->setPosY(this->getPosY() + rectFoto->h / 2 + SEPARACION_CARTAS_FICHAS);
	this->fichas->setAncho(this->getAncho() - rectFoto->w);
	this->fichas->setAlto(rectFoto->h / 2 - SEPARACION_CARTAS_FICHAS);
}

void Jugador::setearDisposicionADer(){
	SDL_Rect* rectFoto = this->calcularRectFoto();
	this->imagen->setPosX(this->getPosX() + this->getAncho() - rectFoto->w);
	this->imagen->setPosY(this->getPosY());

	this->etiquetaNombre->setPosX(this->getPosX() + this->getAncho() - rectFoto->w);
	this->etiquetaNombre->setPosY(this->getPosY() + rectFoto->h);
	this->etiquetaNombre->setAncho(rectFoto->w);
	if ((this->getAlto() - rectFoto->h) < ALTO_MAXIMO_ETIQ_NOMBRE) {
		this->etiquetaNombre->setAlto(this->getAlto() - rectFoto->h);

	} else {
		this->etiquetaNombre->setAlto(ALTO_MAXIMO_ETIQ_NOMBRE);
	}

	int anchoCarta = (int)((this->getAncho() - rectFoto->w - SEPARACION_ENTRE_CARTAS * 2) / 2);
	this->carta1->setPosX(this->getPosX());
	this->carta2->setPosX(this->getPosX() + anchoCarta + SEPARACION_ENTRE_CARTAS);

	this->carta1->setPosY(this->getPosY());
	this->carta2->setPosY(this->getPosY());

	this->carta1->setAncho(anchoCarta);
	this->carta2->setAncho(anchoCarta);

	this->carta1->setAlto(rectFoto->h / 2);
	this->carta2->setAlto(rectFoto->h / 2);

	this->fichas->setPosX(this->getPosX());
	this->fichas->setPosY(this->getPosY() + rectFoto->h / 2 + SEPARACION_CARTAS_FICHAS);
	this->fichas->setAncho(this->getAncho() - rectFoto->w);
	this->fichas->setAlto(rectFoto->h / 2 - SEPARACION_CARTAS_FICHAS);
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

void Jugador::setCarta1(Carta* carta){
	this->carta1 = carta;
}

void Jugador::setCarta2(Carta* carta){
	this->carta2 = carta;
}

Carta* Jugador::getCarta1() {
	return this->carta1;
}

Carta* Jugador::getCarta2() {
	return this->carta2;
}

void Jugador::setCarta(Carta* carta){
	if (this->carta1 == NULL) {
		this->setCarta1(carta);

	} else {
		if (this->carta2 == NULL) {
			this->setCarta2(carta);

		} else {
			throw UIException("Un jugador no puede tener mas de dos cartas.","V");
		}
	}
}

void Jugador::setFichas(string cantidad) {
	if (this->fichas == NULL) {
		this->fichas = new Fichas(cantidad);
	
	} else {
		this->fichas->setCantidad(cantidad);
	}
}

Fichas* Jugador::getFichas(){
	return this->fichas;
}