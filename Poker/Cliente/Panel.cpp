#include "Panel.h"
#include "ServiciosGraficos.h"
#include "RecursosCliente.h"
#include "PokerException.h"
#include "MensajesUtil.h"

Panel::Panel(void)
{
	//seteamos el fondo del menu de operaciones
	this->borde = new Color(RecursosCliente::getConfig()->get("cliente.tema.default.menu.borde"));
	this->fondo = new Color(RecursosCliente::getConfig()->get("cliente.tema.default.menu.fondo"));

	for (int i=0; i < MAX_CANT_COMPONENTES; i++) {
		this->componentes[i] = NULL;
	}

	this->hayNuevosComponentes = true;
}

Panel::~Panel(void)
{
	delete(borde);
	delete(fondo);

	for (int i=0; i < MAX_CANT_COMPONENTES; i++) {
		if (this->componentes[i] != NULL){
			delete (this->componentes[i]);
		}
	}
}

void Panel::agregarComponente(ComponentePanel* componente, int posicion){

	if (posicion < MAX_CANT_COMPONENTES) {

		if (this->componentes[posicion] == NULL || !this->componentes[posicion]->equals(componente)) {

			if (this->componentes[posicion] != NULL) {
				delete(this->componentes[posicion]);
			}

			this->componentes[posicion] = componente;
			componente->setPanel(this);
			this->hayNuevosComponentes = true;
		}

	} else {
		throw PokerException("E", "Indice del array fuera de rango al acceder al los componentes de un panel.");
	}
}

ComponentePanel** Panel::getComponentes(){

	return this->componentes;
}



void Panel::dibujarSobreSup(SDL_Surface* superficie){

	if (this->hayNuevosComponentes) {
		this->configurar();
		this->hayNuevosComponentes = false;
	}

	//dibuja el panel
	SDL_Rect* offsetBorde = this->getContornoConOffset();
	if (this->fondo != NULL) {
		SDL_FillRect(superficie, offsetBorde, this->fondo->toUint32(superficie));
	}
	if (this->borde != NULL) {
		ServiciosGraficos::dibujarContorno(superficie, offsetBorde, this->borde);
	}


	for (int i=0; i < MAX_CANT_COMPONENTES; i++) {
		if (this->componentes[i] != NULL){
			this->componentes[i]->setHayCambios(true);
			this->componentes[i]->dibujar(superficie);
		}
	}
}

void Panel::configurar()
{
	int anchoPanel = PANEL_SEPARACION_BOTONES_H * 3;
	int altoPanel = 0;

	for (int i=0; i < MAX_CANT_COMPONENTES; i++) {
		if (this->componentes[i] != NULL){

			if (this->componentes[i]->getAncho() == 0) {
				this->componentes[i]->setAncho(ANCHO_DEFAULT_COMPONENTE);
			}

			anchoPanel += this->componentes[i]->getAncho() + PANEL_SEPARACION_BOTONES_H;
			if (altoPanel == 0) {
				altoPanel = this->componentes[i]->getAlto();
			}

			if (this->componentes[i]->getAlto() <= 0) {
				this->componentes[i]->setAlto(altoPanel - CORRECCION_ALTURA_COMPONENTE);
			}
		}
	}

	//setea la posicion y el tamanio del panel
	this->setAncho(anchoPanel);
	this->setAlto(altoPanel + PANEL_SEPARACION_BOTONES_V * 2);

	this->posX = (int)((ServiciosGraficos::getAnchoVentana() - this->getAncho()) / 2);
	this->posY = ServiciosGraficos::getAltoVentana() - this->getAlto();


	// se setea la posicion y tamanio de cada componente
	SDL_Rect* offsetMenu = this->getOffsetRect();
	int offsetXAcum = PANEL_SEPARACION_BOTONES_H*2;

	for (int i=0; i < MAX_CANT_COMPONENTES; i++) {
		if (this->componentes[i] != NULL){

			this->componentes[i]->setPosX(offsetMenu->x + offsetXAcum);
			this->componentes[i]->setPosY(offsetMenu->y 
				+ (int)((this->getAlto() - this->componentes[i]->getAlto()) / 2));

			offsetXAcum += this->componentes[i]->getAncho() + PANEL_SEPARACION_BOTONES_H;
		}
	}
}

ElementoGrafico* Panel::getElementoPorId(string id){

	for (int i=0; i < MAX_CANT_COMPONENTES; i++) {
		if (this->componentes[i] != NULL){
			
			if (MensajesUtil::sonIguales(this->componentes[i]->getId(), id)){
				return this->componentes[i];
			}
		}
	}

	return NULL;
}

void Panel::setFondo(Color* color){
	if (this->fondo != NULL) {
		delete(this->fondo);
	}
	this->fondo = color;
	this->hayCambios = true;
}

void Panel::setBorde(Color* color){
	if (this->borde != NULL) {
		delete(this->borde);
	}
	this->borde = color;
	this->hayCambios = true;
}

Color* Panel::getFondo() {
	return this->fondo;
}
