#ifndef _VENTANAADMINISTRACION_H__
#define _VENTANAADMINISTRACION_H__

#include "SDL.h" 
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <list>
#include <windows.h>
#include "Boton.h"
#include "VentanaBase.h"
#include "Mensaje.h"
#include "Panel.h"

using namespace std;

class VentanaAdministracion: public VentanaBase {
private:

	Etiqueta* etNombre;
	Etiqueta* etFichas;
	TextBox* txCantComprar;
	TextBox* txRutaImagen;
	Etiqueta* mensaje;
	list<ElementoGrafico*> elementos;
	list<ComponentePanel*> componentes;

	string usuario; 
	int sessionId;
	int cantFichas;
	bool irMesa;
	bool verEstadisticas;
	bool cancelado;

	void actualizarFichas(int cantFichasCompradas);
	bool manejarEventos(SDL_Event* event);
	bool ejecutarPreEvento(string controlId);
	bool ejecutarEvento(string controlId);
	void lanzarEvento(int codigoEvento);
	void refrescar(SDL_Surface* superficie);
	void configurarControles();
	
protected:
	virtual void dibujarSobreSup(SDL_Surface* superficie);
	virtual void dibujar(SDL_Surface* superficie);

public:
	VentanaAdministracion(string usuario, int sessionId, int cantFichas);
	virtual ~VentanaAdministracion(void);
	void agregarComponentePanel(ComponentePanel* componente);
	string getUsuario();
	int getSesionId();
	int getCantFichas();
	bool getIrMesa();
	bool getVerEstadisticas();
	bool getCancelado();

	//obligatorias (heredadas de Ventana)
	virtual void iniciar();
	virtual void mostrarMensaje(string mensaje);
	virtual void agregarElementoGrafico(ElementoGrafico* elemento);


};

#endif //_VENTANAADMINISTRACION_H__

