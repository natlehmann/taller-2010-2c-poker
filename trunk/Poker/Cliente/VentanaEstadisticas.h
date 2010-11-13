#pragma once
#include "VentanaBase.h"
#include "SDL.h" 
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <list>
#include "Panel.h"
#include "Boton.h"
#include <windows.h>
#include "Mensaje.h"

#define SELECCION_MAYUSCULA "X"
#define SELECCION "x"
#define DIAS 31
#define MESES 12
#define	MINIMO_AÑOS 1900
#define MAXIMO_AÑOS 9999

class VentanaEstadisticas :
	public VentanaBase
{
private:
	TextBox* textboxFecha;
	TextBox* textboxEvolUser;
	TextBox* textboxEvolUserConnect;
	
	TextBox* textboxListUserReg;
	TextBox* textboxListUserCon;
	TextBox* textboxRanking;

	Etiqueta* mensaje;

	list<ElementoGrafico*> elementos;
	list<ComponentePanel*> componentes;

	string usuario;
	int sessionId;
	bool consulto;
	bool cancelado;
	
	void configurarControles();
	void refrescar(SDL_Surface* superficie);
	bool manejarEventos(SDL_Event* event);
	bool ejecutarPreEvento(string controlId);
	bool ejecutarEvento(string controlId);
	void lanzarEvento(int codigoEvento);

	bool validarFecha(string fecha);
	bool validarSeleccion(string texto);
	bool seleccionUnaOpciónOK();

protected:
	void dibujar(SDL_Surface* superficie);
	virtual void dibujarSobreSup(SDL_Surface* superficie);

public:
	VentanaEstadisticas(string usuario, int sessionId);
	~VentanaEstadisticas(void);

	virtual void iniciar();

	virtual void agregarElementoGrafico(ElementoGrafico* elemento);

	void agregarComponentePanel(ComponentePanel* componente);
	
	virtual void mostrarMensaje(string mensaje);

	bool getConsulto();
	bool getCancelado();
};
