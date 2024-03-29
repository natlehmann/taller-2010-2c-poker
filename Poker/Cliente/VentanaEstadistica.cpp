#include "VentanaEstadistica.h"
#include "RecursosCliente.h"
#include "MensajesUtil.h"
#include "DatosInvalidosException.h"
#include "UtilTiposDatos.h"
#include "UICliente.h"
#include "UIException.h"
#include "ComponentePanel.h"
#include "FabricaOperacionesCliente.h"
#include "OpUIClienteSolicitarEstadistica.h"
#include "ServiciosGraficos.h"
#include <typeinfo.h>
#include <cstdlib>

VentanaEstadistica::VentanaEstadistica(string usuario, int sessionId) {

	UICliente::iniciarSDL();

	this->usuario = usuario;
	this->sessionId = sessionId;
	this->id = "";
	this->posX = 0;
	this->posY = 0;
	this->offset = new SDL_Rect();
	this->contorno = new SDL_Rect();
	this->contornoConOffset = new SDL_Rect();

	this->dia = "";
	this->mes = "";
	this->anio = "";
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

	if (this->pantalla == NULL) {
		throw UIException("No se pudo inicializar la ventana de la aplicacion.","E");
	}

	SDL_WM_SetCaption(RecursosCliente::getConfig()->get("cliente.configuracion.mensajeEstadisticas").c_str(), NULL); 
	
	this->fondo = new Color(RecursosCliente::getConfig()->get("cliente.tema.default.menu.fondo"));
	
	this->imagenFondo = new Imagen("pantallaEstadisticas.bmp");
	this->imagenFondo->setAlto(this->getAlto());
	this->imagenFondo->setAncho(this->getAncho());
	this->imagenFondo->setPosX(0);
	this->imagenFondo->setPosY(0);
	this->agregarElementoGrafico(this->imagenFondo);

	this->configurarControles();
	this->hayCambios = true;
}

VentanaEstadistica::~VentanaEstadistica(void)
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


