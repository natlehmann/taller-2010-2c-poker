#include "VentanaEstadisticas.h"
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
#include "OpUIClienteSolicitarEstadistica.h"
#include <typeinfo.h>
#include <cstdlib>

VentanaEstadisticas::VentanaEstadisticas(string usuario, int sessionId)
{
	UICliente::iniciarSDL();
	this->usuario = usuario;
	this->sessionId = sessionId;
	this->consulto = false;
	this->cancelado = false;
	this->id = "";
	this->posX = 0;
	this->posY = 0;
	this->offset = new SDL_Rect();
	this->contorno = new SDL_Rect();
	this->contornoConOffset = new SDL_Rect();

	dia = "";
	mes = "";
	anio = "";

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
	this->setAncho(ancho);
	this->setAlto(alto);
	this->altoFila = this->getAlto()/20;
	this->anchoColumna = this->getAncho()/20;

	this->contorno->x = 0;
	this->contorno->y = 0;
	this->contorno->w = this->getAncho();
	this->contorno->h = this->getAlto();
	
	this->offset->x = this->anchoColumna;
	this->offset->y = this->altoFila;
	
	this->pantalla = SDL_SetVideoMode(this->ancho, this->alto, RESOLUCION_PANTALLA, SDL_SWSURFACE);

	if (this->pantalla == NULL) {
		throw UIException("No se pudo inicializar la ventana de la aplicacion.","E");
	}

	SDL_WM_SetCaption(RecursosCliente::getConfig()->get("cliente.configuracion.mensajeEstadisticas").c_str(), NULL); 
	
	this->fondo = new Color(RecursosCliente::getConfig()->get("cliente.tema.default.menu.fondo"));
	SDL_FillRect(pantalla, contorno, this->fondo->toUint32(pantalla));

	this->configurarControles();
	this->hayCambios = true;
}

VentanaEstadisticas::~VentanaEstadisticas(void)
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
}

void VentanaEstadisticas::iniciar()
{
	//dibuja los controles en la pantalla
	this->dibujar(NULL);

	bool listo = false;
	SDL_Event event;

	while(!listo) {
		while(SDL_WaitEvent(&event) && !listo) {
			listo = this->manejarEventos(&event);

			if( (event.type == SDL_QUIT)
				|| (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) ){
                listo = true;
            }

		}
	}
}

