#include "Jugador.h"
#include "ServiciosGraficos.h"
#include "UIException.h"
#include "MensajesUtil.h"
#include "Color.h"
#include "ImagenRecortada.h"
#include "RecursosCliente.h"
#include "UtilTiposDatos.h"
#include "Ventana.h"

Jugador::Jugador(void) {
	this->imagen = NULL;
	this->nombre = "";
	this->setAncho(ServiciosGraficos::getTamanioCeldaHoriz());
	this->setAlto(ServiciosGraficos::getTamanioCeldaVert());
	this->carta1 = NULL;
	this->carta2 = NULL;
	this->etiquetaNombre = NULL;
	this->etiquetaFichas = NULL;
	this->apuesta = NULL;
	this->fichas = 0;
	this->estado = JUGADOR_ACTIVO;
	this->dealer = false;

	this->imagenDealer = new Imagen("dealer.bmp");
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

	delete(this->imagenDealer);
}

void Jugador::dibujarSobreSup(SDL_Surface* superficie){

	if (this->posicion < 1) {
		throw UIException("No se puede dibujar al jugador porque no se ha seteado su posicion.","E");
	}

	this->calcularCoordenadas();

	if (this->imagen != NULL) {
		this->dibujarJugador(superficie);
	}

	if (this->isDealer()) {
		this->imagenDealer->dibujar(superficie);
	
	} else {
		this->ventana->borrarElemento(this->imagenDealer);
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

	Color* colorCirculo = new Color(RecursosCliente::getConfig()->get(
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

}

string Jugador::getNombre() {
	return this->nombre;
}

void Jugador::setNombre(string nombre){

	if (!MensajesUtil::sonIguales(this->getNombre(), nombre)) {

		this->nombre = nombre;
		if (this->etiquetaNombre == NULL) {
			this->etiquetaNombre = new Etiqueta();
			this->etiquetaNombre->setVentana(this->getVentana());
			this->etiquetaNombre->setAlineacionHorizontal(ALINEACION_HORIZ_CENTRO);
			this->etiquetaNombre->setAlineacionVertical(ALINEACION_VERT_CENTRO);
			this->etiquetaNombre->setBorde(new Color(
				RecursosCliente::getConfig()->get("cliente.tema.default.etiquetas.borde")));
		}
		this->etiquetaNombre->setMensaje(nombre);
		this->hayCambios = true;
	}
}


void Jugador::calcularCoordenadas() {

	switch(posicion) {

		case 1:
			this->posX = ServiciosGraficos::getAnchoVentana() - ServiciosGraficos::getBordeDerecho()
							- ServiciosGraficos::getTamanioCeldaHoriz() * 2;
			this->posY = ServiciosGraficos::getBordeSuperior();
			this->setearDisposicionADer();
			break;


		case 2:
			this->posX = ServiciosGraficos::getAnchoVentana() - ServiciosGraficos::getBordeDerecho()
							- ServiciosGraficos::getTamanioCeldaHoriz();
			this->posY = ServiciosGraficos::getTamanioCeldaVert() + ServiciosGraficos::getBordeSuperior();
			this->setearDisposicionADer();
			break;


		case 3:
			this->posX = ServiciosGraficos::getAnchoVentana() - ServiciosGraficos::getBordeDerecho()
							- ServiciosGraficos::getTamanioCeldaHoriz() * 2;
			this->posY = ServiciosGraficos::getAltoVentana() - ServiciosGraficos::getBordeInferior()
							- ServiciosGraficos::getTamanioCeldaVert();
			this->setearDisposicionADer();
			break;

		
		case 4:
			this->posX = ServiciosGraficos::getTamanioCeldaHoriz() + ServiciosGraficos::getBordeIzquierdo();
			this->posY =ServiciosGraficos::getAltoVentana() - ServiciosGraficos::getBordeInferior()
							- ServiciosGraficos::getTamanioCeldaVert();
			this->setearDisposicionAIzq();
			break;


		case 5:
			this->posX = ServiciosGraficos::getBordeIzquierdo();
			this->posY = ServiciosGraficos::getTamanioCeldaVert() + ServiciosGraficos::getBordeSuperior();
			this->setearDisposicionAIzq();
			break;


		case 6:
			this->posX = ServiciosGraficos::getBordeIzquierdo() + ServiciosGraficos::getTamanioCeldaHoriz();
			this->posY = ServiciosGraficos::getBordeSuperior();
			this->setearDisposicionAIzq();
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

	this->imagenDealer->setAncho(ALTO_MAXIMO_ETIQUETA);
	this->imagenDealer->setAlto(ALTO_MAXIMO_ETIQUETA);
	this->imagenDealer->setPosX(this->getPosX() + rectFoto->w + SEPARACION_CARTAS_APUESTA);
	this->imagenDealer->setPosY(this->getPosY() + rectFoto->h + ALTO_MAXIMO_ETIQUETA);
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

	this->imagenDealer->setAncho(ALTO_MAXIMO_ETIQUETA);
	this->imagenDealer->setAlto(ALTO_MAXIMO_ETIQUETA);
	this->imagenDealer->setPosX(this->getPosX() + this->getAncho() - rectFoto->w 
		- this->imagenDealer->getAncho() - SEPARACION_CARTAS_APUESTA);
	this->imagenDealer->setPosY(this->getPosY() + rectFoto->h + ALTO_MAXIMO_ETIQUETA);
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
	Imagen* imagenDefault = new Imagen(RecursosCliente::getConfig()->get(
		"cliente.tema.default.jugador.imagen.default"));
	return imagenDefault;
}

Imagen* Jugador::getImagen() {
	return this->imagen;
}

void Jugador::setImagen(string nombreImagen) {
	if (this->imagen == NULL || !MensajesUtil::sonIguales(this->imagen->getNombreSinPath(), nombreImagen)) {

		if (this->imagen != NULL) {
			delete (this->imagen);
		}

		this->imagen = new Imagen(nombreImagen);	
		this->hayCambios = true;
	}
}

/**
* Solo setea la carta si no fue seteada anteriormente.
*/
void Jugador::setCarta1(Carta* carta){
	if (this->carta1 == NULL) {
		this->carta1 = carta;
		this->carta1->setVentana(this->getVentana());
	}
	this->hayCambios = this->hayCambios || carta->getHayCambios();
}

/**
* Solo setea la carta si no fue seteada anteriormente.
*/
void Jugador::setCarta2(Carta* carta){
	if (this->carta2 == NULL) {
		this->carta2 = carta;
		this->carta2->setVentana(this->getVentana());
	}
	this->hayCambios = this->hayCambios || carta->getHayCambios();
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

	//if (this->apuesta == NULL || !MensajesUtil::sonIguales(this->apuesta->getCantidad(), cantidad)) {

		if (this->apuesta == NULL) {
			this->apuesta = new Apuesta(cantidad);
			this->apuesta->setVentana(this->getVentana());
		
		} else {
			this->apuesta->setCantidad(cantidad);
		}
		this->hayCambios = true;
	//}
}

Apuesta* Jugador::getApuesta(){
	return this->apuesta;
}

void Jugador::setFichas(int cantidad) {

	if (this->fichas != cantidad) {
		this->fichas = cantidad;
		if (this->etiquetaFichas == NULL) {
			this->etiquetaFichas = new Etiqueta();
			this->etiquetaFichas->setVentana(this->getVentana());
			this->etiquetaFichas->setAlineacionHorizontal(ALINEACION_HORIZ_CENTRO);
			this->etiquetaFichas->setAlineacionVertical(ALINEACION_VERT_CENTRO);
			this->etiquetaFichas->setBorde(new Color(
				RecursosCliente::getConfig()->get("cliente.tema.default.etiquetas.borde")));
		}
		this->etiquetaFichas->setMensaje(UtilTiposDatos::enteroAString(cantidad));
		this->hayCambios = true;
	}
}

int Jugador::getFichas() {
	return this->fichas;
}

ElementoGrafico* Jugador::getElementoPorId(string id){
	if (this->carta1 != NULL && MensajesUtil::sonIguales(this->carta1->getId(), id)) {
		return this->carta1;
	}

	if (this->carta2 != NULL && MensajesUtil::sonIguales(this->carta2->getId(), id)) {
		return this->carta2;
	}

	return NULL;
}

int Jugador::getEstado(){
	return this->estado;
}

void Jugador::setEstado(int estado){
	if (this->estado != estado) {
		this->estado = estado;

		if (estado == JUGADOR_AUSENTE) {
			this->setImagen(RecursosCliente::getConfig()->get(
				"cliente.tema.default.jugador.ausente.imagen"));

			if (this->etiquetaNombre != NULL) {
				this->etiquetaNombre->borrar();
			}

			if (this->etiquetaFichas != NULL) {
				this->etiquetaFichas->borrar();
			}
			
		}

		if (estado == JUGADOR_AUSENTE || estado == JUGADOR_INACTIVO) {

			if (this->apuesta != NULL) {
				this->apuesta->borrar();
			}

			if (this->carta1 != NULL) {
				this->carta1->borrar();
			}

			if (this->carta2 != NULL) {
				this->carta2->borrar();
			}
		}

		if (estado == JUGADOR_ACTIVO) {

			if (this->etiquetaNombre != NULL) {
				this->etiquetaNombre->setVisible(true);
			}

			if (this->etiquetaFichas != NULL) {
				this->etiquetaFichas->setVisible(true);
			}

			if (this->apuesta != NULL) {
				this->apuesta->setVisible(true);
			}

			if (this->carta1 != NULL) {
				//this->carta1->setVisible(true);  //controlado por servidor
			}

			if (this->carta2 != NULL) {
				//this->carta2->setVisible(true);  //controlado por servidor
			}
		}

		this->hayCambios = true;
	}
}

bool Jugador::isDealer(){
	return this->dealer;
}

void Jugador::setDealer(bool esDealer){
	if (this->dealer != esDealer) {
		this->dealer = esDealer;
		this->hayCambios = true;
		this->imagenDealer->setHayCambios(true);
	}
}