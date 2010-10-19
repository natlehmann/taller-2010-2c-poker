#include "Boton.h"
#include "RecursosAplicacion.h"
#include "ServiciosGraficos.h"
#include "UtilTiposDatos.h"
#include "Color.h"
#include "MensajesUtil.h"


Boton::Boton(string texto)
{
	this->setearFuente();

	this->setTexto(texto);
	this->setAncho(0);
	this->setAlto(0);
	this->posX = 0;
	this->posY = 0;
	this->ajustarAlTexto = true;

	string nombreImagenUp = "botonUp.bmp";
	string nombreImagenDown = "botonDown.bmp";
	string nombreImagenOver = "botonOver.bmp";
	this->imagenUp = this->setearImagen(nombreImagenUp);
	this->imagenDown = this->setearImagen(nombreImagenDown);
	this->imagenOver = this->setearImagen(nombreImagenOver);

	this->estado = 'u';

	this->habilitado = false;
	this->idOperacion = "";
}

Boton::Boton(Boton* orig) {

	this->setearFuente();
	this->ajustarAlTexto = true;

	this->setTexto(orig->getTexto());
	this->setPosicion(orig->getPosicion());
	this->setAlto(orig->getAlto());
	this->setAncho(orig->getAncho());
	this->setId(orig->getId());
	this->setIdOperacion(orig->getIdOperacion());

	string nombreImagenUp = "botonUp.bmp";
	string nombreImagenDown = "botonDown.bmp";
	string nombreImagenOver = "botonOver.bmp";
	this->imagenUp = this->setearImagen(nombreImagenUp);
	this->imagenDown = this->setearImagen(nombreImagenDown);
	this->imagenOver = this->setearImagen(nombreImagenOver);

	this->estado = 'u';	
	
	this->setHabilitado(orig->isHabilitado());
	
	// estos metodos deben ejecutarse al final
	this->setPosX(orig->getPosX());
	this->setPosY(orig->getPosY());	
}


Boton::~Boton(void)
{
	if (this->imagenDown != NULL) {
		delete(this->imagenDown);
	}
	if (this->imagenOver != NULL) {
		delete(this->imagenOver);
	}
	if (this->imagenUp != NULL) {
		delete(this->imagenUp);
	}
	if (this->fuente != NULL) {
		delete(this->fuente);
	}
}

void Boton::dibujarSobreSup(SDL_Surface* superficie){

	switch (this->estado)
	{
	case 'u':
		this->imagenUp->dibujar(superficie);
		break;
	case 'd':
		this->imagenDown->dibujar(superficie);
		break;
	case 'o':
		this->imagenOver->dibujar(superficie);
		break;
	}
}

void Boton::setearFuente() {

	string colorFuente = RecursosAplicacion::getClienteConfigProperties()->get(
		"cliente.tema.default.boton.fuente.color");

	int tamanioFuenteMax = UtilTiposDatos::getEntero(RecursosAplicacion::getClienteConfigProperties()->get(
		"cliente.tema.default.boton.fuente.tamanio.maximo"));

	int tamanioFuente = tamanioFuenteMax;
	if (ServiciosGraficos::getAnchoVentana() < MAXIMO_ANCHO_PANTALLA_PROP_TXT) {
		tamanioFuente = (int)(ServiciosGraficos::getAnchoVentana() * tamanioFuenteMax 
			/ MAXIMO_ANCHO_PANTALLA_PROP_TXT);
	}

	string estiloFuente = RecursosAplicacion::getClienteConfigProperties()->get("cliente.configuracion.fuentes") +
						RecursosAplicacion::getClienteConfigProperties()->get("cliente.tema.default.boton.fuente.estilo") + ".ttf";
	this->fuente = new Fuente(colorFuente, tamanioFuente, estiloFuente);
}

