#ifndef _VENTANANUEVOJUGADOR_H__
#define _VENTANANUEVOJUGADOR_H__

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

using namespace std;

class VentanaNuevoJugador: public VentanaBase {
private:

	TextBox* txNombre;
	TextBox* txApellido;
	TextBox* txUsuario;
	TextBox* txPassword;
	TextBox* txConfirmPassword;
	Etiqueta* mensaje;
	list<ElementoGrafico*> elementos;
	list<ComponentePanel*> componentes;

	bool guardado;
	bool cancelado;

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
	VentanaNuevoJugador(void);
	virtual ~VentanaNuevoJugador(void);
	void agregarComponentePanel(ComponentePanel* componente);

	//obligatorias (heredadas de Ventana)
	virtual void iniciar();
	virtual void mostrarMensaje(string mensaje);
	virtual void agregarElementoGrafico(ElementoGrafico* elemento);
	bool getGuardado();
	bool getCancelado();

};

#endif //_VENTANANUEVOJUGADOR_H__

