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
	this->setAlto(this->altoFila*31);
	this->setAncho(this->anchoColumna*25);

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

	SDL_WM_SetCaption(RecursosCliente::getConfig()->get("cliente.configuracion.mensajeNuevoJugador").c_str(), NULL); 
	
	this->fondo = new Color(RecursosCliente::getConfig()->get("cliente.tema.default.menu.fondo"));
	
	this->imagenFondo = new Imagen("pantallaLogin.bmp");
	this->imagenFondo->setAlto(this->getAlto());
	this->imagenFondo->setAncho(this->getAncho());
	this->imagenFondo->setPosX(0);
	this->imagenFondo->setPosY(0);
	this->agregarElementoGrafico(this->imagenFondo);

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

	string estilo = RecursosCliente::getConfig()->get("cliente.configuracion.fuentes") +
					RecursosCliente::getConfig()->get("cliente.tema.default.etiquetas.fuente.estilo") + ".ttf";

	/*
	Panel* pnFecha = new Panel();
	pnFecha->setPosX(this->anchoColumna*1);
	pnFecha->setAncho(this->anchoColumna*18);
	pnFecha->setPosY(this->altoFila*1);
	pnFecha->setAlto(this->altoFila*19);
	pnFecha->setFondo(new Color(fondo->getRed(), fondo->getGreen(), fondo->getBlue()));
	this->agregarElementoGrafico(pnFecha);
	*/
	
	Etiqueta* etTitPnFecha = new Etiqueta("Registracion de nuevo usuario");
	if (ServiciosGraficos::getAnchoVentana() > ANCHO_LIMITE_MINIMO_CORRECCION) {
		etTitPnFecha->setPosX(this->anchoColumna*13);
	} else {
		etTitPnFecha->setPosX(this->anchoColumna*12);
	}
	etTitPnFecha->setAncho(this->anchoColumna*9);
	etTitPnFecha->setPosY((int)(this->altoFila*12.5));
	etTitPnFecha->setAlto(this->altoFila*2);
	etTitPnFecha->setFondo(NULL);
	if (ServiciosGraficos::getAnchoVentana() >= ANCHO_LIMITE_CORRECCION) {
		etTitPnFecha->setFuente(new Fuente("9,78,44", 18, estilo));
	} else {
		etTitPnFecha->setFuente(new Fuente("9,78,44", 13, estilo));
	}
	this->agregarElementoGrafico(etTitPnFecha);

	Etiqueta* etNombre = new Etiqueta("Nombre:");
	etNombre->setPosX(this->anchoColumna*2);
	etNombre->setAncho(this->anchoColumna*4);
	etNombre->setPosY(this->altoFila*16);
	etNombre->setAlto(this->altoFila*1);
	etNombre->setFondo(NULL);
	this->agregarElementoGrafico(etNombre);

	txNombre = new TextBox("");
	txNombre->setPosX(this->anchoColumna*6);
	txNombre->setAncho(this->anchoColumna*6);
	txNombre->setPosY(this->altoFila*16);
	if (ServiciosGraficos::getAnchoVentana() >= ANCHO_LIMITE_CORRECCION) {
		txNombre->setAlto(this->altoFila*1);
	} else {
		txNombre->setAlto((int)(this->altoFila*1.5));
	}
	txNombre->setHabilitado(true);
	this->agregarComponentePanel(txNombre);


	Etiqueta* etApellido = new Etiqueta("Apellido:");
	etApellido->setPosX(this->anchoColumna*2);
	etApellido->setAncho(this->anchoColumna*4);
	etApellido->setPosY(this->altoFila*18);
	etApellido->setAlto(this->altoFila*1);
	etApellido->setFondo(NULL);
	this->agregarElementoGrafico(etApellido);


	txApellido = new TextBox("");
	txApellido->setPosX(this->anchoColumna*6);
	txApellido->setAncho(this->anchoColumna*6);
	txApellido->setPosY(this->altoFila*18);
	if (ServiciosGraficos::getAnchoVentana() >= ANCHO_LIMITE_CORRECCION) {
		txApellido->setAlto(this->altoFila*1);
	} else {
		txApellido->setAlto((int)(this->altoFila*1.5));
	}
	txApellido->setHabilitado(true);
	this->agregarComponentePanel(txApellido);


	Etiqueta* etImagen = NULL;
	if (ServiciosGraficos::getAnchoVentana() >= ANCHO_LIMITE_CORRECCION) {
		etImagen = new Etiqueta("Ruta Imagen:");
	} else {
		etImagen = new Etiqueta("Imagen:");
	}
	etImagen->setPosX(this->anchoColumna*2);
	etImagen->setAncho(this->anchoColumna*4);
	etImagen->setPosY(this->altoFila*20);
	etImagen->setAlto(this->altoFila*1);
	etImagen->setFondo(NULL);
	this->agregarElementoGrafico(etImagen);

	txImagen = new TextBox("");
	txImagen->setPosX(this->anchoColumna*6);
	txImagen->setAncho(this->anchoColumna*6);
	txImagen->setPosY(this->altoFila*20);
	if (ServiciosGraficos::getAnchoVentana() >= ANCHO_LIMITE_CORRECCION) {
		txImagen->setAlto(this->altoFila*1);
	} else {
		txImagen->setAlto((int)(this->altoFila*1.5));
	}
	txImagen->setHabilitado(true);
	this->agregarComponentePanel(txImagen);


	Etiqueta* etUsuario = new Etiqueta("Usuario:");
	etUsuario->setPosX(this->anchoColumna*13);
	etUsuario->setAncho(this->anchoColumna*4);
	etUsuario->setPosY(this->altoFila*16);
	etUsuario->setAlto(this->altoFila*1);
	etUsuario->setFondo(NULL);
	this->agregarElementoGrafico(etUsuario);


	txUsuario = new TextBox("");
	txUsuario->setPosX(this->anchoColumna*17);
	txUsuario->setAncho(this->anchoColumna*6);
	txUsuario->setPosY(this->altoFila*16);
	if (ServiciosGraficos::getAnchoVentana() >= ANCHO_LIMITE_CORRECCION) {
		txUsuario->setAlto(this->altoFila*1);
	} else {
		txUsuario->setAlto((int)(this->altoFila*1.5));
	}
	txUsuario->setHabilitado(true);
	this->agregarComponentePanel(txUsuario);


	Etiqueta* etPassword = new Etiqueta("Password:");
	etPassword->setPosX(this->anchoColumna*13);
	etPassword->setAncho(this->anchoColumna*4);
	etPassword->setPosY(this->altoFila*18);
	etPassword->setAlto(this->altoFila*1);
	etPassword->setFondo(NULL);
	this->agregarElementoGrafico(etPassword);


	txPassword = new TextBox("");
	txPassword->setPosX(this->anchoColumna*17);
	txPassword->setAncho(this->anchoColumna*6);
	txPassword->setPosY(this->altoFila*18);
	if (ServiciosGraficos::getAnchoVentana() >= ANCHO_LIMITE_CORRECCION) {
		txPassword->setAlto(this->altoFila*1);
	} else {
		txPassword->setAlto((int)(this->altoFila*1.5));
	}
	txPassword->setHabilitado(true);
	txPassword->setTipoPassword(true);
	this->agregarComponentePanel(txPassword);

	
	Etiqueta* etConfPassword = NULL;
	if (ServiciosGraficos::getAnchoVentana() >= ANCHO_LIMITE_CORRECCION) {
		etConfPassword = new Etiqueta("Confirmar pw:");
	} else {
		etConfPassword = new Etiqueta("Confirmar:");
	}
	etConfPassword->setPosX(this->anchoColumna*13);
	etConfPassword->setAncho(this->anchoColumna*4);
	etConfPassword->setPosY(this->altoFila*20);
	etConfPassword->setAlto(this->altoFila*1);
	etConfPassword->setFondo(NULL);
	this->agregarElementoGrafico(etConfPassword);


	txConfirmPassword = new TextBox("");
	txConfirmPassword->setPosX(this->anchoColumna*17);
	txConfirmPassword->setAncho(this->anchoColumna*6);
	txConfirmPassword->setPosY(this->altoFila*20);
	if (ServiciosGraficos::getAnchoVentana() >= ANCHO_LIMITE_CORRECCION) {
		txConfirmPassword->setAlto(this->altoFila*1);
	} else {
		txConfirmPassword->setAlto((int)(this->altoFila*1.5));
	}
	txConfirmPassword->setHabilitado(true);
	txConfirmPassword->setTipoPassword(true);
	this->agregarComponentePanel(txConfirmPassword);

	Boton* btGuardar = new Boton("Guardar");
	btGuardar->setId("btGuardar");
	if (ServiciosGraficos::getAnchoVentana() > ANCHO_LIMITE_MINIMO_CORRECCION) {
		btGuardar->setPosX(this->anchoColumna*17);
	} else {
		btGuardar->setPosX(this->anchoColumna*15);
	}
	btGuardar->setPosY(this->altoFila*22);
	btGuardar->setHabilitado(true);
	this->agregarComponentePanel(btGuardar);


	Boton* btCancel = new Boton("Salir");
	btCancel->setId("btCancel");
	if (ServiciosGraficos::getAnchoVentana() > ANCHO_LIMITE_MINIMO_CORRECCION) {
		btCancel->setPosX(this->anchoColumna*21);
	} else {
		btCancel->setPosX(this->anchoColumna*20);
	}
	btCancel->setPosY(this->altoFila*22);
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

	bool refrescar = false;
	if (MensajesUtil::sonIguales(controlId, "btGuardar"))
	{
		mostrarMensaje("Espere, Creando Nuevo Usuario...");
		//lanzarEvento(100);
		refrescar = true;
	}

	return refrescar;
}
bool VentanaNuevoJugador::ejecutarEvento(string controlId){

	bool finalizar = false;
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
		}
		else if (!MensajesUtil::sonIguales(txPassword->getTexto(), txConfirmPassword->getTexto()))
		{
			mostrarMensaje("El Password y la Confirmacion son distintos.");
			lanzarEvento(100);
		}
		else if ((txImagen->getTexto().length() > 0) && (txImagen->getTexto().length() <= 4))
		{
			mostrarMensaje("La imagen debe ser un BMP.");
			lanzarEvento(100);
		}
		else if ((txImagen->getTexto().length() > 0) && 
			!MensajesUtil::sonIguales(MensajesUtil::ToLower(txImagen->getTexto().substr(txImagen->getTexto().length()-4, 4)), ".bmp"))
		{
			mostrarMensaje("La imagen debe ser un BMP.");
			lanzarEvento(100);
		}
		else if (txImagen->getTexto().length() > 0 && !MensajesUtil::FileExists(txImagen->getTexto()))
		{
			mostrarMensaje("El archivo imagen no existe.");
			lanzarEvento(100);
		}	
		else
		{
			FabricaOperacionesCliente fab;
			OperacionUICliente* operacionDatos = NULL;

			vector<string> parametros;
			parametros.push_back(txUsuario->getTexto());
			parametros.push_back(txPassword->getTexto());
			parametros.push_back(txNombre->getTexto());
			parametros.push_back(txApellido->getTexto());
			operacionDatos = fab.newOperacion("OpUIClienteRegistrarJugador", parametros);

			if (operacionDatos->ejecutarAccion(NULL))
			{
				this->guardado = true;

				if (txImagen->getTexto().length())
				{
					//se envia la foto al servidor
					OperacionUICliente* operacionImagen = NULL;

					parametros.clear();
					parametros.push_back(txUsuario->getTexto());
					parametros.push_back(txImagen->getTexto());
					parametros.push_back(txImagen->getTexto());
					operacionImagen = fab.newOperacion("OpUIClienteEnviarFoto", parametros);

					if (operacionImagen->ejecutarAccion(NULL))
					{
						mostrarMensaje("Transaccion exitosa.");
						lanzarEvento(100);
					}
					else
					{
						mostrarMensaje(operacionImagen->getError());
						lanzarEvento(100);
					}

					delete(operacionImagen);
				}

				SDL_Quit();
				finalizar = true;		
			}
			else
			{
				mostrarMensaje(operacionDatos->getError());
				lanzarEvento(100);
			}

			delete(operacionDatos);
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
