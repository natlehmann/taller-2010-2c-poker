#include "TextBox.h"
#include "RecursosAplicacion.h"
#include "MensajesUtil.h"
#include "ServiciosGraficos.h"

TextBox::TextBox(void) {
	this->fondoFoco = new Color(RecursosAplicacion::getClienteConfigProperties()->get("cliente.tema.default.textbox.fondofoco"));
	this->fondoNotFoco = new Color(RecursosAplicacion::getClienteConfigProperties()->get("cliente.tema.default.textbox.fondonotfoco"));
	this->alineacionHorizontal = ALINEACION_HORIZ_IZQUIERDA;
	this->alineacionVertical = ALINEACION_VERT_CENTRO;
	this->borde = NULL;
	this->foco = false;
	this->cursorPosition = 0;
}

TextBox::TextBox(string mensaje){
	this->fondoFoco = new Color(RecursosAplicacion::getClienteConfigProperties()->get("cliente.tema.default.textbox.fondofoco"));
	this->fondoNotFoco = new Color(RecursosAplicacion::getClienteConfigProperties()->get("cliente.tema.default.textbox.fondonotfoco"));
	this->borde = new Color(RecursosAplicacion::getClienteConfigProperties()->get("cliente.tema.default.textbox.borde"));
	this->mensaje = mensaje;
	this->alineacionHorizontal = ALINEACION_HORIZ_IZQUIERDA;
	this->alineacionVertical = ALINEACION_VERT_CENTRO;
	this->foco = false;
	this->cursorPosition = this->mensaje.size();
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
	if (this->fuente != NULL) {
		delete(this->fuente);
	}
}

void TextBox::dibujarSobreSup(SDL_Surface* superficie){ 

	//se configura la fuente
	string colorFuente = RecursosAplicacion::getClienteConfigProperties()->get("cliente.tema.default.textbox.fuente.color");
	string estiloFuente = RecursosAplicacion::getClienteConfigProperties()->get("cliente.configuracion.fuentes") + RecursosAplicacion::getClienteConfigProperties()->get("cliente.tema.default.textbox.fuente.estilo") + ".ttf";
	int anchoPantalla = ServiciosGraficos::getAnchoVentana();
	int tamanioMax = UtilTiposDatos::getEntero(RecursosAplicacion::getClienteConfigProperties()->get("cliente.tema.default.textbox.fuente.tamanio.maximo"));
	int tamanioFuente = tamanioMax;
	if (anchoPantalla < MAXIMO_ANCHO_PANTALLA_PROP_TXT) {
		tamanioFuente = (int)(anchoPantalla * tamanioMax / MAXIMO_ANCHO_PANTALLA_PROP_TXT);
	}
	this->fuente = new Fuente(colorFuente, tamanioFuente, estiloFuente);
		
	//dibuja el texto
	this->dibujarTexto(superficie);

}

void TextBox::dibujarTexto(SDL_Surface* superficie) {
	//se crea la imagen del texto
	string mensajeConCursor = this->mensaje;
	if (this->foco) mensajeConCursor.insert(this->cursorPosition, "|");
	SDL_Surface* superficieTexto = fuente->obtenerSuperficieTexto(mensajeConCursor, NULL);
	
	//se configura el borde
	SDL_Rect* offset = this->getOffsetRect();
	offset->w = this->getAncho();
	offset->h = this->getAlto();
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
	if (this->foco) 
	{
		string newCaracter;

		if(evento->key.keysym.sym == SDLK_BACKSPACE)
		{
			if(!mensaje.empty() && this->cursorPosition > 0)
			{
				mensaje.erase(this->cursorPosition - 1, 1);
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
			if (this->mensaje.size() > this->cursorPosition)
				this->cursorPosition++;
		}
		else if(evento->key.keysym.unicode < 0x80 && evento->key.keysym.unicode > 0) {
			newCaracter += (char)evento->key.keysym.unicode;
			this->mensaje.insert(this->cursorPosition, newCaracter);
			this->cursorPosition++;
		}
		

		this->dibujarTexto(superficie);
		this->refrescar(superficie);
		return true;
	}

	return false;
}

bool TextBox::checkClick(SDL_Surface* superficie)
{
	bool fuePresionado = this->esClickIzquierdo();
	bool estaSobre = this->estaSobre();
	if(estaSobre && fuePresionado)
	{
		if(!this->foco)
		{
			this->cursorPosition = this->mensaje.size();
			this->foco = true;
			this->dibujarTexto(superficie);
			this->refrescar(superficie);
		}
		
		return true;
	}
	else if(!estaSobre && fuePresionado)
	{
		if(this->foco)
		{
			this->foco = false;
			this->dibujarTexto(superficie);
			this->refrescar(superficie);
		}
		
		return true;
	}

	return false;
}

bool TextBox::checkOver(SDL_Surface* superficie)
{
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

bool TextBox::estaSobre()
{
	int checkx,checky;
	SDL_GetMouseState(&checkx, &checky);
	if(checkx >= this->posX && checkx <= (this->posX + this->ancho) && checky >= this->posY && checky <= (this->posY + this->alto))
		return true;

	return false;
}

bool TextBox::esClickIzquierdo()
{
	if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
		return true;

	return false;
}

bool TextBox::esClickDerecho()
{
	if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT))
		return true;

	return false;
}

void TextBox::setMensaje(string mensaje) {
	this->mensaje = mensaje;
}

string TextBox::getMensaje() {
	return this->mensaje;
}

void TextBox::setFondoFoco(Color* color){
	if (this->fondoFoco != NULL) {
		delete(this->fondoFoco);
	}
	this->fondoFoco = color;
}

Color* TextBox::getFondoFoco() {
	return this->fondoFoco;
}

void TextBox::setFondoNotFoco(Color* color){
	if (this->fondoNotFoco != NULL) {
		delete(this->fondoNotFoco);
	}
	this->fondoNotFoco = color;
}

Color* TextBox::getFondoNotFoco() {
	return this->fondoNotFoco;
}

void TextBox::setBorde(Color* color){
	if (this->borde != NULL) {
		delete (this->borde);
	}
	this->borde = color;
}
Color* TextBox::getBorde(){
	return this->borde;
}

void TextBox::setAlineacionHorizontal(int alineacion) {
	this->alineacionHorizontal = alineacion;
}

int TextBox::getAlineacionHorizontal(){
	return this->alineacionHorizontal;
}

void TextBox::setAlineacionVertical(int alineacion){
	this->alineacionVertical = alineacion;
}

int TextBox::getAlineacionVertical(){
	return this->alineacionVertical;
}
