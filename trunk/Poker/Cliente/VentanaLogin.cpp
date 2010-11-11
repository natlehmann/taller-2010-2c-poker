#include "VentanaLogin.h"
#include "RecursosCliente.h"
#include "MensajesUtil.h"
#include "DatosInvalidosException.h"
#include "UtilTiposDatos.h"
#include "UICliente.h"
#include "UIException.h"
#include "ComponentePanel.h"
#include "FabricaOperacionesCliente.h"
#include "OpUIClienteLogin.h"
#include "ServiciosGraficos.h"
#include <typeinfo.h>
#include <cstdlib>

VentanaLogin::VentanaLogin(void) {

	UICliente::iniciarSDL();

	this->id = "";
	this->posX = 0;
	this->posY = 0;
	this->offset = new SDL_Rect();
	this->contorno = new SDL_Rect();
	this->contornoConOffset = new SDL_Rect();
	this->conectado = false;
	this->cancelado = false;
	this->nuevo = false;
	
	string configPantalla = RecursosCliente::getConfig()->get("cliente.configuracion.pantalla");
	list<string> medidas = MensajesUtil::split(configPantalla, "x");

	if (medidas.size() != 2) {
		throw DatosInvalidosException("La configuracion de pantalla esta incorrectamente seteada en el archivo 'config.ini'.", "V");
	}

	int ancho = UtilTiposDatos::getEntero(medidas.front());
	int alto = UtilTiposDatos::getEntero(medidas.back());

	if (ancho < 0 || alto < 0) {
		throw DatosInvalidosException("El ancho o el alto de la configuracion de pantalla en el archivo 'config.ini' no es un numero entero.", "V");
	}

	this->setAncho(ancho/2);
	this->setAlto(alto/2);
	this->altoFila = this->getAlto()/20;
	this->anchoColumna = this->getAncho()/20;

	this->contorno->x = 0;
	this->contorno->y = 0;
	this->contorno->w = this->getAncho();
	this->contorno->h = this->getAlto();
	
	this->offset->x = this->anchoColumna*2;
	this->offset->y = this->altoFila*2 ;
	this->offset->x = this->getAncho() - this->anchoColumna*2;
	this->offset->y = this->getAlto() - this->altoFila*2;

	this->pantalla = SDL_SetVideoMode(this->ancho, this->alto, RESOLUCION_PANTALLA, SDL_SWSURFACE);

	if (this->pantalla == NULL) {
		throw UIException("No se pudo inicializar la ventana de la aplicacion.","E");
	}

	SDL_WM_SetCaption(RecursosCliente::getConfig()->get("cliente.configuracion.mensajeConfiguracion").c_str(), NULL); 
	
	this->fondo = new Color(RecursosCliente::getConfig()->get("cliente.tema.default.menu.fondo"));
	SDL_FillRect(pantalla, contorno, this->fondo->toUint32(pantalla));

	this->configurarControles();
	this->hayCambios = true;
}

VentanaLogin::~VentanaLogin(void)
{
	for (list<ElementoGrafico*>::iterator it = this->elementos.begin();
		it != this->elementos.end(); it++) {
			delete(*it);
	}
	this->elementos.clear();

	for (list<ComponentePanel*>::iterator it = this->componentes.begin();
		it != this->componentes.end(); it++) {
			delete(*it);
	}
	this->componentes.clear();

	delete (this->offset);
	delete (this->contorno);

}


