#ifndef _VENTANAESTADISTICA_H__
#define _VENTANAESTADISTICA_H__

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

#define SELECCION_MAYUSCULA "X"
#define SELECCION "x"
#define DIAS 31
#define MESES 12
#define	MINIMO_AÑOS 1900
#define MAXIMO_AÑOS 9999

using namespace std;

class VentanaEstadistica: public VentanaBase {
private:

	TextBox* txFecha;
	CheckBox* cbEvolucionUsuario;
	CheckBox* cbEvolucionUsuarioConectado;
	CheckBox* cbRanking;
	CheckBox* cbUsuariosConectados;
	CheckBox* cbUsuariosRegistrados;
	Etiqueta* mensaje;
	list<ElementoGrafico*> elementos;
	list<ComponentePanel*> componentes;


	string dia;
	string mes;
	string anio;
	string usuario; 
	int sessionId;
	bool cancelado;

	bool manejarEventos(SDL_Event* event);
	bool ejecutarPreEvento(string controlId);
	bool ejecutarEvento(string controlId);
	void lanzarEvento(int codigoEvento);
	void refrescar(SDL_Surface* superficie);
	void configurarControles();

	void checkExcluyentes(string controlId);
	bool validarFecha(string fecha);
	bool validarSeleccion(string &seleccion);
	
protected:
	virtual void dibujarSobreSup(SDL_Surface* superficie);
	virtual void dibujar(SDL_Surface* superficie);

public:
	VentanaEstadistica(string usuario, int sessionId);
	virtual ~VentanaEstadistica(void);
	void agregarComponentePanel(ComponentePanel* componente);

	//obligatorias (heredadas de Ventana)
	virtual void iniciar();
	virtual void mostrarMensaje(string mensaje);
	virtual void agregarElementoGrafico(ElementoGrafico* elemento);
	string getUsuario();
	int getSesionId();
	bool getCancelado();

};

#endif //_VENTANAESTADISTICA_H__

