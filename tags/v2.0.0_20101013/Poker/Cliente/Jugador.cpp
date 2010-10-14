#include "Jugador.h"
#include "ServiciosGraficos.h"
#include "UIException.h"
#include "MensajesUtil.h"
#include "Color.h"
#include "ImagenRecortada.h"
#include "RecursosAplicacion.h"
#include "UtilTiposDatos.h"

Jugador::Jugador(void) {
	this->imagen = NULL;
	this->setAncho(ServiciosGraficos::getTamanioCeldaHoriz());
	this->setAlto(ServiciosGraficos::getTamanioCeldaVert());
	this->posicion = -1;
	this->carta1 = NULL;
	this->carta2 = NULL;
	this->etiquetaNombre = NULL;
	this->etiquetaFichas = NULL;
	this->apuesta = NULL;
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
	if (this->apuesta != NULL) {
		delete (this->apuesta);
	}
	if (this->etiquetaNombre != NULL) {
		delete (this->etiquetaNombre);
	}
	if (this->etiquetaFichas != NULL) {
		delete (this->etiquetaFichas);
	}
}

void Jugador::dibujarSobreSup(SDL_Surface* superficie){

	if (this->posicion < 1) {
		throw UIException("No se puede dibujar al jugador porque no se ha seteado su posicion.","E");
	}

	this->calcularCoordenadas();

	if (this->imagen != NULL) {
		this->dibujarJugador(superficie);
	}

	if (this->carta1 != NULL) {
		this->carta1->dibujar(superficie);
	}

	if (this->carta2 != NULL) {
		this->carta2->dibujar(superficie);
	}

	if (this->apuesta != NULL) {
		this->apuesta->dibujar(superficie);
	}

	if (this->etiquetaNombre != NULL) {
		this->etiquetaNombre->dibujar(superficie);
	}

	if (this->etiquetaFichas != NULL) {
		this->etiquetaFichas->dibujar(superficie);
	}

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
	//delete(supImagen);

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
	if (this->etiquetaNombre == NULL) {
		this->etiquetaNombre = new Etiqueta();
		this->etiquetaNombre->setAlineacionHorizontal(ALINEACION_HORIZ_CENTRO);
		this->etiquetaNombre->setAlineacionVertical(ALINEACION_VERT_CENTRO);
		this->etiquetaNombre->setBorde(new Color(
			RecursosAplicacion::getClienteConfigProperties()->get("cliente.tema.default.etiquetas.borde")));
	}
	this->etiquetaNombre->setMensaje(nombre);
}

int Jugador::getPosicion() {
	return this->posicion;
}

void Jugador::setPosicion(int posicion) {
	this->posicion = posicion;
}


void Jugador::calcularCoordenadas() {

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

	if (this->imagen == NULL) {
		this->imagen = this->getImagenDefault();
	}

	SDL_Rect* rectFoto = this->calcularRectFoto();
	this->imagen->setPosX(this->getPosX());
	this->imagen->setPosY(this->getPosY());

	if (this->etiquetaNombre != NULL) {
		this->etiquetaNombre->setPosX(this->getPosX());
		this->etiquetaNombre->setPosY(this->getPosY() + rectFoto->h);
		this->etiquetaNombre->setAncho(rectFoto->w);
		if (ServiciosGraficos::getAltoVentana() < MAXIMO_ALTO_PANTALLA_PROP_TXT) {
			this->etiquetaNombre->setAlto((int)(ServiciosGraficos::getAltoVentana() 
				* ALTO_MAXIMO_ETIQUETA / MAXIMO_ALTO_PANTALLA_PROP_TXT));

		} else {
			this->etiquetaNombre->setAlto(ALTO_MAXIMO_ETIQUETA);
		}
	}

	if (this->etiquetaFichas != NULL) {
		this->etiquetaFichas->setPosX(this->getPosX());
		this->etiquetaFichas->setPosY(this->getPosY() + rectFoto->h + this->etiquetaNombre->getAlto());
		this->etiquetaFichas->setAncho(rectFoto->w);
		if (ServiciosGraficos::getAltoVentana() < MAXIMO_ALTO_PANTALLA_PROP_TXT) {
			this->etiquetaFichas->setAlto((int)(ServiciosGraficos::getAltoVentana() 
				* ALTO_MAXIMO_ETIQUETA / MAXIMO_ALTO_PANTALLA_PROP_TXT));

		} else {
			this->etiquetaFichas->setAlto(ALTO_MAXIMO_ETIQUETA);
		}
	}

	int anchoCarta = (int)((this->getAncho() - rectFoto->w) * ANCHO_CARTA_PROPORCIONAL);
	int altoCarta = (int)((rectFoto->h / 2) * ALTO_CARTA_PROPORCIONAL);

	if (this->carta1 != NULL) {
		this->carta1->setPosX(this->getPosX() + rectFoto->w + SEPARACION_ENTRE_CARTAS);
		this->carta1->setPosY(this->getPosY());
		this->carta1->setAncho(anchoCarta);
		this->carta1->setAlto(altoCarta);
	}

	if (this->carta2 != NULL) {
		this->carta2->setPosX(this->getPosX() + this->getAncho() - anchoCarta);
		this->carta2->setPosY(this->getPosY() + (int)(rectFoto->h / 2) - altoCarta);
		this->carta2->setAncho(anchoCarta);
		this->carta2->setAlto(altoCarta);
	}

	if (this->apuesta != NULL) {
		this->apuesta->setPosX(this->getPosX() + rectFoto->w + SEPARACION_ENTRE_CARTAS);
		this->apuesta->setPosY(this->getPosY() + rectFoto->h / 2 + SEPARACION_CARTAS_APUESTA);
		this->apuesta->setAncho(this->getAncho() - rectFoto->w);
		this->apuesta->setAlto(rectFoto->h / 2 - SEPARACION_CARTAS_APUESTA);
	}
}

