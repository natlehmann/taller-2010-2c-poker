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

	this->usuario = ""; 
	this->sessionId = -1;
	this->cantFichas = -1;
	this->id = "";
	this->posX = 0;
	this->posY = 0;
	this->offset = new SDL_Rect();
	this->contorno = new SDL_Rect();
	this->contornoConOffset = new SDL_Rect();
	this->conectado = false;
	this->cancelado = false;
	this->nuevo = false;
	
	this->altoFila = ServiciosGraficos::getAltoFilaVentanaSegundaria();
	this->anchoColumna = ServiciosGraficos::getAnchoColVentanaSegundaria();
	this->setAlto(this->altoFila*18);
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

	SDL_WM_SetCaption(RecursosCliente::getConfig()->get("cliente.configuracion.mensajeLogin").c_str(), NULL); 
	
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
	delete (this->contornoConOffset);

}


void VentanaLogin::configurarControles() {

	Etiqueta* etUsuario = new Etiqueta("Usuario:");
	etUsuario->setPosX(this->anchoColumna*2);
	etUsuario->setAncho(this->anchoColumna*5);
	etUsuario->setPosY(this->altoFila*1);
	etUsuario->setAlto(this->altoFila*2);
	etUsuario->setFondo(new Color(fondo->getRed(), fondo->getGreen(), fondo->getBlue()));
	this->agregarElementoGrafico(etUsuario);

	txUsuario = new TextBox("poddo");
	txUsuario->setPosX(this->anchoColumna*7);
	txUsuario->setAncho(this->anchoColumna*10);
	txUsuario->setPosY(this->altoFila*1);
	txUsuario->setAlto(this->altoFila*2);
	txUsuario->setHabilitado(true);
	this->agregarComponentePanel(txUsuario);

	Etiqueta* etPassword = new Etiqueta("Password:");
	etPassword->setPosX(this->anchoColumna*2);
	etPassword->setAncho(this->anchoColumna*5);
	etPassword->setPosY(this->altoFila*5);
	etPassword->setAlto(this->altoFila*2);
	etPassword->setFondo(new Color(fondo->getRed(), fondo->getGreen(), fondo->getBlue()));
	this->agregarElementoGrafico(etPassword);

	txPassword = new TextBox("123");
	txPassword->setPosX(this->anchoColumna*7);
	txPassword->setAncho(this->anchoColumna*10);
	txPassword->setPosY(this->altoFila*5);
	txPassword->setAlto(this->altoFila*2);
	txPassword->setHabilitado(true);
	txPassword->setTipoPassword(true);
	this->agregarComponentePanel(txPassword);

	cbVirtual = new CheckBox("Virtual");
	cbVirtual->setPosX(this->anchoColumna*2);
	cbVirtual->setPosY(this->altoFila*8);
	cbVirtual->setHabilitado(true);
	this->agregarComponentePanel(cbVirtual);

	cbObservador = new CheckBox("Observador");
	cbObservador->setPosX(this->anchoColumna*2);
	cbObservador->setPosY(this->altoFila*10);
	cbObservador->setHabilitado(true);
	this->agregarComponentePanel(cbObservador);


	Boton* btLogin = new Boton("Login");
	btLogin->setId("btLogin");
	btLogin->setPosX(this->anchoColumna*3);
	btLogin->setPosY(this->altoFila*15);
	btLogin->setHabilitado(true);
	this->agregarComponentePanel(btLogin);

	Boton* btNuevo = new Boton("Nuevo");
	btNuevo->setId("btNuevo");
	btNuevo->setPosX(this->anchoColumna*8);
	btNuevo->setPosY(this->altoFila*15);
	btNuevo->setHabilitado(true);
	this->agregarComponentePanel(btNuevo);

	Boton* btCancel = new Boton("Cancel");
	btCancel->setId("btCancel");
	btCancel->setPosX(this->anchoColumna*13);
	btCancel->setPosY(this->altoFila*15);
	btCancel->setHabilitado(true);
	this->agregarComponentePanel(btCancel);

	mensaje = new Etiqueta("");
	mensaje->setPosX(this->anchoColumna*1);
	mensaje->setAncho(this->anchoColumna*17);
	mensaje->setPosY(this->altoFila*12);
	mensaje->setAlto(this->altoFila*2);
	mensaje->setFondo(new Color(fondo->getRed(), fondo->getGreen(), fondo->getBlue()));
	mensaje->setVisible(false);
	this->agregarElementoGrafico(mensaje);

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

		if (controlId.length() > 0)
			refrescar = this->ejecutarPreEvento(controlId);

		if (refrescar)
			this->refrescar(this->pantalla);

		if (controlId.length() > 0)
			finalizar = this->ejecutarEvento(controlId);
	}

	return finalizar;
}
void VentanaLogin::lanzarEvento(int codigoEvento) {
	SDL_Event event;

	event.type = SDL_USEREVENT;
	event.user.code = codigoEvento;
	event.user.data1 = 0;
	event.user.data2 = 0;
	SDL_PushEvent(&event);
}
bool VentanaLogin::ejecutarPreEvento(string controlId){

	if (MensajesUtil::sonIguales(controlId, "btLogin"))
	{
		mostrarMensaje("Espere, Validando Credenciales...");
		lanzarEvento(100);
		return true;
	}

	return false;
}
bool VentanaLogin::ejecutarEvento(string controlId){

	if (MensajesUtil::sonIguales(controlId, "btLogin"))
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

			string paramVirtual = (this->cbVirtual->getChecked()? "S":"N");
			string paramObservador = (this->cbObservador->getChecked()? "S":"N");
			vector<string> parametros;
			parametros.push_back(txUsuario->getTexto());
			parametros.push_back(txPassword->getTexto());
			parametros.push_back(paramVirtual);
			parametros.push_back(paramObservador);
			operacion = fab.newOperacion("OpUIClienteLogin", parametros);

			if (operacion->ejecutarAccion(NULL))
			{
				this->usuario = txUsuario->getTexto();
				this->sessionId = ((OpUIClienteLogin*)operacion)->getSesionId();
				this->cantFichas = ((OpUIClienteLogin*)operacion)->getCantFichas();
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
	else if (MensajesUtil::sonIguales(controlId, "btNuevo"))
	{
		this->nuevo = true;
		SDL_Quit();
		return true;
	}
	else if (MensajesUtil::sonIguales(controlId, "btCancel"))
	{
		this->cancelado = true;
		SDL_Quit();
		return true;
	}

	return false;
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
string VentanaLogin::getUsuario() {
	return this->usuario;
}
int VentanaLogin::getSesionId() {
	return this->sessionId;
}
int VentanaLogin::getCantFichas() {
	return this->cantFichas;
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

bool VentanaLogin::isVirtual() {
	return this->cbVirtual->getChecked();
}

bool VentanaLogin::isObservador() {
	return this->cbObservador->getChecked();
}