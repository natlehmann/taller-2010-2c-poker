#include "VentanaConfiguracion.h"
#include "RecursosCliente.h"
#include "MensajesUtil.h"
#include "DatosInvalidosException.h"
#include "UtilTiposDatos.h"
#include "UICliente.h"
#include "UIException.h"
#include "Timer.h"
#include "ComponentePanel.h"
#include "FabricaOperacionesCliente.h"
#include "ServiciosGraficos.h"
#include <typeinfo.h>
#include <cstdlib>

VentanaConfiguracion::VentanaConfiguracion(void) {

	UICliente::iniciarSDL();

	this->id = "";
	this->posX = 0;
	this->posY = 0;
	this->offset = new SDL_Rect();
	this->contorno = new SDL_Rect();
	this->contornoConOffset = new SDL_Rect();
	this->conectado = false;
	this->cancelado = false;
	
	this->altoFila = ServiciosGraficos::getAltoFilaVentanaSegundaria();
	this->anchoColumna = ServiciosGraficos::getAnchoColVentanaSegundaria();
	this->setAlto(this->altoFila*24);
	this->setAncho(this->anchoColumna*20);

	this->contorno->x = 0;
	this->contorno->y = 0;
	this->contorno->w = this->getAncho();
	this->contorno->h = this->getAlto();
	
	this->offset->x = this->anchoColumna*2;
	this->offset->y = this->altoFila*2 ;
	this->offset->x = this->getAncho() - this->anchoColumna*2;
	this->offset->y = this->getAlto() - this->altoFila*2;

	this->pantalla = SDL_SetVideoMode(this->ancho, this->alto, RESOLUCION_PANTALLA, SDL_SWSURFACE);
	ServiciosGraficos::initVideoInfo();

	if (this->pantalla == NULL) {
		throw UIException("No se pudo inicializar la ventana de la aplicacion.","E");
	}

	SDL_WM_SetCaption(RecursosCliente::getConfig()->get("cliente.configuracion.mensajeConfiguracion").c_str(), NULL); 
	
	this->fondo = new Color(RecursosCliente::getConfig()->get("cliente.tema.default.menu.fondo"));
	//SDL_FillRect(pantalla, contorno, this->fondo->toUint32(pantalla));

	this->imagenFondo = new Imagen("pantallaConfiguracion.bmp");
	this->imagenFondo->setAlto(this->getAlto());
	this->imagenFondo->setAncho(this->getAncho());
	this->imagenFondo->setPosX(0);
	this->imagenFondo->setPosY(0);
	this->agregarElementoGrafico(this->imagenFondo);

	this->configurarControles();
	this->hayCambios = true;
}

VentanaConfiguracion::~VentanaConfiguracion(void)
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


void VentanaConfiguracion::configurarControles() {

	string estilo = RecursosCliente::getConfig()->get("cliente.configuracion.fuentes") +
					RecursosCliente::getConfig()->get("cliente.tema.default.etiquetas.fuente.estilo") + ".ttf";

	Etiqueta* etiquetaIP = new Etiqueta("Direccion IP:");
	etiquetaIP->setPosX(this->anchoColumna*2);
	etiquetaIP->setAncho(this->anchoColumna*5);
	etiquetaIP->setPosY(this->altoFila*11);
	etiquetaIP->setAlto(this->altoFila*1);
	etiquetaIP->setFondo(NULL);
	if (ServiciosGraficos::getAnchoVentana() >= ANCHO_LIMITE_CORRECCION) {
		etiquetaIP->setFuente(new Fuente("255,255,255", 18, estilo));
	}
	this->agregarElementoGrafico(etiquetaIP);


	textboxIP = new TextBox("localhost");
	textboxIP->setPosX(this->anchoColumna*7);
	textboxIP->setAncho(this->anchoColumna*10);
	textboxIP->setPosY(this->altoFila*11);
	if (ServiciosGraficos::getAnchoVentana() >= ANCHO_LIMITE_CORRECCION) {
		textboxIP->setAlto(this->altoFila*1);
	} else {
		textboxIP->setAlto((int)(this->altoFila*1.5));
	}
	textboxIP->setHabilitado(true);
	this->agregarComponentePanel(textboxIP);


	Etiqueta* etiquetaPuerto = new Etiqueta("Puerto:");
	etiquetaPuerto->setPosX(this->anchoColumna*2);
	etiquetaPuerto->setAncho(this->anchoColumna*5);
	etiquetaPuerto->setPosY(this->altoFila*13);
	etiquetaPuerto->setAlto(this->altoFila*1);
	etiquetaPuerto->setFondo(NULL);
	if (ServiciosGraficos::getAnchoVentana() >= ANCHO_LIMITE_CORRECCION) {
		etiquetaPuerto->setFuente(new Fuente("255,255,255", 18, estilo));
	}
	this->agregarElementoGrafico(etiquetaPuerto);


	textboxPuerto = new TextBox("5000");
	textboxPuerto->setPosX(this->anchoColumna*7);
	textboxPuerto->setAncho(this->anchoColumna*10);
	textboxPuerto->setPosY(this->altoFila*13);
	if (ServiciosGraficos::getAnchoVentana() >= ANCHO_LIMITE_CORRECCION) {
		textboxPuerto->setAlto(this->altoFila*1);
	} else {
		textboxPuerto->setAlto((int)(this->altoFila*1.5));
	}
	textboxPuerto->setHabilitado(true);
	this->agregarComponentePanel(textboxPuerto);


	Boton* btConectar = new Boton("Conectar");
	btConectar->setId("btConectar");
	btConectar->setPosX(this->anchoColumna*7);
	btConectar->setPosY(this->altoFila*15);
	btConectar->setHabilitado(true);
	this->agregarComponentePanel(btConectar);
	

	Boton* btCancel = new Boton("Cancelar");
	btCancel->setId("btCancel");
	if (ServiciosGraficos::getAnchoVentana() >= ANCHO_LIMITE_CORRECCION) {
		btCancel->setPosX(this->anchoColumna*11);
	} else {
		btCancel->setPosX(this->anchoColumna*13);
	}
	btCancel->setPosY(this->altoFila*15);
	btCancel->setHabilitado(true);
	this->agregarComponentePanel(btCancel);

	mensaje = new Etiqueta("");
	mensaje->setPosX(0);
	mensaje->setAlineacionHorizontal(ALINEACION_HORIZ_CENTRO);
	mensaje->setAncho(this->ancho);
	mensaje->setPosY(this->alto - this->altoFila*2);
	mensaje->setAlto(this->altoFila*2);
	mensaje->setFondo(new Color(9,78,44));
	mensaje->setVisible(false);
	agregarElementoGrafico(this->mensaje);

}

