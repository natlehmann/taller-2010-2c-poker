#include "UIServidor.h"

UIServidor::UIServidor(void)
{
	this->cerrarAplicacion = false;
	this->opcionMP = 0;
	this->entrada = "";
}

UIServidor::~UIServidor(void)
{
}

void UIServidor::iniciarAplicacion()
{
	bool volver = true;

	while (!this->cerrarAplicacion)
	{
		if (volver)
		{
			limpiarPantalla();
			menuPrincipal();
			leerEntrada();
			volver = false;
		}
		
		this->opcionMP = General::getEntero(this->entrada);
		
		if ((this->opcionMP >= 1)&&(this->opcionMP <= 2))
		{
			ejecutarAccion();
			volver = true;
		}

		else
		{
			mostrarMensaje("EL VALOR '" + this->entrada + "' NO ES UNA OPCION VALIDA !!!", false);
			mostrarMensaje("INGRESE NUEVAMENTE UNA OPCION DEL MENU:");
			leerEntrada();
			volver = false;
		}
	}
	
}

void UIServidor::menuPrincipal()
{
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
	bool conecto = false;
	bool preguntar = true;
	string ip = "";
	int puerto = 0;

	while (!salir)
	{
		mostrarMensaje("INGRESE EL PUERTO DE CONEXION DEL SERVIDOR: ");
		leerEntrada();

		puerto = General::getEntero(this->entrada);

		if (puerto > 0) 
		{
			mostrarMensaje("INTENTANDO INICIAR SERVIDOR ...", false);
			
			servidor = new Servidor(puerto);
			servidor->iniciarConexion();

			mostrarMensaje("EL SERVIDOR A SIDO INICIADO EN FORMA EXITOSA !!!", false);
			mostrarMensaje("PARA DESCONECTAR EL SERVIDOR PULSE EL CARACTER 'x'", false);

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
			mostrarMensaje("EL PUERTO '" + this->entrada + "' ES INVALIDO !!! ", false);

			while (preguntar)
			{
				mostrarMensaje("DESEA INGRESAR NUEVAMENTE EL PUERTO DE CONEXION [S/N]? ");
				leerEntrada();

				if (General::validarSiNo(this->entrada))
				{
					preguntar = false;

					if (this->entrada == _NO_)
						salir = true;
				}
			}
			preguntar = true;
		}
	}
}

void UIServidor::detenerServidor()
{
	// Se intenta detener el servidor
	servidor->finalizarConexion();
	mostrarMensaje("SE HA DETENIDO EL SERVIDOR EN FORMA EXITOSA!!! ", false);
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