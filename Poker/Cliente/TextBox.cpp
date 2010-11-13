#include "TextBox.h"
#include "RecursosCliente.h"
#include "MensajesUtil.h"
#include "ServiciosGraficos.h"

TextBox::TextBox(string mensaje) : ComponentePanel(mensaje) {

	this->fondoFoco = new Color(RecursosCliente::getConfig()->get(
		"cliente.tema.default.textbox.fondofoco"));

	this->fondoNotFoco = new Color(RecursosCliente::getConfig()->get(
		"cliente.tema.default.textbox.fondonotfoco"));

	this->fondoDeshabilitado = new Color(RecursosCliente::getConfig()->get(
		"cliente.tema.default.textbox.fondoDeshabilitado"));

	this->borde = new Color(RecursosCliente::getConfig()->get(
		"cliente.tema.default.textbox.borde"));

	this->colorFuente = RecursosCliente::getConfig()->get(
			"cliente.tema.default.textbox.fuente.color");

	this->tamanioFuenteMax = UtilTiposDatos::getEntero(
			RecursosCliente::getConfig()->get(
				"cliente.tema.default.textbox.fuente.tamanio.maximo"));

	this->estiloFuente = RecursosCliente::getConfig()->get(
			"cliente.configuracion.fuentes") + RecursosCliente::getConfig()->get(
						"cliente.tema.default.textbox.fuente.estilo") + ".ttf";

	this->setearFuente();

	this->alineacionHorizontal = ALINEACION_HORIZ_IZQUIERDA;
	this->alineacionVertical = ALINEACION_VERT_CENTRO;
	this->tipoPassword = false;
	this->foco = false;
	this->cursorPosition = this->texto.size();
}

ComponentePanel* TextBox::clonar(){

	TextBox* textBox = new TextBox(this->getTexto());
	textBox->setPosicion(this->getPosicion());
	textBox->setAlto(this->getAlto());
	textBox->setAncho(this->getAncho());
	textBox->setId(this->getId());
	textBox->setIdOperacion(this->getIdOperacion());
	
	textBox->setHabilitado(this->isHabilitado());
	
	textBox->setPosX(this->getPosX());
	textBox->setPosY(this->getPosY());

	return textBox;
}

TextBox::~TextBox(void) {
	if (this->fondoFoco != NULL) {
		delete(this->fondoFoco);
	}
	if (this->fondoNotFoco != NULL) {
		delete(this->fondoNotFoco);
	}
	if (this->borde != NULL) {
		delete(this->borde);
	}
	if (this->fondoDeshabilitado != NULL) {
		delete(this->fondoDeshabilitado);
	}
}

void TextBox::dibujarSobreSup(SDL_Surface* superficie){ 
		
	this->dibujarTexto(superficie);

}

void TextBox::dibujarTexto(SDL_Surface* superficie) {

	if (this->isHabilitado()) {

		//se crea la imagen del texto
		string mensajeConCursor;
		if (!this->tipoPassword)
			mensajeConCursor = this->texto;
		else
			mensajeConCursor = mensajeConCursor.insert(0, this->texto.length(), '*');

		if (this->foco) mensajeConCursor.insert(this->cursorPosition, "|");
		SDL_Surface* superficieTexto = fuente->obtenerSuperficieTexto(mensajeConCursor, NULL);
		
		//se configura el borde
		SDL_Rect* offset = this->getContornoConOffset();
		if (this->borde != NULL) {
			ServiciosGraficos::dibujarContorno(superficie, offset, this->borde);
		}

		//se configura el fondo
		SDL_Rect* offsetBox = new SDL_Rect();
		offsetBox->x = offset->x;
		offsetBox->y = offset->y;
		offsetBox->w = offset->w;
		offsetBox->h = offset->h;
		if (this->fondoFoco != NULL && this->fondoNotFoco != NULL) {
			offsetBox->x += 1;
			offsetBox->y += 1;
			offsetBox->w -= 2;
			offsetBox->h -= 2;

			if (this->foco)
				SDL_FillRect(superficie, offsetBox, this->fondoFoco->toUint32(superficie));
			else
				SDL_FillRect(superficie, offsetBox, this->fondoNotFoco->toUint32(superficie));
		}

		//se pega en la pantalla y se libera recursos
		if (superficieTexto != NULL) {
			//se configura el texto visible
			SDL_Rect* offsetTexto = new SDL_Rect();
			offsetTexto->x = (superficieTexto->w > offsetBox->w ? superficieTexto->w - offsetBox->w : 0);
			offsetTexto->y = 0;
			offsetTexto->w = offsetBox->w;
			offsetTexto->h = offsetBox->h;
			offsetBox->y += (superficieTexto->h > offsetBox->h ? 0 : (offsetBox->h - superficieTexto->h)/2);

			SDL_BlitSurface(superficieTexto, offsetTexto, superficie, offsetBox);

			delete(offsetTexto);
		}

		delete(offsetBox);
		SDL_FreeSurface(superficieTexto);

	} else {
		// si esta deshabilitado
		SDL_FillRect(superficie, this->getContornoConOffset(), 
			this->fondoDeshabilitado->toUint32(superficie));
	}

}