void VentanaLogin::configurarControles() {

	Etiqueta* etUsuario = new Etiqueta("Usuario:");
	etUsuario->setPosX(this->anchoColumna*2);
	etUsuario->setPosY(this->altoFila*2);
	etUsuario->setAlto(this->altoFila*3);
	etUsuario->setAncho(this->anchoColumna*6);
	etUsuario->setFondo(new Color(fondo->getRed(), fondo->getGreen(), fondo->getBlue()));
	this->agregarElementoGrafico(etUsuario);

	txUsuario = new TextBox("");
	txUsuario->setPosX(this->anchoColumna*10);
	txUsuario->setPosY(this->altoFila*2);
	txUsuario->setAlto(this->altoFila*3);
	txUsuario->setAncho(this->anchoColumna*8);
	txUsuario->setHabilitado(true);
	this->agregarComponentePanel(txUsuario);

	Etiqueta* etPassword = new Etiqueta("Password:");
	etPassword->setPosX(this->anchoColumna*2);
	etPassword->setPosY(this->altoFila*6);
	etPassword->setAlto(this->altoFila*3);
	etPassword->setAncho(this->anchoColumna*6);
	etPassword->setFondo(new Color(fondo->getRed(), fondo->getGreen(), fondo->getBlue()));
	this->agregarElementoGrafico(etPassword);

	txPassword = new TextBox("");
	txPassword->setPosX(this->anchoColumna*10);
	txPassword->setPosY(this->altoFila*6);
	txPassword->setAlto(this->altoFila*3);
	txPassword->setAncho(this->anchoColumna*8);
	txPassword->setHabilitado(true);
	txPassword->setTipoPassword(true);
	this->agregarComponentePanel(txPassword);

	Boton* botonOk = new Boton("OK");
	botonOk->setId("botonOk");
	botonOk->setPosX(this->anchoColumna*4);
	botonOk->setPosY(this->altoFila*14);
	botonOk->setHabilitado(true);
	this->agregarComponentePanel(botonOk);

	Boton* botonNuevo = new Boton("Nuevo");
	botonNuevo->setId("botonNuevo");
	botonNuevo->setPosX(this->anchoColumna*8);
	botonNuevo->setPosY(this->altoFila*14);
	botonNuevo->setHabilitado(true);
	this->agregarComponentePanel(botonNuevo);

	Boton* botonCancel = new Boton("Cancel");
	botonCancel->setId("botonCancel");
	botonCancel->setPosX(this->anchoColumna*13);
	botonCancel->setPosY(this->altoFila*14);
	botonCancel->setHabilitado(true);
	this->agregarComponentePanel(botonCancel);

	mensajeError = new Etiqueta("");
	mensajeError->setPosX(this->anchoColumna*2);
	mensajeError->setPosY(this->altoFila*10);
	mensajeError->setAlto(this->altoFila*4);
	mensajeError->setAncho(this->anchoColumna*6);
	mensajeError->setFondo(new Color(fondo->getRed(), fondo->getGreen(), fondo->getBlue()));
	mensajeError->setVisible(false);
	this->agregarElementoGrafico(mensajeError);

}

void VentanaLogin::iniciar() {

	//dibuja los controles en la pantalla
	this->dibujar(NULL);

	bool listo = false;
	SDL_Event event;

	while(!listo) {
		while(SDL_WaitEvent(&event) && !listo) {
			listo = this->manejarEventos(&event);

			if( (event.type == SDL_QUIT) || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) ){
				SDL_Quit();
                listo = true;
            }

		}
	}

}

void VentanaLogin::mostrarMensaje(string mensaje){
	if (this->mensajeError != NULL) {
		this->mensajeError->setMensaje(mensaje);
		this->mensajeError->setVisible(true);
		this->mensajeError->dibujar(this->pantalla);
	}
}
void VentanaLogin::agregarElementoGrafico(ElementoGrafico* elemento) {
	this->elementos.push_back(elemento);
	elemento->setVentana(this);
}

void VentanaLogin::agregarComponentePanel(ComponentePanel* componente) {
	this->componentes.push_back(componente);
	componente->setVentana(this);
}

