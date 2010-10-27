#include "Panel.h"
#include "ServiciosGraficos.h"
#include "RecursosCliente.h"
#include "PokerException.h"
#include "MensajesUtil.h"

Panel::Panel(void)
{
	//setamos el fondo del menu de operaciones
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

	for (list<ComponentePanel*>::iterator it = this->listaComponentes.begin(); it != this->listaComponentes.end(); it++) {
		delete(*it);
	}

	this->listaComponentes.clear();
}

void Panel::agregarComponente(ComponentePanel* componente, int posicion){

	if (posicion < MAX_CANT_COMPONENTES) {

		if (this->componentes[posicion] == NULL || !this->componentes[posicion]->equals(componente)) {

			if (this->componentes[posicion] != NULL) {
				delete(this->componentes[posicion]);
			}

			this->componentes[posicion] = componente;
			this->hayNuevosComponentes = true;
		}

	} else {
		throw PokerException("E", "Indice del array fuera de rango al acceder al los componentes de un panel.");
	}
}

list<ComponentePanel*> Panel::getComponentes(){

	if (this->hayNuevosComponentes) {

		
		for (list<ComponentePanel*>::iterator it = this->listaComponentes.begin(); it != this->listaComponentes.end(); it++) {
			delete(*it);
		}
		
		this->listaComponentes.clear();

		for (int i=0; i < MAX_CANT_COMPONENTES; i++) {
			if (this->componentes[i] != NULL){

				ComponentePanel* copia = this->componentes[i]->clonar();
				this->listaComponentes.push_back(copia);
			}
		}

		this->hayNuevosComponentes = false;
	}
	return this->listaComponentes;
}



void Panel::dibujarSobreSup(SDL_Surface* superficie){

	if (this->hayNuevosComponentes) {
		this->configurar();
	}

	//dibuja el panel
	SDL_Rect* offsetBorde = this->getContornoConOffset();
	SDL_FillRect(superficie, offsetBorde, this->borde->toUint32(superficie));
	SDL_Rect* offset = new SDL_Rect();
	offset->x = offsetBorde->x + 1;
	offset->y = offsetBorde->y + 1;
	offset->w = offsetBorde->w - 2;
	offset->h = offsetBorde->h - 2;
	SDL_FillRect(superficie, offset, this->fondo->toUint32(superficie));


	for (int i=0; i < MAX_CANT_COMPONENTES; i++) {
		if (this->componentes[i] != NULL){
			this->componentes[i]->dibujar(superficie);
		}
	}

	delete(offset);
}

void Panel::configurar()
{
	int anchoPanel = PANEL_SEPARACION_BOTONES_H * 3;
	int altoPanel = 0;

	for (int i=0; i < MAX_CANT_COMPONENTES; i++) {
		if (this->componentes[i] != NULL){
			anchoPanel += this->componentes[i]->getAncho() + PANEL_SEPARACION_BOTONES_H;
			if (altoPanel == 0) {
				altoPanel = this->componentes[i]->getAlto();
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
			this->componentes[i]->setPosY(offsetMenu->y + PANEL_SEPARACION_BOTONES_V);

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