void TextBox::ajustarOffset(SDL_Rect* offset, SDL_Surface* superficie) {

	switch(this->alineacionHorizontal) {

		case ALINEACION_HORIZ_DERECHA:
			offset->x = offset->x + offset->w - superficie->w;
			break;

		case ALINEACION_HORIZ_CENTRO:
			offset->x = (int)(offset->x + (offset->w - superficie->w) / 2);
			break;

		// en caso de alineacion izquierda, no cambia nada
	}

	switch (this->alineacionVertical) {

		case ALINEACION_VERT_ABAJO:
			offset->y = offset->y + offset->h - superficie->h;
			break;

		case ALINEACION_VERT_CENTRO:
			offset->y = (int)(offset->y + (offset->h - superficie->h) / 2);
			break;

		// en caso de alineacion arriba, no cambia nada
	}
}

bool TextBox::checkWrite(SDL_Surface* superficie, SDL_Event* evento, int pressed)
{
	if (this->isHabilitado()) {

		if (this->foco) 
		{
			string newCaracter;

			if(evento->key.keysym.sym == SDLK_BACKSPACE)
			{
				if(!texto.empty() && this->cursorPosition > 0)
				{
					texto.erase(this->cursorPosition - 1, 1);
					this->cursorPosition--;
				}
			}
			else if(evento->key.keysym.sym == SDLK_RETURN ||
					evento->key.keysym.sym == SDLK_TAB)
			{
				this->foco = false;
			}
			else if(evento->key.keysym.sym == SDLK_LEFT)
			{
				if (this->cursorPosition > 0)
					this->cursorPosition--;
			}
			else if(evento->key.keysym.sym == SDLK_RIGHT)
			{
				if (this->texto.size() > this->cursorPosition)
					this->cursorPosition++;
			}
			else if(evento->key.keysym.unicode < 0x80 && evento->key.keysym.unicode > 0) {
				newCaracter += (char)evento->key.keysym.unicode;
				this->texto.insert(this->cursorPosition, newCaracter);
				this->cursorPosition++;
			}
			

			this->dibujarTexto(superficie);
			this->hayCambios = true;
			return true;
		}
	}

	return false;
}

bool TextBox::checkClick(SDL_Surface* superficie)
{
	if (this->isHabilitado()) {

		bool fuePresionado = this->esClickIzquierdo();
		bool estaSobre = this->estaSobre();
		if(estaSobre && fuePresionado)
		{
			if(!this->foco)
			{
				this->cursorPosition = this->texto.size();
				this->foco = true;
				this->dibujarTexto(superficie);
				this->hayCambios = true;
			}
			
			//return true;
		}
		else if(!estaSobre && fuePresionado)
		{
			if(this->foco)
			{
				this->foco = false;
				this->dibujarTexto(superficie);
				this->hayCambios = true;
			}
			
			//return true;
		}
	}

	return false;
}

bool TextBox::checkOver(SDL_Surface* superficie)
{
	if (this->isHabilitado()) {

		bool estaSobre = this->estaSobre();
		
		if(estaSobre)
		{
			//Si el puntero es de felchita, hay que cambiar el puntero a escritura	
		}
		else
		{
			//Si el puntero es de escritura, hay que cambiar el puntero a flecha

		}

		return estaSobre;
	}

	return false;
}

void TextBox::setTipoPassword(bool tipoPassword)
{
	this->tipoPassword = tipoPassword;
}

bool TextBox::setTipoPassword()
{
	return this->tipoPassword;
}

void TextBox::setFondoFoco(Color* color){
	// TODO: REVISAR
	if (this->fondoFoco != NULL) {
		delete(this->fondoFoco);
	}
	this->fondoFoco = color;
}

Color* TextBox::getFondoFoco() {
	return this->fondoFoco;
}

void TextBox::setFondoNotFoco(Color* color){
	// TODO: REVISAR
	if (this->fondoNotFoco != NULL) {
		delete(this->fondoNotFoco);
	}
	this->fondoNotFoco = color;
}

Color* TextBox::getFondoNotFoco() {
	return this->fondoNotFoco;
}

void TextBox::setBorde(Color* color){
	// TODO: REVISAR
	if (this->borde != NULL) {
		delete (this->borde);
	}
	this->borde = color;
}
Color* TextBox::getBorde(){
	return this->borde;
}

void TextBox::setAlineacionHorizontal(int alineacion) {
	// TODO: REVISAR
	this->alineacionHorizontal = alineacion;
}

int TextBox::getAlineacionHorizontal(){
	return this->alineacionHorizontal;
}

void TextBox::setAlineacionVertical(int alineacion){
	// TODO: REVISAR
	this->alineacionVertical = alineacion;
}

int TextBox::getAlineacionVertical(){
	return this->alineacionVertical;
}

void TextBox::dibujarDown(SDL_Surface* superficie){
}
void TextBox::dibujarUp(SDL_Surface* superficie){
}