void VentanaEstadistica::configurarControles() {

	/*
	Panel* pnFecha = new Panel();
	pnFecha->setPosX(this->anchoColumna*1);
	pnFecha->setAncho(this->anchoColumna*19);
	pnFecha->setPosY(this->altoFila*1);
	pnFecha->setAlto(this->altoFila*4);
	pnFecha->setFondo(new Color(fondo->getRed(), fondo->getGreen(), fondo->getBlue()));
	this->agregarElementoGrafico(pnFecha);
	*/
	
	Etiqueta* etTitPnFecha = NULL;
	if (ServiciosGraficos::getAnchoVentana() >= ANCHO_LIMITE_CORRECCION) {
		etTitPnFecha = new Etiqueta("Fecha de Consulta (DD/MM/AAAA o MM/AAAA o AAAA)");
	} else {
		etTitPnFecha = new Etiqueta("Fecha (DD/MM/AAAA o MM/AAAA o AAAA)");
	}
	etTitPnFecha->setPosX(this->anchoColumna*2);
	etTitPnFecha->setAncho(this->anchoColumna*13);
	etTitPnFecha->setPosY(this->altoFila*15);
	etTitPnFecha->setAlto(this->altoFila*1);
	etTitPnFecha->setFondo(NULL);
	this->agregarElementoGrafico(etTitPnFecha);


	txFecha = new TextBox("");
	txFecha->setPosX(this->anchoColumna*17);
	txFecha->setAncho(this->anchoColumna*5);
	txFecha->setPosY((int)(this->altoFila*14.7));
	txFecha->setAlto((int)(this->altoFila*1.5));
	txFecha->setHabilitado(true);
	this->agregarComponentePanel(txFecha);

	/*
	Panel* pnTipoEstadistica = new Panel();
	pnTipoEstadistica->setPosX(this->anchoColumna*1);
	pnTipoEstadistica->setAncho(this->anchoColumna*19);
	pnTipoEstadistica->setPosY(this->altoFila*6); 
	pnTipoEstadistica->setAlto(this->altoFila*13);
	pnTipoEstadistica->setFondo(new Color(fondo->getRed(), fondo->getGreen(), fondo->getBlue()));
	this->agregarElementoGrafico(pnTipoEstadistica);
	*/
	
	Etiqueta* etTitPnTipoEstadistica = new Etiqueta("Tipo de Estadistica (seleccione solo una)");
	etTitPnTipoEstadistica->setPosX(this->anchoColumna*2);
	etTitPnTipoEstadistica->setAncho(this->anchoColumna*14);
	etTitPnTipoEstadistica->setPosY((int)(this->altoFila*16.5));
	etTitPnTipoEstadistica->setAlto(this->altoFila*1);
	etTitPnTipoEstadistica->setFondo(NULL);
	this->agregarElementoGrafico(etTitPnTipoEstadistica);


	cbEvolucionUsuario = new CheckBox("Evolucion de los Usuarios");
	cbEvolucionUsuario->setId("cbEvolucionUsuario");
	cbEvolucionUsuario->setPosX(this->anchoColumna*2);
	cbEvolucionUsuario->setPosY(this->altoFila*18);
	cbEvolucionUsuario->setHabilitado(true);
	this->agregarComponentePanel(cbEvolucionUsuario);

	cbEvolucionUsuarioConectado = new CheckBox("Evolucion de los Usuarios Conectados");
	cbEvolucionUsuarioConectado->setId("cbEvolucionUsuarioConectado");
	cbEvolucionUsuarioConectado->setPosX(this->anchoColumna*2);
	cbEvolucionUsuarioConectado->setPosY(this->altoFila*19);
	cbEvolucionUsuarioConectado->setHabilitado(true);
	this->agregarComponentePanel(cbEvolucionUsuarioConectado);

	cbUsuariosRegistrados = new CheckBox("Listado de los Usuarios Registrados");
	cbUsuariosRegistrados->setId("cbUsuariosRegistrados");
	cbUsuariosRegistrados->setPosX(this->anchoColumna*2);
	cbUsuariosRegistrados->setPosY(this->altoFila*20);
	cbUsuariosRegistrados->setHabilitado(true);
	this->agregarComponentePanel(cbUsuariosRegistrados);

	cbUsuariosConectados = new CheckBox("Listado de los Usuarios Conectados");
	cbUsuariosConectados->setId("cbUsuariosConectados");
	cbUsuariosConectados->setPosX(this->anchoColumna*2);
	cbUsuariosConectados->setPosY(this->altoFila*21);
	cbUsuariosConectados->setHabilitado(true);
	this->agregarComponentePanel(cbUsuariosConectados);

	cbRanking = new CheckBox("Ranking");
	cbRanking->setId("cbRanking");
	cbRanking->setPosX(this->anchoColumna*2);
	cbRanking->setPosY(this->altoFila*22);
	cbRanking->setHabilitado(true);
	this->agregarComponentePanel(cbRanking);

	this->mensaje = new Etiqueta("");
	mensaje->setPosX(0);
	mensaje->setAlineacionHorizontal(ALINEACION_HORIZ_CENTRO);
	mensaje->setAncho(this->ancho);
	mensaje->setPosY(this->alto - this->altoFila*2);
	mensaje->setAlto(this->altoFila*2);
	mensaje->setFondo(new Color(9,78,44));
	mensaje->setVisible(false);
	this->agregarElementoGrafico(this->mensaje);

	Boton* btConsulta = new Boton("Consultar");
	btConsulta->setId("btConsulta");
	btConsulta->setPosX(this->anchoColumna*17);
	btConsulta->setPosY(this->altoFila*18);
	btConsulta->setHabilitado(true);
	this->agregarComponentePanel(btConsulta);

	Boton* btVolverMenuPrincipal = NULL;
	if (ServiciosGraficos::getAnchoVentana() >= ANCHO_LIMITE_CORRECCION) {
		btVolverMenuPrincipal = new Boton("Volver a Menu Ppal.");
	} else {
		btVolverMenuPrincipal = new Boton("Volver");
	}
	btVolverMenuPrincipal->setPosX(this->anchoColumna*17);
	btVolverMenuPrincipal->setId("btVolverMenuPrincipal");
	btVolverMenuPrincipal->setPosY(this->altoFila*21);
	btVolverMenuPrincipal->setHabilitado(true);
	this->agregarComponentePanel(btVolverMenuPrincipal);

}

