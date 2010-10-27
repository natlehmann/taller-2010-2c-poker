#include "Boton.h"
#include "RecursosCliente.h"
#include "ServiciosGraficos.h"
#include "UtilTiposDatos.h"
#include "Color.h"
#include "MensajesUtil.h"


Boton::Boton(string texto) : ComponentePanel(texto)
{
	this->colorFuente = RecursosCliente::getConfig()->get(
			"cliente.tema.default.boton.fuente.color");

	this->tamanioFuenteMax = UtilTiposDatos::getEntero(
			RecursosCliente::getConfig()->get(
				"cliente.tema.default.boton.fuente.tamanio.maximo"));

	this->estiloFuente = RecursosCliente::getConfig()->get(
			"cliente.configuracion.fuentes") + RecursosCliente::getConfig()->get(
						"cliente.tema.default.boton.fuente.estilo") + ".ttf";

	this->setearFuente();

	this->setAncho(-1);
	this->setAlto(-1);
	this->posX = 0;
	this->posY = 0;

	this->configurar();
	this->estado = 'u';
}

ComponentePanel* Boton::clonar() {

	Boton* boton = new Boton(this->getTexto());

	boton->setPosicion(this->getPosicion());
	boton->setAlto(this->getAlto());
	boton->setAncho(this->getAncho());
	boton->setId(this->getId());
	boton->setIdOperacion(this->getIdOperacion());
	
	boton->setHabilitado(this->isHabilitado());
	
	// estos metodos deben ejecutarse al final
	boton->setPosX(this->getPosX());
	boton->setPosY(this->getPosY());

	return boton;
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
}

void Boton::configurar() {
	string nombreImagenUp = "botonUp.bmp";
	string nombreImagenDown = "botonDown.bmp";
	string nombreImagenOver = "botonOver.bmp";
	this->imagenUp = this->setearImagen(nombreImagenUp);
	this->imagenDown = this->setearImagen(nombreImagenDown);
	this->imagenOver = this->setearImagen(nombreImagenOver);
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

bool Boton::checkWrite(SDL_Surface* superficie, SDL_Event* evento, int pressed){
	return false;
}
