#include "Panel.h"
#include "ServiciosGraficos.h"
#include "RecursosAplicacion.h"

Panel::Panel(void)
{
	//setamos el fondo del menu de operaciones
	this->borde = new Color(RecursosAplicacion::getClienteConfigProperties()->get("cliente.tema.default.menu.borde"));
	this->fondo = new Color(RecursosAplicacion::getClienteConfigProperties()->get("cliente.tema.default.menu.fondo"));

	//agrega botones a la pantalla
	this->configurarBotones();
}

Panel::~Panel(void)
{
	delete(borde);
	delete(fondo);
}

void Panel::dibujarSobreSup(SDL_Surface* superficie){

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


	for (list<ElementoGrafico*>::iterator it = this->elementos.begin();
		it != this->elementos.end(); it++) {
			(*it)->dibujar(superficie);
	}

	delete(offset);
}

void Panel::configurarBotones()
{
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

	string textoText = "";
	this->textBox = new TextBox(textoText);
	this->textBox->setAlto(20);
	this->textBox->setAncho(70);
	this->agregarElementoGrafico(this->textBox);

	//setea la posicion, alineada, separacion igual entre todos
	this->setAncho(this->btDejarMesa->getAncho() + this->btNoIr->getAncho() 
		+ this->btIgualar->getAncho() + this->btSubir->getAncho() 
		+ this->textBox->getAncho() + PANEL_SEPARACION_BOTONES_H * 7);

	this->setAlto(this->btIgualar->getAlto() + PANEL_SEPARACION_BOTONES_V * 2);

	this->posX = (int)((ServiciosGraficos::getAnchoVentana() - this->getAncho()) / 2);
	this->posY = ServiciosGraficos::getAltoVentana() - this->getAlto();


	SDL_Rect* offsetMenu = this->getOffsetRect();
	this->btDejarMesa->setPosX(offsetMenu->x + PANEL_SEPARACION_BOTONES_H*2);
	this->btDejarMesa->setPosY(offsetMenu->y + PANEL_SEPARACION_BOTONES_V);

	this->btNoIr->setPosX(offsetMenu->x + this->btDejarMesa->getAncho() + PANEL_SEPARACION_BOTONES_H*3);
	this->btNoIr->setPosY(offsetMenu->y + PANEL_SEPARACION_BOTONES_V);

	this->btIgualar->setPosX(offsetMenu->x + this->btDejarMesa->getAncho() 
		+ this->btNoIr->getAncho() + PANEL_SEPARACION_BOTONES_H*4);
	this->btIgualar->setPosY(offsetMenu->y + PANEL_SEPARACION_BOTONES_V);

	this->btSubir->setPosX(offsetMenu->x + this->btDejarMesa->getAncho() 
		+ this->btNoIr->getAncho() + this->btIgualar->getAncho() + PANEL_SEPARACION_BOTONES_H*5);
	this->btSubir->setPosY(offsetMenu->y + PANEL_SEPARACION_BOTONES_V);

	this->textBox->setPosX(offsetMenu->x + this->btDejarMesa->getAncho() 
		+ this->btNoIr->getAncho() + this->btIgualar->getAncho() + this->btSubir->getAncho() + PANEL_SEPARACION_BOTONES_H*6);
	this->textBox->setPosY(offsetMenu->y + (this->getAlto() - this->textBox->getAlto())/2);
}

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

TextBox* Panel::getTextBox() {
	return this->textBox;
}