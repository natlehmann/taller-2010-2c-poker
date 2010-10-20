#include "Panel.h"
#include "ServiciosGraficos.h"
#include "RecursosAplicacion.h"
#include "PokerException.h"
#include "MensajesUtil.h"

Panel::Panel(void)
{
	//setamos el fondo del menu de operaciones
	this->borde = new Color(RecursosAplicacion::getClienteConfigProperties()->get("cliente.tema.default.menu.borde"));
	this->fondo = new Color(RecursosAplicacion::getClienteConfigProperties()->get("cliente.tema.default.menu.fondo"));

	//agrega botones a la pantalla
	//this->configurarBotones();

	for (int i=0; i < MAX_CANT_BOTONES; i++) {
		this->botones[i] = NULL;
	}

	this->hayNuevosBotones = true;
}

Panel::~Panel(void)
{
	delete(borde);
	delete(fondo);

	for (int i=0; i < MAX_CANT_BOTONES; i++) {
		if (this->botones[i] != NULL){
			delete (this->botones[i]);
		}
	}

	for (list<Boton*>::iterator it = this->listaBotones.begin(); it != this->listaBotones.end(); it++) {
		delete(*it);
	}

	this->listaBotones.clear();
}

void Panel::agregarBoton(Boton* boton, int posicion){

	if (posicion < MAX_CANT_BOTONES) {

		if (this->botones[posicion] == NULL || !this->botones[posicion]->equals(boton)) {

			if (this->botones[posicion] != NULL) {
				delete(this->botones[posicion]);
			}

			this->botones[posicion] = boton;
			this->hayNuevosBotones = true;
		}

	} else {
		throw PokerException("E", "Indice del array fuera de rango al acceder al los botones de un panel.");
	}
}

list<Boton*> Panel::getBotones(){

	if (this->hayNuevosBotones) {

		
		for (list<Boton*>::iterator it = this->listaBotones.begin(); it != this->listaBotones.end(); it++) {
			delete(*it);
		}
		
		this->listaBotones.clear();

		for (int i=0; i < MAX_CANT_BOTONES; i++) {
			if (this->botones[i] != NULL){

				Boton* copiaBoton = new Boton(this->botones[i]);
				this->listaBotones.push_back(copiaBoton);
			}
		}

		this->hayNuevosBotones = false;
	}
	return this->listaBotones;
}



void Panel::dibujarSobreSup(SDL_Surface* superficie){

	if (this->hayNuevosBotones) {
		this->configurarBotones();
		//this->hayNuevosBotones = false;
	}

	//dibuja el panel
	SDL_Rect* offsetBorde = this->getOffsetRect();
	offsetBorde->w = this->getAncho();
	offsetBorde->h = this->getAlto();
	SDL_FillRect(superficie, offsetBorde, this->borde->toUint32(superficie));
	SDL_Rect* offset = new SDL_Rect();
	offset->x = offsetBorde->x + 1;
	offset->y = offsetBorde->y + 1;
	offset->w = offsetBorde->w - 2;
	offset->h = offsetBorde->h - 2;
	SDL_FillRect(superficie, offset, this->fondo->toUint32(superficie));


	/*
	for (list<ElementoGrafico*>::iterator it = this->elementos.begin();
		it != this->elementos.end(); it++) {
			(*it)->dibujar(superficie);
	}
	*/

	for (int i=0; i < MAX_CANT_BOTONES; i++) {
		if (this->botones[i] != NULL){
			this->botones[i]->dibujar(superficie);
		}
	}

	delete(offset);
}

void Panel::configurarBotones()
{
	/*
	//agrega botones a la pantalla
	string textoDejarMesa = RecursosAplicacion::getClienteConfigProperties()->get("cliente.tema.default.boton.texto.dejarmesa");
	this->btDejarMesa = new Boton(textoDejarMesa);
	this->agregarElementoGrafico(this->btDejarMesa);

	string textoNoIr = RecursosAplicacion::getClienteConfigProperties()->get("cliente.tema.default.boton.texto.noir");
	this->btNoIr = new Boton(textoNoIr);
	this->agregarElementoGrafico(this->btNoIr);

	string textoIgualar = RecursosAplicacion::getClienteConfigProperties()->get("cliente.tema.default.boton.texto.igualar");
	this->btIgualar = new Boton(textoIgualar);
	this->agregarElementoGrafico(this->btIgualar);

	string textoSubir = RecursosAplicacion::getClienteConfigProperties()->get("cliente.tema.default.boton.texto.subir");
	this->btSubir = new Boton(textoSubir);
	this->agregarElementoGrafico(this->btSubir);
	*/

	string textoText = "";
	this->textBox = new TextBox(textoText);
	this->textBox->setAlto(20);
	this->textBox->setAncho(70);
	this->agregarElementoGrafico(this->textBox);

	int anchoPanel = PANEL_SEPARACION_BOTONES_H * 7;
	int altoPanel = 0;

	for (int i=0; i < MAX_CANT_BOTONES; i++) {
		if (this->botones[i] != NULL){
			anchoPanel += this->botones[i]->getAncho();
			altoPanel = this->botones[i]->getAlto();
		}
	}

	//setea la posicion y el tamanio del panel
	this->setAncho(anchoPanel);
	this->setAlto(altoPanel + PANEL_SEPARACION_BOTONES_V * 2);

	this->posX = (int)((ServiciosGraficos::getAnchoVentana() - this->getAncho()) / 2);
	this->posY = ServiciosGraficos::getAltoVentana() - this->getAlto();


	// se setea la posicion y tamanio de cada boton
	SDL_Rect* offsetMenu = this->getOffsetRect();
	int offsetXAcum = PANEL_SEPARACION_BOTONES_H*2;

	for (int i=0; i < MAX_CANT_BOTONES; i++) {
		if (this->botones[i] != NULL){

			this->botones[i]->setPosX(offsetMenu->x + offsetXAcum);
			this->botones[i]->setPosY(offsetMenu->y + PANEL_SEPARACION_BOTONES_V);

			offsetXAcum += this->botones[i]->getAncho() + PANEL_SEPARACION_BOTONES_H;
		}
	}

	/*
	this->textBox->setPosX(offsetMenu->x + this->btDejarMesa->getAncho() 
		+ this->btNoIr->getAncho() + this->btIgualar->getAncho() + this->btSubir->getAncho() + PANEL_SEPARACION_BOTONES_H*6);
	this->textBox->setPosY(offsetMenu->y + (this->getAlto() - this->textBox->getAlto())/2);
	*/
}

ElementoGrafico* Panel::getElementoPorId(string id){

	for (int i=0; i < MAX_CANT_BOTONES; i++) {
		if (this->botones[i] != NULL){
			
			if (MensajesUtil::sonIguales(this->botones[i]->getId(), id)){
				return this->botones[i];
			}
		}
	}

	return NULL;
}

/*
Boton* Panel::getBotonDejarMesa() {
	return this->btDejarMesa;
}

Boton* Panel::getBotonNoIr() {
	return this->btNoIr;
}

Boton* Panel::getBotonIgualar() {
	return this->btIgualar;
}

Boton* Panel::getBotonSubir() {
	return this->btSubir;
}
*/
TextBox* Panel::getTextBox() {
	return this->textBox;
}