void VentanaEstadisticas::configurarControles(){
	Etiqueta* tagEstadistica = new Etiqueta("Ingrese a continuación la fecha de consulta:");
	tagEstadistica->setPosX(this->anchoColumna);
	tagEstadistica->setPosY(this->altoFila);
	tagEstadistica->setAlto(this->altoFila);
	tagEstadistica->setAncho(this->anchoColumna*2);
	tagEstadistica->setFondo(this->fondo);
	tagEstadistica->getFuente()->setTamanio(16);
	this->agregarElementoGrafico(tagEstadistica);

	Etiqueta* tagFormatoFecha = new Etiqueta("Fecha DD/MM/AAAA o MM/AAAA o AAAA:");
	tagFormatoFecha->setPosX(this->anchoColumna);
	tagFormatoFecha->setPosY(this->altoFila*3);
	tagFormatoFecha->setAlto(this->altoFila);
	tagFormatoFecha->setAncho(this->anchoColumna*2);
	tagFormatoFecha->setFondo(this->fondo);
	tagFormatoFecha->getFuente()->setTamanio(16);
	this->agregarElementoGrafico(tagFormatoFecha);

	textboxFecha = new TextBox("");
	textboxFecha->setPosX(this->anchoColumna);
	textboxFecha->setPosY(this->altoFila*2);
	textboxFecha->setAlto(this->altoFila);
	textboxFecha->setAncho(this->anchoColumna*5);
	textboxFecha->setHabilitado(true);
	//textboxIP->getFuente()->setTamanio(14);
	this->agregarComponentePanel(textboxFecha);

	Etiqueta* tagLeyenda = new Etiqueta("Seleccione una opción con una X");
	tagLeyenda->setPosX(this->anchoColumna);
	tagLeyenda->setPosY(this->altoFila*4);
	tagLeyenda->setAlto(this->altoFila);
	tagLeyenda->setAncho(this->anchoColumna*6);
	tagLeyenda->setFondo(this->fondo);
	tagLeyenda->getFuente()->setTamanio(16);
	this->agregarElementoGrafico(tagLeyenda);

	Etiqueta* tagEvolUser = new Etiqueta("Evolucion de los Usuarios:");
	tagEvolUser->setPosX(this->anchoColumna);
	tagEvolUser->setPosY(this->altoFila*5);
	tagEvolUser->setAlto(this->altoFila);
	tagEvolUser->setAncho(this->anchoColumna*2);
	tagEvolUser->setFondo(this->fondo);
	tagEvolUser->getFuente()->setTamanio(16);
	this->agregarElementoGrafico(tagEvolUser);

	Etiqueta* tagEvolUserConnect = new Etiqueta("Evolucion de los Usuarios Conectados:");
	tagEvolUserConnect->setPosX(this->anchoColumna);
	tagEvolUserConnect->setPosY(this->altoFila*6);
	tagEvolUserConnect->setAlto(this->altoFila);
	tagEvolUserConnect->setAncho(this->anchoColumna);
	tagEvolUserConnect->setFondo(this->fondo);
	tagEvolUserConnect->getFuente()->setTamanio(16);
	this->agregarElementoGrafico(tagEvolUserConnect);

	//Opciones para Listado de los Usuarios Registrados
	Etiqueta* tagListUserReg = new Etiqueta("Listado de los Usuarios Registrados:");
	tagListUserReg->setPosX(this->anchoColumna);
	tagListUserReg->setPosY(this->altoFila*7);
	tagListUserReg->setAlto(this->altoFila);
	tagListUserReg->setAncho(this->anchoColumna*6);
	tagListUserReg->setFondo(this->fondo);
	tagListUserReg->getFuente()->setTamanio(16);
	this->agregarElementoGrafico(tagListUserReg);

	//Opciones para Listado de los Usuarios Conectados
	Etiqueta* tagListUserCon = new Etiqueta("Listado de los Usuarios Conectados:");
	tagListUserCon->setPosX(this->anchoColumna);
	tagListUserCon->setPosY(this->altoFila*8);
	tagListUserCon->setAlto(this->altoFila);
	tagListUserCon->setAncho(this->anchoColumna*6);
	tagListUserCon->setFondo(this->fondo);
	tagListUserCon->getFuente()->setTamanio(16);
	//setear color
	this->agregarElementoGrafico(tagListUserCon);

	//Opciones para Ranking
	Etiqueta* tagRanking = new Etiqueta("Ranking:");
	tagRanking->setPosX(this->anchoColumna);
	tagRanking->setPosY(this->altoFila*9);
	tagRanking->setAlto(this->altoFila);
	tagRanking->setAncho(this->anchoColumna*6);
	tagRanking->setFondo(this->fondo);
	tagRanking->getFuente()->setTamanio(16);
	this->agregarElementoGrafico(tagRanking);

	textboxEvolUser = new TextBox("");
	textboxEvolUser->setPosX(this->anchoColumna*8);
	textboxEvolUser->setPosY(this->altoFila*5);
	textboxEvolUser->setAlto(this->altoFila);
	textboxEvolUser->setAncho(this->anchoColumna);
	textboxEvolUser->setHabilitado(true);
	//textboxIP->getFuente()->setTamanio(14);
	this->agregarComponentePanel(textboxEvolUser);
	
	textboxEvolUserConnect= new TextBox("");
	textboxEvolUserConnect->setPosX(this->anchoColumna*8);
	textboxEvolUserConnect->setPosY(this->altoFila*6);
	textboxEvolUserConnect->setAlto(this->altoFila);
	textboxEvolUserConnect->setAncho(this->anchoColumna);
	textboxEvolUserConnect->setHabilitado(true);
	//textboxIP->getFuente()->setTamanio(14);
	this->agregarComponentePanel(textboxEvolUserConnect);

	textboxListUserReg = new TextBox("");
	textboxListUserReg->setPosX(this->anchoColumna*8);
	textboxListUserReg->setPosY(this->altoFila*7);
	textboxListUserReg->setAlto(this->altoFila);
	textboxListUserReg->setAncho(this->anchoColumna);
	textboxListUserReg->setHabilitado(true);
	//textboxIP->getFuente()->setTamanio(14);
	this->agregarComponentePanel(textboxListUserReg);

	textboxListUserCon = new TextBox("");
	textboxListUserCon->setPosX(this->anchoColumna*8);
	textboxListUserCon->setPosY(this->altoFila*8);
	textboxListUserCon->setAlto(this->altoFila);
	textboxListUserCon->setAncho(this->anchoColumna);
	textboxListUserCon->setHabilitado(true);
	//textboxIP->getFuente()->setTamanio(14);
	this->agregarComponentePanel(textboxListUserCon);

	textboxRanking = new TextBox("");
	textboxRanking->setPosX(this->anchoColumna*8);
	textboxRanking->setPosY(this->altoFila*9);
	textboxRanking->setAlto(this->altoFila);
	textboxRanking->setAncho(this->anchoColumna);
	textboxRanking->setHabilitado(true);
	//textboxIP->getFuente()->setTamanio(14);
	this->agregarComponentePanel(textboxRanking);

	this->mensaje = new Etiqueta("");
	this->mensaje->setPosX(this->anchoColumna);
	this->mensaje->setPosY(this->altoFila*10);
	this->mensaje->setAlto(this->altoFila);
	this->mensaje->setAncho(this->anchoColumna*15);
	this->mensaje->setFondo(new Color(fondo->getRed(), fondo->getGreen(), fondo->getBlue()));
	this->mensaje->setVisible(false);
	this->agregarElementoGrafico(this->mensaje);


	Boton* bConRanking = new Boton("Consultar");
	bConRanking->setId("consulta");
	bConRanking->setPosX(this->anchoColumna*3);
	bConRanking->setPosY(this->altoFila*11);
	bConRanking->setAlto(this->altoFila);
	bConRanking->setAncho(this->anchoColumna*2);
	bConRanking->setHabilitado(true);
	this->agregarComponentePanel(bConRanking);

	//Boton para volver al Menu Administracion
	Boton* bVolverMenuPrincipal = new Boton("Volver a Menu Principal");
	bVolverMenuPrincipal->setId("volverMenuAdm");
	bVolverMenuPrincipal->setPosX(this->anchoColumna*3);
	bVolverMenuPrincipal->setPosY(this->altoFila*12);
	bVolverMenuPrincipal->setAlto(this->altoFila);
	bVolverMenuPrincipal->setAncho(this->anchoColumna*2);
	bVolverMenuPrincipal->setHabilitado(true);
	this->agregarComponentePanel(bVolverMenuPrincipal);
}

