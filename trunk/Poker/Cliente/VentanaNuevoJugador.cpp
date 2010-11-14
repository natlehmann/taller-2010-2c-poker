#include "VentanaNuevoJugador.h"
#include "RecursosCliente.h"
#include "MensajesUtil.h"
#include "DatosInvalidosException.h"
#include "UtilTiposDatos.h"
#include "UICliente.h"
#include "UIException.h"
#include "ComponentePanel.h"
#include "FabricaOperacionesCliente.h"
#include "OpUIClienteRegistrarJugador.h"
#include "ServiciosGraficos.h"
#include <typeinfo.h>
#include <cstdlib>

VentanaNuevoJugador::VentanaNuevoJugador(void) {

	UICliente::iniciarSDL();

	this->id = "";
	this->posX = 0;
	this->posY = 0;
	this->offset = new SDL_Rect();
	this->contorno = new SDL_Rect();
	this->contornoConOffset = new SDL_Rect();
	this->guardado = false;
	this->cancelado = false;
	
	this->altoFila = ServiciosGraficos::getAltoFilaVentanaSegundaria();
	this->anchoColumna = ServiciosGraficos::getAnchoColVentanaSegundaria();
	this->setAlto(this->altoFila*27);
	this->setAncho(this->anchoColumna*19);

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

	SDL_WM_SetCaption(RecursosCliente::getConfig()->get("cliente.configuracion.mensajeNuevoJugador").c_str(), NULL); 
	
	this->fondo = new Color(RecursosCliente::getConfig()->get("cliente.tema.default.menu.fondo"));
	SDL_FillRect(pantalla, contorno, this->fondo->toUint32(pantalla));

	this->configurarControles();
	this->hayCambios = true;
}

VentanaNuevoJugador::~VentanaNuevoJugador(void)
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


void VentanaNuevoJugador::configurarControles() {

	Etiqueta* etNombre = new Etiqueta("Nombre:");
	etNombre->setPosX(this->anchoColumna*2);
	etNombre->setAncho(this->anchoColumna*6);
	etNombre->setPosY(this->altoFila*1);
	etNombre->setAlto(this->altoFila*2);
	etNombre->setFondo(new Color(fondo->getRed(), fondo->getGreen(), fondo->getBlue()));
	this->agregarElementoGrafico(etNombre);

	txNombre = new TextBox("");
	txNombre->setPosX(this->anchoColumna*8);
	txNombre->setAncho(this->anchoColumna*10);
	txNombre->setPosY(this->altoFila*1);
	txNombre->setAlto(this->altoFila*2);
	txNombre->setHabilitado(true);
	this->agregarComponentePanel(txNombre);

	Etiqueta* etApellido = new Etiqueta("Apellido:");
	etApellido->setPosX(this->anchoColumna*2);
	etApellido->setAncho(this->anchoColumna*6);
	etApellido->setPosY(this->altoFila*5);
	etApellido->setAlto(this->altoFila*2);
	etApellido->setFondo(new Color(fondo->getRed(), fondo->getGreen(), fondo->getBlue()));
	this->agregarElementoGrafico(etApellido);

	txApellido = new TextBox("");
	txApellido->setPosX(this->anchoColumna*8);
	txApellido->setAncho(this->anchoColumna*10);
	txApellido->setPosY(this->altoFila*5);
	txApellido->setAlto(this->altoFila*2);
	txApellido->setHabilitado(true);
	this->agregarComponentePanel(txApellido);

	Etiqueta* etUsuario = new Etiqueta("Usuario:");
	etUsuario->setPosX(this->anchoColumna*2);
	etUsuario->setAncho(this->anchoColumna*6);
	etUsuario->setPosY(this->altoFila*9);
	etUsuario->setAlto(this->altoFila*2);
	etUsuario->setFondo(new Color(fondo->getRed(), fondo->getGreen(), fondo->getBlue()));
	this->agregarElementoGrafico(etUsuario);

	txUsuario = new TextBox("");
	txUsuario->setPosX(this->anchoColumna*8);
	txUsuario->setAncho(this->anchoColumna*10);
	txUsuario->setPosY(this->altoFila*9);
	txUsuario->setAlto(this->altoFila*2);
	txUsuario->setHabilitado(true);
	this->agregarComponentePanel(txUsuario);

	Etiqueta* etPassword = new Etiqueta("Password:");
	etPassword->setPosX(this->anchoColumna*2);
	etPassword->setAncho(this->anchoColumna*6);
	etPassword->setPosY(this->altoFila*13);
	etPassword->setAlto(this->altoFila*2);
	etPassword->setFondo(new Color(fondo->getRed(), fondo->getGreen(), fondo->getBlue()));
	this->agregarElementoGrafico(etPassword);

	txPassword = new TextBox("");
	txPassword->setPosX(this->anchoColumna*8);
	txPassword->setAncho(this->anchoColumna*10);
	txPassword->setPosY(this->altoFila*13);
	txPassword->setAlto(this->altoFila*2);
	txPassword->setHabilitado(true);
	txPassword->setTipoPassword(true);
	this->agregarComponentePanel(txPassword);

	Etiqueta* etConfPassword = new Etiqueta("C. Password:");
	etConfPassword->setPosX(this->anchoColumna*2);
	etConfPassword->setAncho(this->anchoColumna*6);
	etConfPassword->setPosY(this->altoFila*17);
	etConfPassword->setAlto(this->altoFila*2);
	etConfPassword->setFondo(new Color(fondo->getRed(), fondo->getGreen(), fondo->getBlue()));
	this->agregarElementoGrafico(etConfPassword);

	txConfirmPassword = new TextBox("");
	txConfirmPassword->setPosX(this->anchoColumna*8);
	txConfirmPassword->setAncho(this->anchoColumna*10);
	txConfirmPassword->setPosY(this->altoFila*17);
	txConfirmPassword->setAlto(this->altoFila*2);
	txConfirmPassword->setHabilitado(true);
	txConfirmPassword->setTipoPassword(true);
	this->agregarComponentePanel(txConfirmPassword);

	Boton* btGuardar = new Boton("Guardar");
	btGuardar->setId("btGuardar");
	btGuardar->setPosX(this->anchoColumna*5);
	btGuardar->setPosY(this->altoFila*23);
	btGuardar->setHabilitado(true);
	this->agregarComponentePanel(btGuardar);

	Boton* btCancel = new Boton("Salir");
	btCancel->setId("btCancel");
	btCancel->setPosX(this->anchoColumna*11);
	btCancel->setPosY(this->altoFila*23);
	btCancel->setHabilitado(true);
	this->agregarComponentePanel(btCancel);

	mensaje = new Etiqueta("");
	mensaje->setPosX(this->anchoColumna*1);
	mensaje->setAncho(this->anchoColumna*17);
	mensaje->setPosY(this->altoFila*20);
	mensaje->setAlto(this->altoFila*2);
	mensaje->setFondo(new Color(fondo->getRed(), fondo->getGreen(), fondo->getBlue()));
	mensaje->setVisible(false);
	this->agregarElementoGrafico(mensaje);

}