void VentanaEstadistica::iniciar() {

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

void VentanaEstadistica::mostrarMensaje(string mensaje){
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
void VentanaEstadistica::agregarElementoGrafico(ElementoGrafico* elemento) {
	this->elementos.push_back(elemento);
	elemento->setVentana(this);
}

void VentanaEstadistica::agregarComponentePanel(ComponentePanel* componente) {
	this->componentes.push_back(componente);
	componente->setVentana(this);
}

bool VentanaEstadistica::manejarEventos(SDL_Event* event){


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
void VentanaEstadistica::lanzarEvento(int codigoEvento) {
	SDL_Event event;

	event.type = SDL_USEREVENT;
	event.user.code = codigoEvento;
	event.user.data1 = 0;
	event.user.data2 = 0;
	SDL_PushEvent(&event);
}
bool VentanaEstadistica::ejecutarPreEvento(string controlId){

	bool refrescar = false;
	if (MensajesUtil::sonIguales(controlId, "btConsulta"))
	{
		mostrarMensaje("Espere, Generando la Estadistica...");
		refrescar = true;
	}
	else if (MensajesUtil::sonIguales(controlId, "cbEvolucionUsuario") ||
			 MensajesUtil::sonIguales(controlId, "cbEvolucionUsuarioConectado") ||
			 MensajesUtil::sonIguales(controlId, "cbRanking") ||
			 MensajesUtil::sonIguales(controlId, "cbUsuariosConectados") ||
			 MensajesUtil::sonIguales(controlId, "cbUsuariosRegistrados"))
	{
		checkExcluyentes(controlId);
		refrescar = true;
	}
	return refrescar ;
}
bool VentanaEstadistica::ejecutarEvento(string controlId){

	bool finalizar = false;
	if (MensajesUtil::sonIguales(controlId, "btConsulta"))
	{
		string seleccion;
		if (validarSeleccion(seleccion))
		{
			if(validarFecha(txFecha->getTexto()) | MensajesUtil::sonIguales(seleccion,"ConsultaRanking"))
			{
				FabricaOperacionesCliente fab;
				OperacionUICliente* operacion = NULL;

				vector<string> parametros;
				parametros.push_back(seleccion);
				parametros.push_back(anio); //se supone que anio llega siempre
				if(mes != "")
					parametros.push_back(mes);
				if(dia != "")
					parametros.push_back(dia);
				
				operacion = fab.newOperacion("OpUIClienteSolicitarEstadistica", parametros);
				string pathArchivo;

				if (operacion->ejecutarAccion(NULL))
				{
					mostrarMensaje("Generado " + ((OpUIClienteSolicitarEstadistica*)operacion)->getArchivo());
					lanzarEvento(100);
				}

				delete (operacion);
			}
			else
			{
			mostrarMensaje("Verifique el formato de fecha.");
			lanzarEvento(100);
			}
		}
		else
		{
			mostrarMensaje("Debe seleccionar solo una opci�n.");
			lanzarEvento(100);
		}
	}
	if (MensajesUtil::sonIguales(controlId, "btVolverMenuPrincipal"))
	{
		this->cancelado = true;
		SDL_Quit();
		finalizar = true;
	}

	return finalizar;
}
void VentanaEstadistica::refrescar(SDL_Surface* superficie) {
		if(SDL_Flip(superficie) == -1) { 
		throw UIException("Error al redibujar la pantalla completa.","E");
	} 
}
void VentanaEstadistica::dibujarSobreSup(SDL_Surface* superficie){

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
void VentanaEstadistica::dibujar(SDL_Surface* superficie){

	if (this->hayCambios) {
		if (superficie != NULL) {
			this->dibujarSobreSup(superficie);

		} else {
			this->dibujarSobreSup(this->pantalla);
		}
		this->hayCambios = false;
	}
}
void VentanaEstadistica::checkExcluyentes(string controlId)
{
	if (!MensajesUtil::sonIguales(controlId, "cbEvolucionUsuario"))
		cbEvolucionUsuario->dibujarUp(this->pantalla);
	if (!MensajesUtil::sonIguales(controlId, "cbEvolucionUsuarioConectado"))
		cbEvolucionUsuarioConectado->dibujarUp(this->pantalla);
	if (!MensajesUtil::sonIguales(controlId, "cbRanking"))
		cbRanking->dibujarUp(this->pantalla);
	if (!MensajesUtil::sonIguales(controlId, "cbUsuariosConectados"))
		cbUsuariosConectados->dibujarUp(this->pantalla);
	if (!MensajesUtil::sonIguales(controlId, "cbUsuariosRegistrados"))
		cbUsuariosRegistrados->dibujarUp(this->pantalla);
}
bool VentanaEstadistica::validarFecha(string fecha)
{
	bool validacion = false;
	dia = "";
	mes = "";
	anio = "";

	if(fecha.length() != 0)
	{
		list<string> listaFecha = MensajesUtil::split(fecha,"/");
		if(listaFecha.size() < 4)
		{
			list<string>::iterator it = listaFecha.begin();
			
			if(listaFecha.size() == 1)
			{
				if (atoi((it->c_str())) > MINIMO_A�OS && atoi((it->c_str())) < MAXIMO_A�OS)
				{
					anio = it->c_str();
					validacion = true;
				}
			}

			if(listaFecha.size() == 2)
			{
				if (atoi((it->c_str())) > 0 && atoi((it->c_str())) <= MESES)
				{
					mes = it->c_str();
					it++;
					if (atoi((it->c_str())) > MINIMO_A�OS && atoi((it->c_str())) <= MAXIMO_A�OS)
					{
						anio = it->c_str();
						validacion = true;
					}
				}
			}

			if(listaFecha.size() == 3)
			{
				if (atoi((it->c_str())) > 0 && atoi((it->c_str())) <= DIAS)
				{
					dia = it->c_str();
					it++;
					if (atoi((it->c_str())) > 0 && atoi((it->c_str())) <= MESES)
					{
						mes = it->c_str();
						it++;
						if (atoi((it->c_str())) > MINIMO_A�OS && atoi((it->c_str())) <= MAXIMO_A�OS)
						{
							anio = it->c_str();
							validacion = true;
						}
					}
				}
			}
		}
	}

	return validacion;
}


bool VentanaEstadistica::validarSeleccion(string &seleccion)
{
	bool validacion = false;
	seleccion = "";
	if (this->cbEvolucionUsuario->getChecked())
		seleccion = "ConsultaEvolucionUsuarios";
	else if (this->cbEvolucionUsuarioConectado->getChecked())
		seleccion = "ConsultaEvolucionUsuariosConectados";
	else if (this->cbUsuariosConectados->getChecked())
		seleccion = "ConsultaListadoUsuariosConectados";
	else if (this->cbUsuariosRegistrados->getChecked())
		seleccion = "ConsultaListadoUsuariosRegistrados";
	else if (this->cbRanking->getChecked())
		seleccion = "ConsultaRanking";

	if (seleccion.length() > 0)
		validacion = true;

	return validacion;
}
string VentanaEstadistica::getUsuario() {
	return this->usuario;
}
int VentanaEstadistica::getSesionId() {
	return this->sessionId;
}
bool VentanaEstadistica::getCancelado() {
	return this->cancelado;
}
