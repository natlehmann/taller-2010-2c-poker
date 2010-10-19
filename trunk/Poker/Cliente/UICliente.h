#pragma once

#include <stdlib.h>
#include <string>
#include <iostream>
#include <list>
#include "Cliente.h"
#include "SDL_thread.h" 
#include "Ventana.h"

using namespace std;

class UICliente
{
	private:
		
		static Cliente* cliente;	
		static SDL_Thread* threadRefresh;

		static bool conectarServidor();
		UICliente(void);

	public:
		
		virtual ~UICliente(void);

		static void iniciarAplicacion();
		static void lanzarThreads(Ventana* ventana);
		static void mostrarMensaje(string msg, bool ingresaDatos = true);
		static void finalizar();

		static Cliente* getCliente();
};