void VentanaNuevoJugador::iniciar() {

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

void VentanaNuevoJugador::mostrarMensaje(string mensaje){
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
void VentanaNuevoJugador::agregarElementoGrafico(ElementoGrafico* elemento) {
	this->elementos.push_back(elemento);
	elemento->setVentana(this);
}

void VentanaNuevoJugador::agregarComponentePanel(ComponentePanel* componente) {
	this->componentes.push_back(componente);
	componente->setVentana(this);
}

bool VentanaNuevoJugador::manejarEventos(SDL_Event* event){


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
void VentanaNuevoJugador::lanzarEvento(int codigoEvento) {
	SDL_Event event;

	event.type = SDL_USEREVENT;
	event.user.code = codigoEvento;
	event.user.data1 = 0;
	event.user.data2 = 0;
	SDL_PushEvent(&event);
}
bool VentanaNuevoJugador::ejecutarPreEvento(string controlId){

	if (MensajesUtil::sonIguales(controlId, "btGuardar"))
	{
		mostrarMensaje("Espere, Creando Nuevo Usuario...");
		lanzarEvento(100);
		return true;
	}

	return false;
}
bool VentanaNuevoJugador::ejecutarEvento(string controlId){

	if (MensajesUtil::sonIguales(controlId, "btGuardar"))
	{
		if (txPassword->getTexto().length() == 0 || txUsuario->getTexto().length() == 0 ||
			txNombre->getTexto().length() == 0 || txApellido->getTexto().length() == 0 ||
			txConfirmPassword->getTexto().length() == 0)
		{
			if (txNombre->getTexto().length() == 0)
				mostrarMensaje("Complete nombre e intente nuevamente.");
			else if (txApellido->getTexto().length() == 0)
				mostrarMensaje("Complete apellido e intente nuevamente.");
			else if (txUsuario->getTexto().length() == 0)
				mostrarMensaje("Complete usuario e intente nuevamente.");
			else if (txPassword->getTexto().length() == 0)
				mostrarMensaje("Complete password e intente nuevamente.");
			else if (txConfirmPassword->getTexto().length() == 0)
				mostrarMensaje("Complete la confirmacion e intente nuevamente.");

			lanzarEvento(100);
			return false;
		}
		else if (!MensajesUtil::sonIguales(txPassword->getTexto(), txConfirmPassword->getTexto()))
		{
			mostrarMensaje("El Password y la Confirmacion son distintos.");
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
			parametros.push_back(txNombre->getTexto());
			parametros.push_back(txApellido->getTexto());
			operacion = fab.newOperacion("OpUIClienteRegistrarJugador", parametros);

			if (operacion->ejecutarAccion(NULL))
			{
				this->guardado = true;
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
	else if (MensajesUtil::sonIguales(controlId, "btCancel"))
	{
		this->cancelado = true;
		SDL_Quit();
		return true;
	}

	return false;
}
void VentanaNuevoJugador::refrescar(SDL_Surface* superficie) {
		if(SDL_Flip(superficie) == -1) { 
		throw UIException("Error al redibujar la pantalla completa.","E");
	} 
}
void VentanaNuevoJugador::dibujarSobreSup(SDL_Surface* superficie){

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
void VentanaNuevoJugador::dibujar(SDL_Surface* superficie){

	if (this->hayCambios) {
		if (superficie != NULL) {
			this->dibujarSobreSup(superficie);

		} else {
			this->dibujarSobreSup(this->pantalla);
		}
		this->hayCambios = false;
	}
}
bool VentanaNuevoJugador::getGuardado() {
	return this->guardado;
}
bool VentanaNuevoJugador::getCancelado() {
	return this->cancelado;
}
