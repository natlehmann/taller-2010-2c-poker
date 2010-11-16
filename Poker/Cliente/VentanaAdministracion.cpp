#include "VentanaAdministracion.h"
#include "RecursosCliente.h"
#include "MensajesUtil.h"
#include "DatosInvalidosException.h"
#include "UtilTiposDatos.h"
#include "UICliente.h"
#include "UIException.h"
#include "ComponentePanel.h"
#include "FabricaOperacionesCliente.h"
#include "ServiciosGraficos.h"
#include <typeinfo.h>
#include <cstdlib>
#include <direct.h> 

VentanaAdministracion::VentanaAdministracion(string usuario, int sessionId, int cantFichas) {

	UICliente::iniciarSDL();

	this->usuario = usuario;
	this->sessionId = sessionId;
	this->cantFichas = cantFichas;
	this->id = "";
	this->posX = 0;
	this->posY = 0;
	this->offset = new SDL_Rect();
	this->contorno = new SDL_Rect();
	this->contornoConOffset = new SDL_Rect();
	this->irMesa = false;
	this->verEstadisticas = false;
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

	SDL_WM_SetCaption(RecursosCliente::getConfig()->get("cliente.configuracion.mensajeAdministracion").c_str(), NULL); 
	
	this->fondo = new Color(RecursosCliente::getConfig()->get("cliente.tema.default.menu.fondo"));
	
	this->imagenFondo = new Imagen("pantallaAdministracion.bmp");
	this->imagenFondo->setAlto(this->getAlto());
	this->imagenFondo->setAncho(this->getAncho());
	this->imagenFondo->setPosX(0);
	this->imagenFondo->setPosY(0);
	this->agregarElementoGrafico(this->imagenFondo);

	this->configurarControles();
	this->hayCambios = true;
}

VentanaAdministracion::~VentanaAdministracion(void)
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


