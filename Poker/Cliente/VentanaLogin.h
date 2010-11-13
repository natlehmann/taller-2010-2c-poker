#ifndef _VENTANALOGIN_H__
#define _VENTANALOGIN_H__

#include "SDL.h" 
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <list>
#include "Panel.h"
#include "Boton.h"
#include "CheckBox.h"
#include <windows.h>
#include "VentanaBase.h"
#include "Mensaje.h"

using namespace std;

class VentanaLogin: public VentanaBase {
private:

	TextBox* txUsuario;
	TextBox* txPassword;
	CheckBox* cbVirtual;
	CheckBox* cbObservador;
	Etiqueta* mensaje;
	list<ElementoGrafico*> elementos;
	list<ComponentePanel*> componentes;

	string usuario; 
	int sessionId;
	int cantFichas;
	bool conectado;
	bool cancelado;
	bool nuevo;

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
	VentanaLogin(void);
	virtual ~VentanaLogin(void);
	void agregarComponentePanel(ComponentePanel* componente);

	//obligatorias (heredadas de Ventana)
	virtual void iniciar();
	virtual void mostrarMensaje(string mensaje);
	virtual void agregarElementoGrafico(ElementoGrafico* elemento);
	string getUsuario();
	int getSesionId();
	int getCantFichas();
	bool getConectado();
	bool getCancelado();
	bool getNuevo();

};

#endif //_VENTANALOGIN_H__

