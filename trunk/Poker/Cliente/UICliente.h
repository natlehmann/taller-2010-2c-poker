#pragma once

#include <stdlib.h>
#include <string>
#include <iostream>
#include <list>
#include "General.h"
#include "Cliente.h"

using namespace std;

class UICliente
{
	enum eMenu {MP=1, TO, OP, XML};
	enum eOperacion {SUMA=1, RESTA, MULTIPLICACION, DIVISION};

	private:
		bool cerrarAplicacion;
		int opcionMenu;
		bool hayError;
		string msgError;
		string entrada;
		list<string> lstOperandos; // Lista con los operandos ingresados por el usuario
		Cliente* cliente;
		eOperacion tipoOperacion;
		string resultado;

		// Metodos de impresion de Menues
		void menuPrincipal();
		void menuTipoOperaciones();
		void menuOperaciones();
		
		// Entrada de opcion de Menu
		void leerOpcionMenu();

		// Entrada general de datos
		void leerEntrada();
		
		void ejecutarAccionMP();
		void ejecutarAccionTO();
		void ejecutarAccionO();
		
		void ejecutarOperaciones(bool manual);

		bool validarOpcionMenu(eMenu tipoMenu);
		void limpiarPantalla();
		void mostrarMensaje(string msg, bool ingresaDatos = true);
		void mostrarEncabezado(string mensaje);
		void reingresarOpcionMenu();

		bool conectarServidor();
		bool desconectarServidor();
		void procesarEntradaOperandos();
		void procesarArchivoXML();
		void enviarOperacion();
		void mostrarResultado();

		// Metodos 
		void agregarOperando();
		void limpiarListaOperandos();


	public:
		UICliente(void);
		virtual ~UICliente(void);

		void iniciarAplicacion();
};