void VentanaAdministracion::configurarControles() {

	string estilo = RecursosCliente::getConfig()->get("cliente.configuracion.fuentes") +
					RecursosCliente::getConfig()->get("cliente.tema.default.etiquetas.fuente.estilo") + ".ttf";


	etNombre = new Etiqueta("Usuario: " + this->usuario);
	if (ServiciosGraficos::getAnchoVentana() > ANCHO_LIMITE_MINIMO_CORRECCION) {
		etNombre->setPosX(this->anchoColumna*12);
	} else {
		etNombre->setPosX(this->anchoColumna*11);
	}
	etNombre->setAncho(this->anchoColumna*5);
	etNombre->setPosY((int)(this->altoFila*12.5));
	etNombre->setAlto(this->altoFila*2);
	etNombre->setFondo(NULL);
	if (ServiciosGraficos::getAnchoVentana() >= ANCHO_LIMITE_CORRECCION) {
		etNombre->setFuente(new Fuente("9,78,44", 16, estilo));
	} else {
		etNombre->setFuente(new Fuente("9,78,44", 13, estilo));
	}
	this->agregarElementoGrafico(etNombre);


	etFichas = new Etiqueta("Fichas: " + MensajesUtil::intToString(this->cantFichas));
	etFichas->setPosX(this->anchoColumna*18);
	etFichas->setAncho(this->anchoColumna*4);
	etFichas->setPosY((int)(this->altoFila*12.5));
	etFichas->setAlto(this->altoFila*2);
	etFichas->setFondo(NULL);
	if (ServiciosGraficos::getAnchoVentana() >= ANCHO_LIMITE_CORRECCION) {
		etFichas->setFuente(new Fuente("9,78,44", 16, estilo));
	} else {
		etFichas->setFuente(new Fuente("9,78,44", 13, estilo));
	}
	this->agregarElementoGrafico(etFichas);

	/*
	Panel* pnComprarFichas = new Panel();
	pnComprarFichas->setPosX(this->anchoColumna*1);
	pnComprarFichas->setAncho(this->anchoColumna*23);
	pnComprarFichas->setPosY(this->altoFila*16); 
	pnComprarFichas->setAlto(this->altoFila*1);
	pnComprarFichas->setFondo(NULL);
	this->agregarElementoGrafico(pnComprarFichas);
	*/
	

	Etiqueta* etTitPnComprarFichas = new Etiqueta(" Comprar Fichas");
	etTitPnComprarFichas->setPosX(this->anchoColumna*2);
	if (ServiciosGraficos::getAnchoVentana() >= ANCHO_LIMITE_CORRECCION) {
		etTitPnComprarFichas->setAncho(this->anchoColumna*5);
	} else {
		etTitPnComprarFichas->setAncho(this->anchoColumna*6);
	}
	etTitPnComprarFichas->setPosY(this->altoFila*16);
	etTitPnComprarFichas->setAlto((int)(this->altoFila*1.5));
	etTitPnComprarFichas->setFondo(new Color(9,78,44));
	this->agregarElementoGrafico(etTitPnComprarFichas);


	Etiqueta* etCantidad = new Etiqueta("Cantidad:");
	if (ServiciosGraficos::getAnchoVentana() >= ANCHO_LIMITE_CORRECCION) {
		etCantidad->setPosX(this->anchoColumna*8);
	} else {
		etCantidad->setPosX((int)(this->anchoColumna*8.5));
	}
	etCantidad->setAncho(this->anchoColumna*4);
	etCantidad->setPosY(this->altoFila*16);
	etCantidad->setAlto((int)(this->altoFila*1.5));
	etCantidad->setFondo(NULL);
	this->agregarElementoGrafico(etCantidad);

	txCantComprar = new TextBox("");
	txCantComprar->setPosX(this->anchoColumna*12);
	txCantComprar->setAncho(this->anchoColumna*5);
	txCantComprar->setPosY(this->altoFila*16);
	txCantComprar->setAlto((int)(this->altoFila*1.5));
	txCantComprar->setHabilitado(true);
	this->agregarComponentePanel(txCantComprar);


	Boton* btComprar = new Boton("Comprar");
	btComprar->setId("btComprar");
	btComprar->setPosX(this->anchoColumna*18);
	btComprar->setPosY(this->altoFila*16);
	btComprar->setHabilitado(true);
	this->agregarComponentePanel(btComprar);

	/*
	Panel* pnCambiarImagen = new Panel();
	pnCambiarImagen->setPosX(this->anchoColumna*1);
	pnCambiarImagen->setAncho(this->anchoColumna*23);
	pnCambiarImagen->setPosY(this->altoFila*18);
	pnCambiarImagen->setAlto(this->altoFila*1);
	pnCambiarImagen->setFondo(NULL);
	this->agregarElementoGrafico(pnCambiarImagen);
	*/
	
	Etiqueta* etTitPnCambiarImagen = new Etiqueta(" Cambiar Imagen");
	etTitPnCambiarImagen->setPosX(this->anchoColumna*2);
	if (ServiciosGraficos::getAnchoVentana() >= ANCHO_LIMITE_CORRECCION) {
		etTitPnCambiarImagen->setAncho(this->anchoColumna*5);
	} else {
		etTitPnCambiarImagen->setAncho(this->anchoColumna*6);
	}
	etTitPnCambiarImagen->setPosY(this->altoFila*18);
	etTitPnCambiarImagen->setAlto((int)(this->altoFila*1.5));
	etTitPnCambiarImagen->setFondo(new Color(9,78,44));
	this->agregarElementoGrafico(etTitPnCambiarImagen);

	Etiqueta* etRutaImagen = NULL;
	if (ServiciosGraficos::getAnchoVentana() >= ANCHO_LIMITE_CORRECCION) {
		etRutaImagen = new Etiqueta("Path Imagen:");
	} else {
		etRutaImagen = new Etiqueta("Path:");
	}
	if (ServiciosGraficos::getAnchoVentana() >= ANCHO_LIMITE_CORRECCION) {
		etRutaImagen->setPosX(this->anchoColumna*8);
	} else {
		etRutaImagen->setPosX((int)(this->anchoColumna*8.5));
	}
	etRutaImagen->setAncho(this->anchoColumna*4);
	etRutaImagen->setPosY(this->altoFila*18);
	etRutaImagen->setAlto((int)(this->altoFila*1.5));
	etRutaImagen->setFondo(NULL);
	this->agregarElementoGrafico(etRutaImagen);


	txRutaImagen = new TextBox("");
	txRutaImagen->setPosX(this->anchoColumna*12);
	txRutaImagen->setAncho(this->anchoColumna*5);
	txRutaImagen->setPosY(this->altoFila*18);
	txRutaImagen->setAlto((int)(this->altoFila*1.5));
	txRutaImagen->setHabilitado(true);
	this->agregarComponentePanel(txRutaImagen);


	Boton* btCargar = new Boton("Cargar Imagen");
	btCargar->setId("btCargar");
	btCargar->setPosX(this->anchoColumna*18);
	btCargar->setPosY(this->altoFila*18);
	btCargar->setHabilitado(true);
	this->agregarComponentePanel(btCargar);

	/*
	Panel* pnBotonera = new Panel();
	pnBotonera->setPosX(this->anchoColumna*1);
	pnBotonera->setAncho(this->anchoColumna*23);
	pnBotonera->setPosY((int)(this->altoFila*20.5));
	pnBotonera->setAlto(this->altoFila*2);
	pnBotonera->setFondo(new Color("183,210,90"));
	this->agregarElementoGrafico(pnBotonera);
	*/

	Boton* btMesa = new Boton("Ir a Mesa");
	btMesa->setId("btMesa");
	btMesa->setPosX(this->anchoColumna*2);
	btMesa->setPosY(this->altoFila*21);
	btMesa->setHabilitado(true);
	this->agregarComponentePanel(btMesa);

	Boton* btEstadisticas = new Boton("Ver Estadisticas");
	btEstadisticas->setId("btEstadisticas");
	if (ServiciosGraficos::getAnchoVentana() >= ANCHO_LIMITE_CORRECCION) {
		btEstadisticas->setPosX(this->anchoColumna*6);
	} else {
		btEstadisticas->setPosX(this->anchoColumna*7);
	}
	btEstadisticas->setPosY(this->altoFila*21);
	btEstadisticas->setHabilitado(true);
	this->agregarComponentePanel(btEstadisticas);

	Boton* btCancel = new Boton("Salir");
	btCancel->setId("btCancel");
	btCancel->setPosX(this->anchoColumna*18);
	btCancel->setPosY(this->altoFila*21);
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

void VentanaAdministracion::iniciar() {

	//dibuja los controles en la pantalla
	this->dibujar(NULL);

	bool listo = false;
	SDL_Event event;

	while(!listo) {
		while(SDL_WaitEvent(&event) && !listo) {
			listo = this->manejarEventos(&event);

			if( (event.type == SDL_QUIT) || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) ){
				lanzarEvento(101);
				/*this->cancelado = true;
				SDL_Quit();
                listo = true;*/
            }

		}
	}

}

