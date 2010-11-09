#ifndef _VENTANACONFIGURACION_H__
#define _VENTANACONFIGURACION_H__

#include "SDL.h" 
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <list>
#include "Panel.h"
#include "Boton.h"
#include <windows.h>
#include "VentanaBase.h"
#include "Mensaje.h"

using namespace std;

class VentanaConfiguracion: public VentanaBase {
private:

	TextBox* textboxIP;
	TextBox* textboxPuerto;
	Etiqueta* mensaje;
	list<ElementoGrafico*> elementos;
	list<ComponentePanel*> componentes;

	bool conectado;

	bool manejarEventos(SDL_Event* event);
	bool ejecutarEvento(string controlId);
	void lanzarEvento(int codigoEvento);
	void refrescar(SDL_Surface* superficie);
	void configurarControles();
	
protected:
	virtual void dibujarSobreSup(SDL_Surface* superficie);
	virtual void dibujar(SDL_Surface* superficie);

public:
	VentanaConfiguracion(void);
	virtual ~VentanaConfiguracion(void);
	void agregarComponentePanel(ComponentePanel* componente);

	//obligatorias (heredadas de Ventana)
	virtual void iniciar();
	virtual void mostrarMensaje(string mensaje);
	virtual void agregarElementoGrafico(ElementoGrafico* elemento);
	bool getConectado();

};

#endif //_VENTANACONFIGURACION_H__

