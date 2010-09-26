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
}

Ventana::~Ventana(void)
{
}

void Ventana::dibujar(){
	// TODO: FALTA IMPLEMENTAR : ver como imprimimos el fondo (por separado o un elemento mas)

	for (list<ElementoGrafico*>::iterator it = this->elementos.begin();
		it != this->elementos.end(); it++) {
			(*it)->dibujar();

			SDL_BlitSurface((*it)->getSuperficie(), (*it)->getOffsetRect(), 
				this->pantalla, this->getOffsetRect()); 
	}

	if(SDL_Flip(this->pantalla) == -1) { 
		throw UIException("Error al redibujar la pantalla completa.","E");
	} 
}
