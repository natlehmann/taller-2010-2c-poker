#include "Bote.h"
#include <sstream>
Bote::Bote(void)
{
	int anchoSeccion = ServiciosGraficos::getTamanioCeldaHoriz();
	int altoSeccion = ServiciosGraficos::getTamanioCeldaVert();
	this->setAncho((int)(anchoSeccion*RELACION_ANCHO));
	this->setAlto((int)(altoSeccion*RELACION_ALTO));
	int posicionRelativaX = (anchoSeccion - this->ancho)/2;
	int posicionRelativaY = (altoSeccion - this->alto)/2;
	this->posX = ServiciosGraficos::getBordeIzquierdo() + ServiciosGraficos::getTamanioCeldaHoriz() * 2 + posicionRelativaX;
	this->posY = ServiciosGraficos::getBordeSuperior() + posicionRelativaY;
	this->imagen = NULL;
	this->etiqueta = NULL;
	this->total = 0;
}

Bote::~Bote(void)
{
	if (this->imagen != NULL) 
		delete(this->imagen);
}

void Bote::dibujarSobreSup(SDL_Surface* superficie)
{
	if (this->imagen == NULL) {
		this->imagen = new Imagen(
			RecursosAplicacion::getClienteConfigProperties()->get(
			"cliente.tema.default.imagen.bote"));
	}

//	this->imagen = new Imagen(nombreImagen);
	int altoEtiqueta = (int)(this->getAlto() * BOTE_ALTO_ETIQUETA);

	if (this->etiqueta == NULL) {
		this->etiqueta = new Etiqueta();
	}

	this->etiqueta->setPosX(this->getPosX());
	this->etiqueta->setPosY(this->getPosY());
	this->etiqueta->setAncho(this->getAncho());
	this->etiqueta->setAlto(altoEtiqueta);

	std::stringstream mensaje;
	mensaje << this->getTotal();
	this->etiqueta->setMensaje(mensaje.str());

	this->imagen->setPosX(this->getPosX());
	this->imagen->setPosY(this->getPosY()+ altoEtiqueta);
	this->imagen->setAncho(this->getAncho());
	this->imagen->setAlto(this->getAlto());

	this->imagen->dibujar(superficie);
	this->etiqueta->dibujar(superficie);
}

int Bote::getTotal() 
{
	return this->total;
}

void Bote::setTotal(int total) 
{
	this->total = total;
}
