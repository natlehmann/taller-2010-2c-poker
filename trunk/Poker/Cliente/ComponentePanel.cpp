#include "ComponentePanel.h"
#include "ServiciosGraficos.h"
#include "MensajesUtil.h"
#include "Panel.h"


ComponentePanel::ComponentePanel(string texto) {

	this->setTexto(texto);
	this->ajustarAlTexto = true;
	this->habilitado = false;
	this->idOperacion = "";
	this->panel = NULL;
	this->idComponentePanelRelacionado = "";
}

ComponentePanel::~ComponentePanel(void)
{
	if (this->fuente != NULL) {
		delete(this->fuente);
	}
}

void ComponentePanel::setearFuente() {

	int tamanioFuente = this->tamanioFuenteMax;
	if (ServiciosGraficos::getAnchoVentana() < MAXIMO_ANCHO_PANTALLA_PROP_TXT) {
		tamanioFuente = (int)(ServiciosGraficos::getAnchoVentana() * this->tamanioFuenteMax
			/ MAXIMO_ANCHO_PANTALLA_PROP_TXT);
	}

	this->fuente = new Fuente(this->colorFuente, tamanioFuente, this->estiloFuente);
}


bool ComponentePanel::estaSobre()
{
	int checkx,checky;
	SDL_GetMouseState(&checkx, &checky);
	if(checkx >= this->posX && checkx <= (this->posX + this->ancho) && checky >= this->posY && checky <= (this->posY + this->alto))
		return true;

	return false;
}

bool ComponentePanel::esClickDerecho()
{
	if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT))
		return true;

	return false;
}

bool ComponentePanel::esClickIzquierdo()
{
	if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
		return true;

	return false;
}

string ComponentePanel::getTexto() {
	return this->texto;
}
void ComponentePanel::setTexto(string texto) {
	if (!MensajesUtil::sonIguales(this->texto, texto)) {
		this->texto = texto;
		this->hayCambios = true;
	}
}

bool ComponentePanel::isHabilitado(){
	return this->habilitado;
}

void ComponentePanel::setHabilitado(bool habilitado){
	if (this->habilitado != habilitado) {
		this->habilitado = habilitado;
		this->hayCambios = true;
	}
}

string ComponentePanel::getIdOperacion(){
	return this->idOperacion;
}

void ComponentePanel::setIdOperacion(string idOperacion){
	if (!MensajesUtil::sonIguales(this->getIdOperacion(), idOperacion)) {
		this->idOperacion = idOperacion;
		this->hayCambios = true;
	}
}

string ComponentePanel::getIdComponentePanelRelacionado(){
	return this->idComponentePanelRelacionado;
}

void ComponentePanel::setIdComponentePanelRelacionado(string idComponentePanelRelacionado){
	if (!MensajesUtil::sonIguales(this->getIdComponentePanelRelacionado(), idComponentePanelRelacionado)) {
		this->idComponentePanelRelacionado = idComponentePanelRelacionado;
		this->hayCambios = true;
	}
}

void ComponentePanel::setPanel(Panel* panel) {
	this->panel = panel;
}

