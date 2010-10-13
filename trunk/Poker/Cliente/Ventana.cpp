#include "Ventana.h"
#include "RecursosAplicacion.h"
#include "MensajesUtil.h"
#include "DatosInvalidosException.h"
#include "UtilTiposDatos.h"
#include "UIException.h"

Ventana::Ventana(void) {

	string configPantalla = RecursosAplicacion::getClienteConfigProperties()->get(
		"cliente.configuracion.pantalla");
	list<string> medidas = MensajesUtil::split(configPantalla, "x");

	if (medidas.size() != 2) {
		throw DatosInvalidosException(
			"La configuracion de pantalla esta incorrectamente seteada en el archivo 'config.ini'.", "V");
	}

	int ancho = UtilTiposDatos::getEntero(medidas.front());
	int alto = UtilTiposDatos::getEntero(medidas.back());

	if (ancho < 0 || alto < 0) {
		throw DatosInvalidosException(
			"El ancho o el alto de la configuracion de pantalla en el archivo 'config.ini' no es un numero entero.", "V");
	}

	this->setAncho(ancho);
	this->setAlto(alto);

	this->pantalla = SDL_SetVideoMode(this->ancho, this->alto, RESOLUCION_PANTALLA, SDL_SWSURFACE);

	if (this->pantalla == NULL) {
		throw UIException("No se pudo inicializar la ventana de la aplicacion.","E");
	}

	SDL_WM_SetCaption(RecursosAplicacion::getClienteConfigProperties()->get(
		"cliente.configuracion.mensaje").c_str(), NULL); 

	this->panelComando = new Panel();
}

Ventana::~Ventana(void)
{
	if (this->panelComando != NULL) {
		delete(this->panelComando);
	}
}

void Ventana::dibujarSobreSup(SDL_Surface* superficie){

	for (list<ElementoGrafico*>::iterator it = this->elementos.begin();
		it != this->elementos.end(); it++) {

			(*it)->dibujar(this->pantalla);
	}

	//se genera el panel de comando
	panelComando->dibujar(this->pantalla);

	//refresca la pantalla
	this->refrescar(this->pantalla);

	// TODO: ACA SE LANZARIA EL PROCESAMIENTO DE EVENTOS
	bool listo = false;
	SDL_Event event;
	while(!listo) 
	{
        if(!SDL_WaitEvent(&event))
            continue;

		switch (event.type)
		{
		case (SDL_KEYDOWN):
			if (event.key.keysym.sym == SDLK_ESCAPE) 
				listo = true;
			break;
		case (SDL_MOUSEMOTION):
			this->panelComando->getBotonDejarMesa()->checkOver(this->pantalla);
			this->panelComando->getBotonIgualar()->checkOver(this->pantalla);
			this->panelComando->getBotonNoIr()->checkOver(this->pantalla);
			this->panelComando->getBotonSubir()->checkOver(this->pantalla);
			break;
		case (SDL_MOUSEBUTTONDOWN):
			if(this->panelComando->getBotonDejarMesa()->checkClick(this->pantalla))
			{
				//accion a realizar
			}
			else if(this->panelComando->getBotonIgualar()->checkClick(this->pantalla))
			{
				//accion a realizar
			}
			else if(this->panelComando->getBotonNoIr()->checkClick(this->pantalla))
			{
				//accion a realizar
			}				
			else if(this->panelComando->getBotonSubir()->checkClick(this->pantalla))
			{
				//accion a realizar
			}
			break;		
		case (SDL_MOUSEBUTTONUP):
			this->panelComando->getBotonDejarMesa()->checkOver(this->pantalla);
			this->panelComando->getBotonIgualar()->checkOver(this->pantalla);
			this->panelComando->getBotonNoIr()->checkOver(this->pantalla);
			this->panelComando->getBotonSubir()->checkOver(this->pantalla);
			break;		
		}
	}
}