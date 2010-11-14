#include "CheckBox.h"
#include "RecursosCliente.h"
#include "ServiciosGraficos.h"
#include "UtilTiposDatos.h"
#include "Color.h"
#include "MensajesUtil.h"


CheckBox::CheckBox(string texto) : ComponentePanel(texto)
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
	this->altoImagen = 13;
	this->anchoImagen = 13;
	this->espacio = 4;

	this->estado = 'u';
	this->checked = false;
	this->hayCambios = false;

	this->superficieTexto = NULL;
	this->hayCambiosTexto = true;

	this->configurar();
}

ComponentePanel* CheckBox::clonar() {

	CheckBox* checkBox = new CheckBox(this->getTexto());

	checkBox->setPosicion(this->getPosicion());
	checkBox->setAlto(this->getAlto());
	checkBox->setAncho(this->getAncho());
	checkBox->setId(this->getId());
	checkBox->setIdOperacion(this->getIdOperacion());
	
	checkBox->setHabilitado(this->isHabilitado());
	
	// estos metodos deben ejecutarse al final
	checkBox->setPosX(this->getPosX());
	checkBox->setPosY(this->getPosY());

	return checkBox;
}


CheckBox::~CheckBox(void)
{
	if (this->imagenCheck != NULL) {
		delete(this->imagenCheck);
	}
	if (this->imagenOverCheck != NULL) {
		delete(this->imagenOverCheck);
	}
	if (this->imagenOverUnCheck != NULL) {
		delete(this->imagenOverUnCheck);
	}
	if (this->imagenUnCheck != NULL) {
		delete(this->imagenUnCheck);
	}
	if (this->imagenDeshabilitado != NULL) {
		delete(this->imagenDeshabilitado);
	}

	SDL_FreeSurface(this->superficieTexto);
}

void CheckBox::configurar() {
	string nombreImagenCheck = "cbCheck.bmp";
	string nombreImagenUnCheck = "cbUnCheck.bmp";
	string nombreImagenOverCheck = "cbOverCheck.bmp";
	string nombreImagenOverUnCheck = "cbOverUnCheck.bmp";
	string nombreImagenDeshabilitado = "cbDeshabilitado.bmp";

	//if (this->imagenUp != NULL)
	//	delete(this->imagenUp);
	//if (this->imagenDown != NULL)
	//	delete(this->imagenDown);
	//if (this->imagenOver != NULL)
	//	delete(this->imagenOver);
	//if (this->imagenDeshabilitado != NULL)
	//	delete(this->imagenDeshabilitado);

	this->imagenCheck = this->setearImagen(nombreImagenCheck);
	this->imagenUnCheck = this->setearImagen(nombreImagenUnCheck);
	this->imagenOverCheck = this->setearImagen(nombreImagenOverCheck);
	this->imagenOverUnCheck = this->setearImagen(nombreImagenOverUnCheck);
	this->imagenDeshabilitado = this->setearImagen(nombreImagenDeshabilitado);
}

void CheckBox::dibujarSobreSup(SDL_Surface* superficie){

	Imagen* imagenADibujar = NULL;

	if (this->isHabilitado()) {

		switch (this->checked)
		{
		case false:
			imagenADibujar = this->imagenUnCheck;
			break;
		case true:
			imagenADibujar = this->imagenCheck;
			break;
		//case 'u':
		//	imagenADibujar = this->imagenUnCheck;
		//	break;
		//case 'c':
		//	imagenADibujar = this->imagenCheck;
		//	break;
		//case 'o':
		//	imagenADibujar = this->imagenOverUnCheck;
		//	break;
		//case 'b':
		//	imagenADibujar = this->imagenOverCheck;
		//	break;
		}

	} else {
		imagenADibujar = this->imagenDeshabilitado;
	}

	this->dibujarBoton(superficie, imagenADibujar);
	
}


Imagen* CheckBox::setearImagen(string nombreImagen)
{
	//Se genera el texto
	this->setearImagenTexto();

	//se configura la imagen 
	Imagen* imagen = new Imagen(nombreImagen);
	imagen->setPosX(this->getPosX());
	imagen->setPosY(this->getPosY());
	imagen->setAlto(this->altoImagen);
	imagen->setAncho(this->anchoImagen);

	imagen->generarSuperficie();	

	return imagen;
}
void CheckBox::setearImagenTexto()
{
	//Se genera el texto
	if (this->superficieTexto == NULL || this->hayCambiosTexto) 
	{
		this->superficieTexto = this->fuente->obtenerSuperficieTexto(this->texto, NULL);
		this->hayCambiosTexto = false;

		//actualiza el alto y ancho del control (para el over)
		this->setAlto(this->altoImagen);
		this->setAncho(this->anchoImagen + this->espacio + this->superficieTexto->w);
	}
}
SDL_Rect* CheckBox::getOffsetTexto() {

	SDL_Rect* offsetTexto = new SDL_Rect();
	offsetTexto->w = superficieTexto->w;
	offsetTexto->h = superficieTexto->h;

	offsetTexto->x = this->anchoImagen + this->espacio + this->getPosX();
	offsetTexto->y = (this->altoImagen - superficieTexto->h)/2 + this->getPosY();

	return offsetTexto;
}