void Jugador::setearDisposicionADer(){

	if (this->imagen == NULL) {
		this->imagen = this->getImagenDefault();
	}

	SDL_Rect* rectFoto = this->calcularRectFoto();
	this->imagen->setPosX(this->getPosX() + this->getAncho() - rectFoto->w);
	this->imagen->setPosY(this->getPosY());

	if (this->etiquetaNombre != NULL) {
		this->etiquetaNombre->setPosX(this->getPosX() + this->getAncho() - rectFoto->w);
		this->etiquetaNombre->setPosY(this->getPosY() + rectFoto->h);
		this->etiquetaNombre->setAncho(rectFoto->w);
		if (ServiciosGraficos::getAltoVentana() < MAXIMO_ALTO_PANTALLA_PROP_TXT) {
			this->etiquetaNombre->setAlto((int)(ServiciosGraficos::getAltoVentana() 
				* ALTO_MAXIMO_ETIQUETA / MAXIMO_ALTO_PANTALLA_PROP_TXT));

		} else {
			this->etiquetaNombre->setAlto(ALTO_MAXIMO_ETIQUETA);
		}
	}

	if (this->etiquetaFichas != NULL) {
		this->etiquetaFichas->setPosX(this->getPosX() + this->getAncho() - rectFoto->w);
		this->etiquetaFichas->setPosY(this->getPosY() + rectFoto->h + this->etiquetaNombre->getAlto());
		this->etiquetaFichas->setAncho(rectFoto->w);
		if (ServiciosGraficos::getAltoVentana() < MAXIMO_ALTO_PANTALLA_PROP_TXT) {
			this->etiquetaFichas->setAlto((int)(ServiciosGraficos::getAltoVentana() 
				* ALTO_MAXIMO_ETIQUETA / MAXIMO_ALTO_PANTALLA_PROP_TXT));

		} else {
			this->etiquetaFichas->setAlto(ALTO_MAXIMO_ETIQUETA);
		}
	}

	int anchoCarta = (int)((this->getAncho() - rectFoto->w) * ANCHO_CARTA_PROPORCIONAL);
	int altoCarta = (int)((rectFoto->h / 2) * ALTO_CARTA_PROPORCIONAL);

	if (this->carta1 != NULL) {
		this->carta1->setPosX(this->getPosX());
		this->carta1->setPosY(this->getPosY());
		this->carta1->setAncho(anchoCarta);
		this->carta1->setAlto(altoCarta);
	}

	if (this->carta2 != NULL) {
		this->carta2->setPosX(this->getPosX() + this->getAncho() - rectFoto->w - anchoCarta);
		this->carta2->setPosY(this->getPosY() + (int)(rectFoto->h / 2) - altoCarta);
		this->carta2->setAncho(anchoCarta);
		this->carta2->setAlto(altoCarta);
	}

	if (this->apuesta != NULL) {
		this->apuesta->setPosX(this->getPosX());
		this->apuesta->setPosY(this->getPosY() + rectFoto->h / 2 + SEPARACION_CARTAS_APUESTA);
		this->apuesta->setAncho(this->getAncho() - rectFoto->w);
		this->apuesta->setAlto(rectFoto->h / 2 - SEPARACION_CARTAS_APUESTA);
	}
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

Imagen* Jugador::getImagenDefault(){
	Imagen* imagenDefault = new Imagen(RecursosAplicacion::getClienteConfigProperties()->get(
		"cliente.tema.default.jugador.imagen.default"));
	return imagenDefault;
}

Imagen* Jugador::getImagen() {
	return this->imagen;
}

void Jugador::setImagen(Imagen* imagen) {
	this->imagen = imagen;	
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

void Jugador::setApuesta(string cantidad) {
	if (this->apuesta == NULL) {
		this->apuesta = new Apuesta(cantidad);
	
	} else {
		this->apuesta->setCantidad(cantidad);
	}
}

Apuesta* Jugador::getApuesta(){
	return this->apuesta;
}

void Jugador::setFichas(int cantidad) {
	this->fichas = cantidad;
	if (this->etiquetaFichas == NULL) {
		this->etiquetaFichas = new Etiqueta();
		this->etiquetaFichas->setAlineacionHorizontal(ALINEACION_HORIZ_CENTRO);
		this->etiquetaFichas->setAlineacionVertical(ALINEACION_VERT_CENTRO);
		this->etiquetaFichas->setBorde(new Color(
			RecursosAplicacion::getClienteConfigProperties()->get("cliente.tema.default.etiquetas.borde")));
	}
	this->etiquetaFichas->setMensaje(UtilTiposDatos::enteroAString(cantidad));
}

int Jugador::getFichas() {
	return this->fichas;
}
