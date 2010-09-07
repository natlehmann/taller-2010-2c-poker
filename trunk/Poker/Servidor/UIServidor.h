#pragma once

#include <stdlib.h>
#include <string>
#include <iostream>
#include "General.h"
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
		void salirAplicacion();

		void limpiarPantalla();
		void mostrarMensaje(string msg, bool ingresaDatos = true);
		
	public:
		UIServidor(void);
		virtual ~UIServidor(void);

		void iniciarAplicacion();
};