void VentanaEstadisticas::agregarElementoGrafico(ElementoGrafico* elemento) {
	this->elementos.push_back(elemento);
	elemento->setVentana(this);
}

void VentanaEstadisticas::dibujar(SDL_Surface* superficie){

	if (this->hayCambios) {
		if (superficie != NULL) {
			this->dibujarSobreSup(superficie);

		} else {
			this->dibujarSobreSup(this->pantalla);
		}
		this->hayCambios = false;
	}
}

void VentanaEstadisticas::agregarComponentePanel(ComponentePanel* componente) {
	this->componentes.push_back(componente);
	componente->setVentana(this);
}

void VentanaEstadisticas::dibujarSobreSup(SDL_Surface* superficie){

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

void VentanaEstadisticas::mostrarMensaje(string mensaje){
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

void VentanaEstadisticas::refrescar(SDL_Surface* superficie) {
		if(SDL_Flip(superficie) == -1) { 
		throw UIException("Error al redibujar la pantalla completa.","E");
	} 
}

bool VentanaEstadisticas::manejarEventos(SDL_Event* event){


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
void VentanaEstadisticas::lanzarEvento(int codigoEvento) {
	SDL_Event event;

	event.type = SDL_USEREVENT;
	event.user.code = codigoEvento;
	event.user.data1 = 0;
	event.user.data2 = 0;
	SDL_PushEvent(&event);
}
bool VentanaEstadisticas::ejecutarPreEvento(string controlId){

	if (MensajesUtil::sonIguales(controlId, "btGuardar"))
	{
		mostrarMensaje("Espere, Consultando Estadisticas.");
		lanzarEvento(100);
		return true;
	}

	return false;
}
bool VentanaEstadisticas::ejecutarEvento(string controlId)
{
	if (MensajesUtil::sonIguales(controlId, "consulta"))
	{
		if(validarFecha(textboxFecha->getTexto()))
		{
			string seleccion;
			if (seleccionUnaOpcionOK(seleccion))
			{
				FabricaOperacionesCliente fab;
				OperacionUICliente* operacion = NULL;

				vector<string> parametros;
				bool solicitoOK = false;
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
					//mostrar el nombre del archivo
					pathArchivo = ( static_cast<OpUIClienteSolicitarEstadistica *> (operacion))->getPathArchivo();
					solicitoOK = true;
				}
				delete (operacion);

				if (solicitoOK)
				{
					//parametrosArchivo.push_back(pathArchivo);
					OperacionUICliente* operacionPedirArchivo = fab.newOperacion("OpUIClienteSolicitarArchivo",pathArchivo);
					if (operacionPedirArchivo->ejecutarAccion(NULL))
					{
						mostrarMensaje("Se ha guardado el archivo:  " + pathArchivo);
						lanzarEvento(100);
						return false;	
					}
					else
					{
						mostrarMensaje("No se ha podido guardar el archivo:  " + pathArchivo);
						lanzarEvento(100);
						return false;	
					}
				}
				else
				{
					//TODO
				}

				}
			else
			{
				mostrarMensaje("Debe seleccionar solo una opción.");
				lanzarEvento(100);
				return false;
			}
		}
		else
		{
			mostrarMensaje("Verifique el formato de fecha.");
			lanzarEvento(100);
			return false;
		}
	}
	if (MensajesUtil::sonIguales(controlId, "volverMenuAdm"))
	{
		//aca tiene que volver al menu principal
	}

	return false;
}

bool VentanaEstadisticas::validarFecha(string fecha)
{
	dia = "";
	mes = "";
	anio = "";
	if(fecha.length() == 0)
	{
		return false;
	}
	else
	{
		list<string> listaFecha = MensajesUtil::split(fecha,"/");
		if(listaFecha.size() < 4)
		{
			list<string>::iterator it = listaFecha.begin();
			
			if(listaFecha.size() == 1)
			{
				if (atoi((it->c_str())) > MINIMO_AÑOS && atoi((it->c_str())) < MAXIMO_AÑOS)
				{
					anio = it->c_str();
					return true;
				}
				else 
					return false;
			}

			if(listaFecha.size() == 2)
			{
				if (atoi((it->c_str())) > 0 && atoi((it->c_str())) <= MESES)
				{
					mes = it->c_str();
					it++;
					if (atoi((it->c_str())) > MINIMO_AÑOS && atoi((it->c_str())) <= MAXIMO_AÑOS)
					{
						anio = it->c_str();
						return true;
					}
				}
				else return false;
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
						if (atoi((it->c_str())) > MINIMO_AÑOS && atoi((it->c_str())) <= MAXIMO_AÑOS)
						{
							anio = it->c_str();
							return true;
						}
					}
					else return false;
				}
				else return false;
			}
		}
		else 
			return false;
	}
}

