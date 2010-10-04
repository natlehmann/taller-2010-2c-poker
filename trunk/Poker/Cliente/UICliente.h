#pragma once

#include <stdlib.h>
#include <string>
#include <iostream>
#include <list>
#include "Cliente.h"

using namespace std;

class UICliente
{
	/*
	enum eMenu {MP=1, TO, OP, XML};
	enum eOperacion {SUMA=1, RESTA, MULTIPLICACION, DIVISION};
	*/

	private:
		/*
		bool cerrarAplicacion;
		int opcionMenu;
		bool hayError;
		string msgError;
		string entrada;
		list<string> lstOperandos; // Lista con los operandos ingresados por el usuario
		eOperacion tipoOperacion;
		string resultado;
		*/
		

		
		//static Cliente* cliente;		

		static bool conectarServidor();

		
		/*
		// Metodos de impresion de Menues
		void menuPrincipal();
		void menuTipoOperaciones();
		void menuOperaciones();
		
		// Entrada de opcion de Menu
		void leerOpcionMenu();

		// Entrada general de datos
		void leerEntrada();
		
		//void ejecutarAccionMP();
		void ejecutarAccionTO();
		//void ejecutarAccionO();
		
		void ejecutarOperaciones(bool manual);

		bool validarOpcionMenu(eMenu tipoMenu);
		void limpiarPantalla();
		void mostrarEncabezado(string mensaje);
		void reingresarOpcionMenu();

		
		bool desconectarServidor();
		void procesarEntradaOperandos();
		void procesarArchivoXML();
		void enviarOperacion();
		//void mostrarResultado();

		// Metodos 
		void agregarOperando();
		void limpiarListaOperandos();
		void hacerUnaPausa();
		*/
		UICliente(void);

	public:
		
		virtual ~UICliente(void);

		static void iniciarAplicacion();
		static void mostrarMensaje(string msg, bool ingresaDatos = true);
		static void finalizar();

		static Cliente* getCliente();
};