Imagen* Boton::setearImagen(string nombreImagen)
{
	//Se genera el texto
	SDL_Surface* superficieTexto = this->fuente->obtenerSuperficieTexto(this->texto, NULL);

	//se configura la imagen 
	Imagen* imagen = new Imagen(nombreImagen);
	imagen->setPosX(this->getPosX());
	imagen->setPosY(this->getPosY());
	
	if (this->ajustarAlTexto)
	{
		int paddingV = ServiciosGraficos::getAnchoVentana() > MAXIMO_ANCHO_PANTALLA_PROP_TXT ? 
				PADDING_VERT : (int)(PADDING_VERT / 2);
		this->setAlto(superficieTexto->h + paddingV);
		this->setAncho(superficieTexto->w + PADDING_HORIZ);
	}

	imagen->setAlto(this->getAlto());
	imagen->setAncho(this->getAncho());
	imagen->generarSuperficie();
	SDL_Surface* superficieImagen = imagen->getSuperficie();

	//se configura offset texto
	SDL_Rect* offsetTexto = new SDL_Rect();
	offsetTexto->w = superficieTexto->w;
	offsetTexto->h = superficieTexto->h;

	if (this->ancho > superficieTexto->w)
		offsetTexto->x = (this->ancho - superficieTexto->w)/2;
	else
		offsetTexto->x = this->posX;
	if (this->alto > superficieTexto->h)
		offsetTexto->y = (this->alto - superficieTexto->h)/2;
	else
		offsetTexto->y = this->posY;

	SDL_BlitSurface(superficieTexto, NULL, imagen->getSuperficie(), offsetTexto);

	SDL_FreeSurface(superficieTexto);

	return imagen;
}

void Boton::setPosX(int posX){
	ElementoGrafico::setPosX(posX);
	this->imagenUp->setPosX(posX);
	this->imagenDown->setPosX(posX);
	this->imagenOver->setPosX(posX);
}

void Boton::setPosY(int posY){
	ElementoGrafico::setPosY(posY);
	this->imagenUp->setPosY(posY);
	this->imagenDown->setPosY(posY);
	this->imagenOver->setPosY(posY);
}


void Boton::dibujarOver(SDL_Surface* superficie)
{
	this->imagenOver->setHayCambios(true);
	this->hayCambios = true;
	this->imagenOver->dibujar(superficie);
	estado = 'o';
}
void Boton::dibujarDown(SDL_Surface* superficie)
{
	this->imagenDown->setHayCambios(true);
	this->hayCambios = true;
	this->imagenDown->dibujar(superficie);
	estado = 'd';
}
void Boton::dibujarUp(SDL_Surface* superficie)
{
	this->imagenUp->setHayCambios(true);
	this->hayCambios = true;
	this->imagenUp->dibujar(superficie);
	estado = 'u';
}

bool Boton::checkClick(SDL_Surface* superficie)
{
	bool estaSobre = this->estaSobre();
	if(estaSobre)
	{
		bool fuePresionado = this->esClickIzquierdo();
		if(fuePresionado)
		{
			if(estado != 'd') {
				dibujarDown(superficie);			
				return true;
			}
		}
	}
	return false;
}

bool Boton::checkOver(SDL_Surface* superficie)
{
	bool estaSobre = this->estaSobre();
	bool redibujar = false;
	
	if(estaSobre)
	{
		if(estado != 'o')
		{
			bool fuePresionado = this->esClickIzquierdo();
			if(!fuePresionado) {
				dibujarOver(superficie);
				redibujar = true;

			} else {
				checkClick(superficie);
			}
		}
	}
	else
	{
		if(estado != 'u') {
			dibujarUp(superficie);
			redibujar = true;
		}
	}

	return redibujar;
}

bool Boton::estaSobre()
{
	int checkx,checky;
	SDL_GetMouseState(&checkx, &checky);
	if(checkx >= this->posX && checkx <= (this->posX + this->ancho) && checky >= this->posY && checky <= (this->posY + this->alto))
		return true;

	return false;
}

bool Boton::esClickIzquierdo()
{
	if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
		return true;

	return false;
}

bool Boton::esClickDerecho()
{
	if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT))
		return true;

	return false;
}

string Boton::getTexto() {
	return this->texto;
}
void Boton::setTexto(string texto) {
	this->texto = texto;
	this->hayCambios = true;
}

bool Boton::isHabilitado(){
	return this->habilitado;
}

void Boton::setHabilitado(bool habilitado){
	this->habilitado = habilitado;
}

string Boton::getIdOperacion(){
	return this->idOperacion;
}

void Boton::setIdOperacion(string idOperacion){
	this->idOperacion = idOperacion;
}

bool Boton::equals(ElementoGrafico* otro){

	bool iguales = false;
	if (otro != NULL && MensajesUtil::sonIguales(typeid(*otro).name(), "class Boton")) {
		Boton* otroBoton = (Boton*)otro;

		if (MensajesUtil::sonIguales(this->getTexto(), otroBoton->getTexto()) 
			&& MensajesUtil::sonIguales(this->getId(), otroBoton->getId()) 
			&& this->isHabilitado() == otroBoton->isHabilitado() ){
				iguales = true;
		}
	}

	return iguales;
}