bool VentanaEstadisticas::validarSeleccion(string texto)
{
	if (MensajesUtil::sonIguales(texto,SELECCION) || MensajesUtil::sonIguales(texto,SELECCION_MAYUSCULA))
		return true;
	else return false;
}

bool VentanaEstadisticas::seleccionUnaOpcionOK(string &seleccion)
{
	int cantidadSeleccionadaOK = 0;
	int cantidadSeleccionada = 0;
	if (validarSeleccion(textboxEvolUser->getTexto()))
	{
		cantidadSeleccionadaOK++;
		seleccion = "ConsultaEvolucionUsuarios";
	}
	if (textboxEvolUser->getTexto().length() != 0 ) 
		cantidadSeleccionada++;
	if (validarSeleccion(textboxEvolUserConnect->getTexto()))
	{
		cantidadSeleccionadaOK++;
		seleccion = "ConsultaEvolucionUsuariosConectados";
	}
	if (textboxEvolUserConnect->getTexto().length() != 0 ) 
		cantidadSeleccionada++;
	if (validarSeleccion(textboxListUserCon->getTexto()))
	{
		cantidadSeleccionadaOK++;
		seleccion = "ConsultaListadoUsuariosConectados";
	}
	if (textboxListUserCon->getTexto().length() != 0 ) 
		cantidadSeleccionada++;
	if (validarSeleccion(textboxListUserReg->getTexto()))
	{
		cantidadSeleccionadaOK++;
		seleccion = "ConsultaListadoUsuariosRegistrados";
	}
	if (textboxListUserReg->getTexto().length() != 0 ) 
		cantidadSeleccionada++;
	if (validarSeleccion(textboxRanking->getTexto()))
	{
		cantidadSeleccionadaOK++;
		seleccion = "ConsultaRanking";
	}
	if (textboxRanking->getTexto().length() != 0 ) 
		cantidadSeleccionada++;
	if(cantidadSeleccionada == 1 && cantidadSeleccionadaOK == 1)
		return true;
	else return false;
}
bool VentanaEstadisticas::getConsulto() {
	return this->consulto;
}
bool VentanaEstadisticas::getCancelado() {
	return this->cancelado;
}