void CheckBox::setPosX(int posX){
	ElementoGrafico::setPosX(posX);
	this->imagenUnCheck->setPosX(posX);
	this->imagenCheck->setPosX(posX);
	this->imagenOverCheck->setPosX(posX);
	this->imagenOverUnCheck->setPosX(posX);
	this->imagenDeshabilitado->setPosX(posX);
}

void CheckBox::setPosY(int posY){
	ElementoGrafico::setPosY(posY);
	this->imagenUnCheck->setPosY(posY);
	this->imagenCheck->setPosY(posY);
	this->imagenOverCheck->setPosY(posY);
	this->imagenOverUnCheck->setPosY(posY);
	this->imagenDeshabilitado->setPosY(posY);
}


void CheckBox::dibujarBoton(SDL_Surface* superficie, Imagen* imagen){

	this->setearImagenTexto();

	imagen->setHayCambios(true);
	imagen->dibujar(superficie);

	SDL_Rect* offsetTexto = this->getOffsetTexto();
	SDL_BlitSurface(this->superficieTexto, NULL, superficie, offsetTexto);
	delete(offsetTexto);
}


void CheckBox::dibujarOverCheck(SDL_Surface* superficie)
{
	this->checked = true;
	this->hayCambios = true;
	estado = 'b';
	if (this->habilitado) {
		this->dibujarBoton(superficie, this->imagenOverCheck);
	}
}
void CheckBox::dibujarOverUnCheck(SDL_Surface* superficie)
{
	this->checked = false;
	this->hayCambios = true;
	estado = 'o';
	if (this->habilitado) {
		this->dibujarBoton(superficie, this->imagenOverUnCheck);
	}
}

void CheckBox::dibujarDown(SDL_Surface* superficie)
{
	this->checked = true;
	this->hayCambios = true;
	estado = 'c';
	if (this->habilitado) {
		this->dibujarBoton(superficie, this->imagenCheck);
	}
}
void CheckBox::dibujarUp(SDL_Surface* superficie)
{
	this->checked = false;
	this->hayCambios = true;
	estado = 'u';
	if (this->habilitado) {
		this->dibujarBoton(superficie, this->imagenUnCheck);
	}
}

bool CheckBox::checkClick(SDL_Surface* superficie)
{
	if (this->isHabilitado()) {
		bool estaSobre = this->estaSobre();
		if(estaSobre)
		{
			bool fuePresionado = this->esClickIzquierdo();
			if(fuePresionado)
			{
				if(estado == 'b' || estado == 'c') {
					this->checked = false;
					dibujarOverUnCheck(superficie);			
					return true;
				}
				else if(estado == 'o' || estado == 'u') {
					this->checked = true;
					dibujarOverCheck(superficie);			
					return true;
				}
				return true;
			}
		}
	}

	return false;
}

bool CheckBox::checkOver(SDL_Surface* superficie)
{
	bool redibujar = false;
	if(this->isHabilitado()) {

		bool estaSobre = this->estaSobre();
		
		if(estaSobre)
		{
			if(estado != 'o' && estado != 'b')
			{
				bool fuePresionado = this->esClickIzquierdo();
				if(!fuePresionado) {

					if(estado == 'c') 
						dibujarOverCheck(superficie);
					if(estado == 'u')
						dibujarOverUnCheck(superficie);
					
					redibujar = true;

				} else {
					checkClick(superficie);
				}
			}
		}
		else
		{
			if(estado == 'o') {
				dibujarUp(superficie);
				redibujar = true;
			}
			else if(estado == 'b') {
				dibujarDown(superficie);
				redibujar = true;
			}
		}
	}

	return redibujar;
}


bool CheckBox::equals(ElementoGrafico* otro){

	//bool iguales = false;
	//if (otro != NULL && MensajesUtil::sonIguales(typeid(*otro).name(), "class Boton")) {
	//	Boton* otroBoton = (Boton*)otro;

	//	if (MensajesUtil::sonIguales(this->getTexto(), otroBoton->getTexto()) 
	//		&& MensajesUtil::sonIguales(this->getId(), otroBoton->getId()) 
	//		&& this->isHabilitado() == otroBoton->isHabilitado() ){
	//			iguales = true;
	//	}
	//}

	//return iguales;
	return false;
}

bool CheckBox::checkWrite(SDL_Surface* superficie, SDL_Event* evento, int pressed){
	return false;
}

void CheckBox::setTexto(string texto) {
	if (!MensajesUtil::sonIguales(this->texto, texto)) {
		this->texto = texto;
		this->hayCambiosTexto = true;
	}
}

void CheckBox::setChecked(bool checked) {
	this->checked = checked;
}

bool CheckBox::getChecked() {
	return this->checked;
}