void VentanaConfiguracion::iniciar() {

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

void VentanaConfiguracion::mostrarMensaje(string mensaje){
	if (this->mensaje != NULL) {
		if (mensaje.length() > 0)
		{
			this->mensaje->setMensaje(mensaje);
			this->mensaje->setVisible(true);
		}
		else
		{
			this->mensaje->setMensaje(" ");
			this->mensaje->setVisible(true);
		}
		this->mensaje->dibujar(this->pantalla);
	}
}
void VentanaConfiguracion::agregarElementoGrafico(ElementoGrafico* elemento) {
	this->elementos.push_back(elemento);
	elemento->setVentana(this);
}

void VentanaConfiguracion::agregarComponentePanel(ComponentePanel* componente) {
	this->componentes.push_back(componente);
	componente->setVentana(this);
}

bool VentanaConfiguracion::manejarEventos(SDL_Event* event){


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

		if (controlId.length() > 0)
			refrescar = this->ejecutarPreEvento(controlId);

		if (refrescar)
			this->refrescar(this->pantalla);

		if (controlId.length() > 0)
			finalizar = this->ejecutarEvento(controlId);

	}
	
	return finalizar;
}
void VentanaConfiguracion::lanzarEvento(int codigoEvento) {
	SDL_Event event;

	event.type = SDL_USEREVENT;
	event.user.code = codigoEvento;
	event.user.data1 = 0;
	event.user.data2 = 0;
	SDL_PushEvent(&event);
}

bool VentanaConfiguracion::ejecutarPreEvento(string controlId){
	bool refrescar = false;
	if (MensajesUtil::sonIguales(controlId, "btConectar"))
	{
		mostrarMensaje("Espere, Intentando de conectar al Servidor...");
		refrescar = true;
	}

	return refrescar;
}
bool VentanaConfiguracion::ejecutarEvento(string controlId){

	bool finalizar = false;
	if (MensajesUtil::sonIguales(controlId, "btConectar"))
	{
		if (textboxIP->getTexto().length() == 0 || textboxPuerto->getTexto().length() == 0 
			|| !UtilTiposDatos::esEntero(textboxPuerto->getTexto()))
		{
			mostrarMensaje("Datos invalidos, corriga e intente nuevamente.");
			lanzarEvento(100);
		}
		else
		{
			if (UICliente::conectarServidor(textboxIP->getTexto(), UtilTiposDatos::getEntero(textboxPuerto->getTexto())))
			{
				this->conectado = true;
				SDL_Quit();
				finalizar = true;		
			}
			else
			{
				mostrarMensaje("Error al intentar coneccion con el servidor!");
				lanzarEvento(100);
			}
		}
	}
	else if (MensajesUtil::sonIguales(controlId, "btCancel"))
	{
		this->cancelado = true;
		SDL_Quit();
		finalizar = true;
	}

	return finalizar;
}
void VentanaConfiguracion::refrescar(SDL_Surface* superficie) {
		if(SDL_Flip(superficie) == -1) { 
		throw UIException("Error al redibujar la pantalla completa.","E");
	} 
}
void VentanaConfiguracion::dibujarSobreSup(SDL_Surface* superficie){

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
void VentanaConfiguracion::dibujar(SDL_Surface* superficie){

	if (this->hayCambios) {
		if (superficie != NULL) {
			this->dibujarSobreSup(superficie);

		} else {
			this->dibujarSobreSup(this->pantalla);
		}
		this->hayCambios = false;
	}
}
bool VentanaConfiguracion::getConectado() {
	return this->conectado;
}
bool VentanaConfiguracion::getCancelado() {
	return this->cancelado;
}