void VentanaAdministracion::mostrarMensaje(string mensaje){
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
void VentanaAdministracion::actualizarFichas(int cantFichasCompradas){
	if (this->etFichas != NULL) {
		this->cantFichas += cantFichasCompradas;
		this->etFichas->setMensaje("Fichas: " + MensajesUtil::intToString(this->cantFichas));
		this->etFichas->setVisible(true);
		this->etFichas->dibujar(this->pantalla);
	}
}
void VentanaAdministracion::agregarElementoGrafico(ElementoGrafico* elemento) {
	this->elementos.push_back(elemento);
	elemento->setVentana(this);
}

void VentanaAdministracion::agregarComponentePanel(ComponentePanel* componente) {
	this->componentes.push_back(componente);
	componente->setVentana(this);
}

bool VentanaAdministracion::manejarEventos(SDL_Event* event){


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
				if (event->user.code == 100)
					refrescar = true;
				else if (event->user.code == 101)
					controlId = "btCancel";
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
void VentanaAdministracion::lanzarEvento(int codigoEvento) {
	SDL_Event event;

	event.type = SDL_USEREVENT;
	event.user.code = codigoEvento;
	event.user.data1 = 0;
	event.user.data2 = 0;
	SDL_PushEvent(&event);
}
bool VentanaAdministracion::ejecutarPreEvento(string controlId){

	bool refrescar = false;
	if (MensajesUtil::sonIguales(controlId, "btComprar"))
	{
		mostrarMensaje("Espere, realizando transaccion...");
		//lanzarEvento(100);
		refrescar = true;
	}
	else if (MensajesUtil::sonIguales(controlId, "btCargar"))
	{
		mostrarMensaje("Espere, transferiendo imagen al servidor...");
		//lanzarEvento(100);
		refrescar = true;
	}

	return refrescar;
}
bool VentanaAdministracion::ejecutarEvento(string controlId){

	bool finalizar = false;
	if (MensajesUtil::sonIguales(controlId, "btComprar"))
	{
		if (txCantComprar->getTexto().length() == 0 || !UtilTiposDatos::esEntero(txCantComprar->getTexto()))
		{
			if (txCantComprar->getTexto().length() == 0)
				mostrarMensaje("Complete la cantidad de fichas e intente nuevamente.");
			else if (!UtilTiposDatos::esEntero(txCantComprar->getTexto()))
				mostrarMensaje("Cantidad invalida, corriga e intente nuevamente.");			
			
			lanzarEvento(100);
		}
		else
		{
			FabricaOperacionesCliente fab;
			OperacionUICliente* operacion = NULL;

			vector<string> parametros;
			parametros.push_back(this->usuario);
			parametros.push_back(txCantComprar->getTexto());
			operacion = fab.newOperacion("OpUIClienteComprarFichas", parametros);

			if (operacion->ejecutarAccion(NULL))
			{
				int cantFichasCompradas = UtilTiposDatos::getEntero(txCantComprar->getTexto());
				this->actualizarFichas(cantFichasCompradas);
				this->mostrarMensaje("Transaccion exitosa.");
				this->lanzarEvento(100);
			}
			else
			{
				mostrarMensaje(operacion->getError());
				lanzarEvento(100);
			}

			delete(operacion);
		}
	}
	if (MensajesUtil::sonIguales(controlId, "btCargar"))
	{
		if (txRutaImagen->getTexto().length() == 0)
		{
			if (txCantComprar->getTexto().length() == 0)
				mostrarMensaje("Complete la ruta del archivo e intente nuevamente.");
			
			lanzarEvento(100);
		}
		else if (txRutaImagen->getTexto().length() <= 4 || 
			!MensajesUtil::sonIguales(MensajesUtil::ToLower(txRutaImagen->getTexto().substr(txRutaImagen->getTexto().length()-4, 4)), ".bmp"))
		{
			mostrarMensaje("La imagen debe ser un BMP.");
			
			lanzarEvento(100);
		}
		else
		{
			FabricaOperacionesCliente fab;
			OperacionUICliente* operacion = NULL;

			vector<string> parametros;
			parametros.push_back(this->usuario);
			parametros.push_back(txRutaImagen->getTexto());
			parametros.push_back(txRutaImagen->getTexto());
			operacion = fab.newOperacion("OpUIClienteEnviarFoto", parametros);

			if (operacion->ejecutarAccion(NULL))
			{
				mostrarMensaje("Transaccion exitosa.");
				lanzarEvento(100);
			}
			else
			{
				mostrarMensaje(operacion->getError());
				lanzarEvento(100);
			}

			delete(operacion);
		}
	}
	else if (MensajesUtil::sonIguales(controlId, "btMesa"))
	{
		this->irMesa = true;
		SDL_Quit();
		finalizar = true;
	}
	else if (MensajesUtil::sonIguales(controlId, "btEstadisticas"))
	{
		this->verEstadisticas = true;
		SDL_Quit();
		finalizar = true;
	}
	else if (MensajesUtil::sonIguales(controlId, "btCancel"))
	{
		FabricaOperacionesCliente fab;
		OperacionUICliente* operacion = NULL;

		vector<string> parametros;
		parametros.push_back(this->usuario);
		parametros.push_back(MensajesUtil::intToString(this->sessionId));
		operacion = fab.newOperacion("OpUIClienteLogoff", parametros);

		operacion->ejecutarAccion(NULL);
		delete(operacion);

		this->cancelado = true;
		SDL_Quit();
		finalizar = true;
	}

	return finalizar;
}
void VentanaAdministracion::refrescar(SDL_Surface* superficie) {
		if(SDL_Flip(superficie) == -1) { 
		throw UIException("Error al redibujar la pantalla completa.","E");
	} 
}
void VentanaAdministracion::dibujarSobreSup(SDL_Surface* superficie){

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
void VentanaAdministracion::dibujar(SDL_Surface* superficie){

	if (this->hayCambios) {
		if (superficie != NULL) {
			this->dibujarSobreSup(superficie);

		} else {
			this->dibujarSobreSup(this->pantalla);
		}
		this->hayCambios = false;
	}
}
string VentanaAdministracion::getUsuario() {
	return this->usuario;
}
int VentanaAdministracion::getSesionId() {
	return this->sessionId;
}
int VentanaAdministracion::getCantFichas() {
	return this->cantFichas;
}
bool VentanaAdministracion::getIrMesa() {
	return this->irMesa;
}
bool VentanaAdministracion::getVerEstadisticas() {
	return this->verEstadisticas;
}
bool VentanaAdministracion::getCancelado() {
	return this->cancelado;
}
