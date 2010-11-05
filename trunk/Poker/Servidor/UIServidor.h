#pragma once

#include <stdlib.h>
#include <string>
#include <iostream>
#include "Servidor.h"

using namespace std;

class UIServidor
{
	private:
		bool cerrarAplicacion;
		int opcionMP;
		string entrada;
		Servidor* servidor;

		void menuPrincipal();
		void leerEntrada();
		void ejecutarAccion();

		void iniciarServidor();
		void detenerServidor();

		void limpiarPantalla();
		void mostrarMensaje(string msg, bool ingresaDatos = true);
		void hacerUnaPausa();

		// Esta funcion sirve crea las tablas del sistema en caso de que no existan
		void inicializarDatos();
		
	public:
		UIServidor(void);
		virtual ~UIServidor(void);

		void iniciarAplicacion();
};
