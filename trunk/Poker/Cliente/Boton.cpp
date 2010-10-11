#include "Boton.h"
#include "RecursosAplicacion.h"
#include "ServiciosGraficos.h"
#include "UtilTiposDatos.h"
#include "Fuente.h"
#include "Color.h"


Boton::Boton(void) 
{
	this->setTexto(" ");
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
}

Boton::Boton(string texto)
{
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
}

Boton::Boton(string texto, int posx, int posy)
{
	this->setTexto(texto);
	this->setAncho(0);
	this->setAlto(0);
	this->posX = posx;
	this->posY = posy;
	this->ajustarAlTexto = true;

	string nombreImagenUp = "botonUp.bmp";
	string nombreImagenDown = "botonDown.bmp";
	string nombreImagenOver = "botonOver.bmp";
	this->imagenUp = this->setearImagen(nombreImagenUp);
	this->imagenDown = this->setearImagen(nombreImagenDown);
	this->imagenOver = this->setearImagen(nombreImagenOver);

	this->estado = 'u';
}

Boton::Boton(string texto, int ancho, int alto, int posx, int posy)
{
	this->setTexto(texto);
	this->setAncho(ancho);
	this->setAlto(alto);
	this->posX = posx;
	this->posY = posy;
	this->ajustarAlTexto = false;

	string nombreImagenUp = "botonUp.bmp";
	string nombreImagenDown = "botonDown.bmp";
	string nombreImagenOver = "botonOver.bmp";
	this->imagenUp = this->setearImagen(nombreImagenUp);
	this->imagenDown = this->setearImagen(nombreImagenDown);
	this->imagenOver = this->setearImagen(nombreImagenOver);

	this->estado = 'u';
}

Boton::~Boton(void)
{
	if (this->imagenDown != NULL) 
		delete(this->imagenDown);
	if (this->imagenOver != NULL) 
		delete(this->imagenOver);
	if (this->imagenUp != NULL) 
		delete(this->imagenUp);
}

void Boton::dibujarSobreSup(SDL_Surface* superficie){

	this->setearPosicion();

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
	string colorFuente = RecursosAplicacion::getClienteConfigProperties()->get("cliente.tema.default.boton.fuente.color");
	int tamanioFuente = UtilTiposDatos::getEntero(RecursosAplicacion::getClienteConfigProperties()->get("cliente.tema.default.boton.fuente.tamanio"));
	string estiloFuente = RecursosAplicacion::getClienteConfigProperties()->get("cliente.configuracion.fuentes") +
						RecursosAplicacion::getClienteConfigProperties()->get("cliente.tema.default.boton.fuente.estilo") + ".ttf";
	Fuente* fuente = new Fuente(colorFuente, tamanioFuente, estiloFuente);
	SDL_Surface* superficieTexto = fuente->obtenerSuperficieTexto(this->texto, NULL);

	//se configura la imagen 
	Imagen* imagen = new Imagen(nombreImagen);
	imagen->setPosX(this->getPosX());
	imagen->setPosY(this->getPosY());
	
	if (this->ajustarAlTexto)
	{
		this->setAlto(superficieTexto->h + 10);
		this->setAncho(superficieTexto->w + 10);
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

	delete(fuente);
	delete(superficieTexto);

	return imagen;
}

void Boton::setearPosicion()
{
	this->imagenUp->setPosX(this->posX);
	this->imagenUp->setPosY(this->posY);
	this->imagenDown->setPosX(this->posX);
	this->imagenDown->setPosY(this->posY);
	this->imagenOver->setPosX(this->posX);
	this->imagenOver->setPosY(this->posY);
}

void Boton::dibujarOver(SDL_Surface* superficie)
{
	this->imagenOver->dibujar(superficie);
	this->refrescar(superficie);
	estado = 'o';
}
void Boton::dibujarDown(SDL_Surface* superficie)
{
	this->imagenDown->dibujar(superficie);
	this->refrescar(superficie);
	estado = 'd';
}
void Boton::dibujarUp(SDL_Surface* superficie)
{
	this->imagenUp->dibujar(superficie);
	this->refrescar(superficie);
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
			if(estado != 'd')
				dibujarDown(superficie);
			
			return true;
		}
	}
	return false;
}

bool Boton::checkOver(SDL_Surface* superficie)
{
	bool estaSobre = this->estaSobre();
	
	if(estaSobre)
	{
		if(estado != 'o')
		{
			bool fuePresionado = this->esClickIzquierdo();
			if(!fuePresionado)
				dibujarOver(superficie);
			else
				checkClick(superficie);
		}
	}
	else
	{
		if(estado != 'u')
			dibujarUp(superficie);
	}

	return estaSobre;
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
}