bool VentanaLogin::manejarEventos(SDL_Event* event){


	string controlId = "";
	bool refrescar = false;
	bool finalizar = false;
	if (this->componentes.size() > 0) {

		switch (event->type){	
			case (SDL_KEYDOWN):
				for (list<ComponentePanel*>::iterator it = this->componentes.begin();
					it != this->componentes.end(); it++) {
						refrescar = refrescar || (*it)->checkWrite(this->pantalla, event, 1) ;
				}
				break;
			case (SDL_MOUSEMOTION):
				for (list<ComponentePanel*>::iterator it = this->componentes.begin();
					it != this->componentes.end(); it++) {
						refrescar = refrescar || (*it)->checkOver(this->pantalla);
				}
				break;
			case (SDL_MOUSEBUTTONDOWN):

				for (list<ComponentePanel*>::iterator it = this->componentes.begin();
					it != this->componentes.end(); it++) {

					

					if ((*it)->checkClick(this->pantalla)) {
						controlId = (*it)->getId();
					}

					if ((*it)->getHayCambios()) {
						refrescar = refrescar || true;

					}
				}
				break;		
			case (SDL_MOUSEBUTTONUP):
				for (list<ComponentePanel*>::iterator it = this->componentes.begin();
					it != this->componentes.end(); it++) {
						(*it)->checkOver(this->pantalla);
						
						if ((*it)->getHayCambios()) 
							refrescar = refrescar || true;
				}
				break;	
			case (SDL_USEREVENT):
					refrescar = true;
				break;	

		}

		if (refrescar)
			this->refrescar(this->pantalla);

		if (controlId.length() > 0)
			finalizar = this->ejecutarEvento(controlId);

		return finalizar;
	}

}
void VentanaLogin::lanzarEvento(int codigoEvento) {
	SDL_Event event;

	event.type = SDL_USEREVENT;
	event.user.code = codigoEvento;
	event.user.data1 = 0;
	event.user.data2 = 0;
	SDL_PushEvent(&event);
}

bool VentanaLogin::ejecutarEvento(string controlId){

	if (MensajesUtil::sonIguales(controlId, "botonOk"))
	{
		if (txPassword->getTexto().length() == 0 || txUsuario->getTexto().length() == 0)
		{
			mostrarMensaje("Complete user y password e intente nuevamente.");
			lanzarEvento(100);
			return false;
		}
		else
		{
			FabricaOperacionesCliente fab;
			OperacionUICliente* operacion = NULL;

			vector<string> parametros;
			parametros.push_back(txUsuario->getTexto());
			parametros.push_back(txPassword->getTexto());
			parametros.push_back("S");
			parametros.push_back("N");
			operacion = fab.newOperacion("OpUIClienteLogin", parametros);

			if (operacion->ejecutarAccion(NULL))
			{
				this->conectado = true;
				SDL_Quit();
				return true;		
			}
			else
			{
				mostrarMensaje(operacion->getError());
				lanzarEvento(100);
				return false;
			}

			delete(operacion);
		}
	}
	else if (MensajesUtil::sonIguales(controlId, "botonNuevo"))
	{
		this->nuevo = true;
		SDL_Quit();
		return true;
	}
	else if (MensajesUtil::sonIguales(controlId, "botonCancel"))
	{
		this->cancelado = true;
		SDL_Quit();
		return true;
	}
}
void VentanaLogin::refrescar(SDL_Surface* superficie) {
		if(SDL_Flip(superficie) == -1) { 
		throw UIException("Error al redibujar la pantalla completa.","E");
	} 
}
void VentanaLogin::dibujarSobreSup(SDL_Surface* superficie){

	if (this->hayCambios) {

		for (list<ElementoGrafico*>::iterator it = this->elementos.begin();
			it != this->elementos.end(); it++) {

				(*it)->dibujar(this->pantalla);
		}

		for (list<ComponentePanel*>::iterator it = this->componentes.begin();
			it != this->componentes.end(); it++) {

				(*it)->dibujar(this->pantalla);
		}

		//refresca la pantalla
		this->refrescar(this->pantalla);

		this->hayCambios = false;
	}
}
void VentanaLogin::dibujar(SDL_Surface* superficie){

	if (this->hayCambios) {
		if (superficie != NULL) {
			this->dibujarSobreSup(superficie);

		} else {
			this->dibujarSobreSup(this->pantalla);
		}
		this->hayCambios = false;
	}
}
bool VentanaLogin::getConectado() {
	return this->conectado;
}
bool VentanaLogin::getCancelado() {
	return this->cancelado;
}
bool VentanaLogin::getNuevo() {
	return this->nuevo;
}