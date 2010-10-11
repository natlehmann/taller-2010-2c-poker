#include "Panel.h"
#include "ServiciosGraficos.h"
#include "RecursosAplicacion.h"

Panel::Panel(void)
{
	this->setAncho(ServiciosGraficos::getTamanioCeldaHoriz()*3);
	this->setAlto(ServiciosGraficos::getTamanioCeldaVert()/5);
	this->posX = ServiciosGraficos::getTamanioCeldaHoriz() + ServiciosGraficos::getBordeIzquierdo();
	this->posY = ServiciosGraficos::getAltoVentana() - ServiciosGraficos::getBordeInferior() - this->getAlto();

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

	//setea la posicion, alineada, separacion igual entre todos
	int separacionH = (this->ancho - (btDejarMesa->getAncho() + btNoIr->getAncho() + btIgualar->getAncho() + btSubir->getAncho()))/5;
	int separacionV = (this->alto - btDejarMesa->getAlto())/2;

	SDL_Rect* offsetMenu = this->getOffsetRect();
	this->btDejarMesa->setPosX(offsetMenu->x + separacionH);
	this->btDejarMesa->setPosY(offsetMenu->y + separacionV);
	this->btNoIr->setPosX(offsetMenu->x + this->btDejarMesa->getAncho() + separacionH*2);
	this->btNoIr->setPosY(offsetMenu->y + separacionV);
	this->btIgualar->setPosX(offsetMenu->x + this->btDejarMesa->getAncho() + this->btNoIr->getAncho() + separacionH*3);
	this->btIgualar->setPosY(offsetMenu->y + separacionV);
	this->btSubir->setPosX(offsetMenu->x + this->btDejarMesa->getAncho() + this->btNoIr->getAncho() + this->btIgualar->getAncho() + separacionH*4);
	this->btSubir->setPosY(offsetMenu->y + separacionV);
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