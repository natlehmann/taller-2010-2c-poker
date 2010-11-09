#include "UIServidor.h"
#include "UtilTiposDatos.h"
#include "RecursosServidor.h"
#include "AccesoDatos.h"

#include <cstdlib>

UIServidor::UIServidor(void)
{
	this->cerrarAplicacion = false;
	this->opcionMP = 0;
	this->entrada = "";
	this->servidor = NULL;
}

UIServidor::~UIServidor(void)
{
	if (this->servidor != NULL) {
		delete(this->servidor);
	}
}

void UIServidor::iniciarAplicacion()
{
	bool volver = true;

	while (!this->cerrarAplicacion)
	{
		if (volver)
		{
			menuPrincipal();
			leerEntrada();
			volver = false;
		}
		
		this->opcionMP = UtilTiposDatos::getEntero(this->entrada);
		
		if ((this->opcionMP >= 1)&&(this->opcionMP <= 2))
		{
			ejecutarAccion();
			volver = true;
		}

		else
		{
			mostrarMensaje("EL VALOR '" + this->entrada + "' NO ES UNA OPCION VALIDA !!!", false);
			mostrarMensaje("INGRESE NUEVAMENTE UNA OPCION DEL MENU: ");
			leerEntrada();
			volver = false;
		}
	}
	
}

void UIServidor::menuPrincipal()
{
	limpiarPantalla();
	cout << "****************************************************" << endl;
	cout << "*********  Servidor de Operaciones Remotas  ********" << endl;
	cout << "****************************************************" << endl;
	cout << endl;
	cout << "   1. INICIAR SERVIDOR." << endl;
	cout << "   2. CERRAR APLICACION." << endl;
	cout << endl;
	cout << "INGRESE LA OPCION ELEGIDA: ";
}

void UIServidor::leerEntrada()
{
	getline(cin, entrada);
	this->entrada = MensajesUtil::trim(this->entrada);
}

void UIServidor::ejecutarAccion()
{
	switch (this->opcionMP)
	{
		case 1:	this->iniciarServidor();
				break;

		case 2: this->cerrarAplicacion = true;
				break;
	}
}

void UIServidor::iniciarServidor()
{
	bool salir = false;
	bool preguntar = true;
	int puerto = UtilTiposDatos::getEntero(
		RecursosServidor::getConfig()->get("servidor.conexion.puerto"));

	while (!salir)
	{
		if (puerto > 0) 
		{
			mostrarMensaje("INTENTANDO INICIAR SERVIDOR ...", false);
			
			servidor = new Servidor(puerto);
			servidor->iniciarConexion();

			mostrarMensaje("EL SERVIDOR A SIDO INICIADO EN FORMA EXITOSA !!!", false);
			mostrarMensaje("PARA DESCONECTAR EL SERVIDOR PULSE EL CARACTER 'x'", false);

			// Esta funcion genera las tablas del sistema en el caso de que se ejecute por primera vez el servidor
			this->inicializarDatos();
			
			while (!salir)
			{
				leerEntrada();
		
				if (this->entrada.compare("x")==0 || this->entrada.compare("X") ==0)
				{
					this->detenerServidor();
					salir = true;
				}
			}		
		}
		else
		{
			mostrarMensaje("NO SE HA PODIDO LEVANTAR EL SERVIDOR EN EL PUERTO "
				+ RecursosServidor::getConfig()->get("servidor.conexion.puerto"), false);
			exit(1);
		}
	}
}

void UIServidor::detenerServidor()
{
	// Se intenta detener el servidor
	servidor->finalizarConexion();
	mostrarMensaje("SE HA DETENIDO EL SERVIDOR EN FORMA EXITOSA!!! ", false);
	hacerUnaPausa();
}

void UIServidor::mostrarMensaje(string msg, bool ingresaDatos)
{
	std::cout << msg;

	if (!ingresaDatos)
		std::cout << std::endl;
}
void UIServidor::limpiarPantalla()
{
	system("CLS");
}

void UIServidor::hacerUnaPausa()
{
	string buffer;
	this->mostrarMensaje("\n\nPRESIONE INTRO PARA CONTINUAR...",false);
	getline(cin, buffer);
}

void UIServidor::inicializarDatos()
{
	AccesoDatos ad;
	ad.inicializarBaseDatos();
}
