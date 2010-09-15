#include "UICliente.h"
#include "ParserEntradaTeclado.h"
#include "MensajesUtil.h"
#include "XmlParserArchivo.h"
#include "DomTree.h"
#include "GeneradorRespuesta.h"
#include "UtilTiposDatos.h"
#include <fstream>

UICliente::UICliente(void)
{
	this->hayError = false;
	this->msgError = "";
	this->cerrarAplicacion = false;
	this->opcionMenu = 0;
	this->entrada = "";
	this->resultado = "";
}

UICliente::~UICliente(void)
{
	if (this->cliente != NULL) {
		delete (this->cliente);
	}
}

void UICliente::iniciarAplicacion()
{
	bool volverMenuMP = true;
	bool volverMenuTO = true;

	while (!this->cerrarAplicacion)
	{
		if (volverMenuMP)
		{
			menuPrincipal();
			leerOpcionMenu();
			volverMenuMP = false;
		}
		
		if (this->validarOpcionMenu(MP))
		{
			if (this->opcionMenu == 1)
			{
				if (conectarServidor())
				{
					while (!volverMenuMP)
					{
						if (volverMenuTO)
						{
							menuTipoOperaciones();
							leerOpcionMenu();
							volverMenuTO = false;
						}

						if (this->validarOpcionMenu(TO))
						{
							if (this->opcionMenu != 3)
							{
								ejecutarAccionTO();
								volverMenuTO = true;
							}
							else
							{
								if (this->desconectarServidor())
								{
									this->mostrarMensaje("SE HA DESCONECTADO CORRECTAMENTE", false);
									hacerUnaPausa();
									volverMenuMP = true;
									volverMenuTO = true;
								}
							}
						}
						else
							reingresarOpcionMenu();
					}
				}
				else
				{
					this->mostrarMensaje("NO SE HA PODIDO CONECTAR AL SERVIDOR", false);
					hacerUnaPausa();
					volverMenuMP = true;
				}
			}
			else
				this->cerrarAplicacion = true;
		}
		else
			reingresarOpcionMenu();
	}	
}

void UICliente::menuPrincipal()
{
	limpiarPantalla();
	cout << "****************************************************" << endl;
	cout << "*********  CLIENTE DE OPERACIONES REMOTAS  *********" << endl;
	cout << "****************************************************" << endl;
	cout << endl;
	cout << "   1. CONECTAR CON SERVIDOR." << endl;
	cout << "   2. CERRAR APLICACION." << endl;
	cout << endl;
	cout << "INGRESE LA OPCION ELEGIDA: ";
}

void UICliente::menuTipoOperaciones()
{
	limpiarPantalla();
	cout << "****************************************************" << endl;
	cout << "*********       OPERACIONES REMOTAS      **********" << endl;
	cout << "****************************************************" << endl;
	cout << endl;
	cout << "   1. EJECUTAR OPERACIONES MANUALES." << endl;
	cout << "   2. ENVIAR XML PRUEBA." << endl;
	cout << "   3. DESCONECTAR SERVIDOR." << endl;
	cout << endl;
	cout << "INGRESE LA OPCION ELEGIDA: ";
}

void UICliente::menuOperaciones()
{
	limpiarPantalla();
	cout << "**************************************************************" << endl;
	cout << "*********   EJECUCION MANUAL DE OPERACIONES REMOTAS   ********" << endl;
	cout << "**************************************************************" << endl;
	cout << endl;
	cout << "   1. SUMA." << endl;
	cout << "   2. RESTA." << endl;
	cout << "   3. MULTIPLICACION." << endl;
	cout << "   4. DIVISION." << endl;
	cout << "   5. VOLVER MENU ANTERIOR." << endl;
	cout << endl;
	cout << "INGRESE LA OPCION ELEGIDA: ";
}

void UICliente::leerOpcionMenu()
{
	getline(cin, this->entrada);
	this->entrada = MensajesUtil::trim(this->entrada);
	this->opcionMenu = UtilTiposDatos::getEntero(this->entrada);
}
void UICliente::leerEntrada()
{
	getline(cin, this->entrada);
	this->entrada = MensajesUtil::trim(this->entrada);
}

void UICliente::ejecutarAccionTO()
{
	switch (this->opcionMenu)
	{
		case 1:	this->ejecutarOperaciones(true);
				break;

		case 2: this->ejecutarOperaciones(false);
				break;
	}
}


void UICliente::ejecutarOperaciones(bool manual)
{
	bool volverMenuOP = true;
	bool salir = false;

	while (!salir)
	{
		if (manual)
		{
			if(volverMenuOP)
			{
				menuOperaciones();
				leerOpcionMenu();
				volverMenuOP = false;
			}

			if (this->validarOpcionMenu(OP))
			{
				if (this->opcionMenu != 5)
				{
					procesarEntradaOperandos();
					volverMenuOP = true;
				}
				else
					salir = true;
			}
			else
				reingresarOpcionMenu();
		}
		else
		{
			procesarArchivoXML();
			salir = true;
		}
	}
}
bool UICliente::conectarServidor()
{
	bool salir = false;
	bool conecto = false;
	bool preguntar = true;
	string ip = "";
	int puerto;

	while ((!salir)&&(!conecto))
	{
		if (ip=="")
		{
			mostrarMensaje("INGRESE LA IP DEL SERVIDOR: ");
			leerEntrada();
			ip = this->entrada;
		}
		
		mostrarMensaje("INGRESE EL PUERTO DE CONEXION DEL SERVIDOR: ");
		leerEntrada();
		puerto = UtilTiposDatos::getEntero(this->entrada);

		if (puerto > 0)  
		{
			mostrarMensaje("INTENTANDO CONECTAR CON EL SERVIDOR " + ip + " ...", false);
			
			cliente = new Cliente(puerto, ip);

			if (cliente->iniciarConexion())
			{
				mostrarMensaje("LA CONEXION CON EL SERVIDOR HA SIDO EXITOSA !!!", false);
				hacerUnaPausa();
				conecto = true;
			}
			else
			{
				mostrarMensaje("NO SE HA PODIDO ESTABLECER LA CONEXION CON EL SERVIDOR, INTENTELO MAS TARDE.", false);
				delete(cliente);

				while (preguntar)
				{
					mostrarMensaje("DESEA INTENTAR CONECTARSE NUEVAMENTE [S/N]? ");
					leerEntrada();

					if (UtilTiposDatos::validarSiNo(this->entrada))
					{
						preguntar = false;

						if ((this->entrada == _NO_)||(this->entrada  == _no_))
						{
							salir = true;
							conecto = false;
						}
					}
				}

				preguntar = true;
				ip = "";
			}
		}
		else
		{
			mostrarMensaje("EL PUERTO '" + this->entrada + "' ES INVALIDO !!! ", false);

			while (preguntar)
			{
				mostrarMensaje("DESEA INGRESAR NUEVAMENTE EL PUERTO DE CONEXION [S/N]? ");
				leerEntrada();

				if (UtilTiposDatos::validarSiNo(this->entrada))
				{
					preguntar = false;

					if ((this->entrada == _NO_)||(this->entrada  == _no_))
					{
						salir = true;
						conecto = false;
					}
				}
			}
			preguntar = true;
		}
	}

	return conecto;
}

bool UICliente::desconectarServidor()
{
	return cliente->finalizarConexion();
}
void UICliente::procesarArchivoXML()
{
	this->mostrarMensaje("INGRESE LA RUTA DEL XML QUE CONTIENE LAS OPERACIONES: ");
	this->leerEntrada();

	XmlParserArchivo* parser = NULL;

	try {
		parser = new XmlParserArchivo(this->entrada);

	} catch (PokerException&) {
		this->mostrarMensaje("No se ha podido procesar el archivo indicado.", false);
		hacerUnaPausa();
	}

	if (parser != NULL) {

		this->mostrarMensaje("INGRESE LA RUTA DEL ARCHIVO DE SALIDA: ", true); 
		this->leerEntrada();

		string archivoSalida = "";
		if (!MensajesUtil::esVacio(this->entrada)) {
			archivoSalida = this->entrada;
		}		

		ofstream salida(archivoSalida.c_str(), ios::out | ios::trunc);
		if (MensajesUtil::esVacio(archivoSalida) || !salida.is_open()) {
			this->mostrarMensaje("No se ha podido abrir el archivo " 
				+ archivoSalida + " para escritura.", false);
			hacerUnaPausa();

		} else {

			bool huboErrores = false;
			try {
				DomTree* domTree = parser->getSiguiente();

				while (domTree != NULL) {	
					
					if(cliente->enviarMsj(parser->toString(domTree)))
					{
						string respuestaServ;
						huboErrores = !cliente->recibirMsj(respuestaServ);
						// TODO: FALTA CHEQUEO
						salida << respuestaServ << "\n";
					}
					else
					{	
						/*this->mostrarMensaje(
							"SE PRODUJO UN ERROR AL REALIZAR EL ENVIO DE DATOS AL SERVIDOR, INTENTELO MAS TARDE O PRUEBE VOLVER A CONECTARSE.", false);*/
						huboErrores = true;
					}

					delete (domTree);
					domTree = parser->getSiguiente();
				}

			} catch (PokerException& e){

				GeneradorRespuesta* generador = new GeneradorRespuesta();
				generador->agregarRespuesta(&e.getError());
				salida << generador->obtenerRespuesta() << endl;
				delete (generador);
			}

			salida.close();
			
			if (huboErrores) {
				this->mostrarMensaje("OCURRIERON ERRORES EN LA COMUNICACION CON EL SERVIDOR, INTENTE VOLVER A CONECTARSE.", false);
			} else {
				this->mostrarMensaje("SE HA PROCESADO CORRECTAMENTE EL ARCHIVO XML.", false);
			}
			hacerUnaPausa();
		}

		delete(parser);
	}
}

void UICliente::procesarEntradaOperandos()
{
	bool enviar = false;
	bool salir = false;

	switch (this->opcionMenu)
	{
		case 1:	this->tipoOperacion = SUMA;
				break;

		case 2: this->tipoOperacion = RESTA;
				break;

		case 3: this->tipoOperacion = MULTIPLICACION;
				break;

		case 4: this->tipoOperacion = DIVISION;
				break;
	}
	
	if (this->tipoOperacion != DIVISION)
	{
		this->mostrarMensaje("INGRESE LOS OPERANDOS DE LA OPERACION (PARA FINALIZAR PRESIONE 'x'):", false);
		this->entrada = "";

		while (!salir)
		{
			this->leerEntrada();
			
			salir = (this->entrada.compare("x")==0 || this->entrada.compare("X") ==0);

			if (!salir)
			{
				// Se valida que lo ingresado sea un numero real
				if (UtilTiposDatos::esDouble(this->entrada)) {
					if (!MensajesUtil::esVacio(this->entrada)){
						agregarOperando();
					}
				} else {
					mostrarMensaje("OPERANDO INGRESADO INCORRECTO!!!", false);
				}
			}
		}

		// Se valida que por lo menos se hayan ingresado dos operandos
		if (this->lstOperandos.size() > 1) {
			enviar = true;
		} else {
			mostrarMensaje("\nNO SE PROCESA LA OPERACION PORQUE NO HAY SUFICIENTES OPERANDOS.\n");
			hacerUnaPausa();
		}
	}
	else
	{
		mostrarMensaje("INGRESE EL DIVIDENDO: ");
		
		while (!salir)
		{
			leerEntrada();

			// Se valida que el dividendo sea un numero entero
			if(UtilTiposDatos::esEntero(this->entrada))
			{
				agregarOperando();

				mostrarMensaje("INGRESE EL DIVISOR: ");
				
				while (!salir)
				{
					leerEntrada();

					// Se valida que el divisor sea un numero entero
					if(UtilTiposDatos::esEntero(this->entrada))
					{
						if (UtilTiposDatos::stringADouble(this->entrada)!=0)
						{
							agregarOperando();
							enviar = true;
							salir = true;
						}
						else
						{
							mostrarMensaje("DIVISOR INGRESADO INCORRECTO!!!. DEBE SER UN VALOR DISTINTO DE CERO.", false);
							mostrarMensaje("VUELVA A INGRESAR EL DIVISOR: ");
						}
					}
					else
					{
						mostrarMensaje("DIVISOR INGRESADO INCORRECTO!!!. DEBE SER UN VALOR ENTERO.", false);
						mostrarMensaje("VUELVA A INGRESAR EL DIVISOR: ");
					}
				}
			}
			else
			{
				mostrarMensaje("DIVIDENDO INGRESADO INCORRECTO!!!. DEBE SER UN VALOR ENTERO.", false);
				mostrarMensaje("VUELVA A INGRESAR EL DIVIDENDO: ");
			}
		}
	}

	// Si no se produjo errores al ingresar los datos --> se los envia
	if (enviar)
		enviarOperacion();

	limpiarListaOperandos();
}

void UICliente::enviarOperacion()
{
	// Se pasa al parserTeclado el tipo de operacion y la lista de operandos
	// se devuelve un string
	string codigoOperacion;
	
	switch (this->tipoOperacion)
	{
		case 1:	codigoOperacion = "S";
				break;
		case 2: codigoOperacion = "R";
				break;
		case 3:	codigoOperacion = "M";
				break;
		case 4: codigoOperacion = "D";
				break;
	}

	ParserEntradaTeclado parserTeclado(codigoOperacion, &this->lstOperandos);
	string mensaje = parserTeclado.generarMensaje();
	
	if(cliente->enviarMsj(mensaje))
	{
		//string respuestaServ = cliente->recibirMsj(respuestaServ);
		string respuestaServ;
		if (cliente->recibirMsj(respuestaServ))
		{
			this->mostrarEncabezado("Resultado ejecucion");
			string respuesta = parserTeclado.obtenerRespuesta(respuestaServ);
			this->mostrarMensaje(respuesta,false);
			hacerUnaPausa();
		}
		else 
		{
			this->mostrarMensaje("SE PRODUJO UN ERROR AL RECIBIR EL RESULTADO DESDE EL SERVIDOR, INTENTELO MAS TARDE O PRUEBE VOLVER A CONECTARSE.", false);
			hacerUnaPausa();
		}
		
	}
	else
	{
		this->mostrarMensaje("SE PRODUJO UN ERROR AL REALIZAR EL ENVIO DE DATOS AL SERVIDOR, INTENTELO MAS TARDE O PRUEBE VOLVER A CONECTARSE.", false);
		hacerUnaPausa();
	}
}

void UICliente::mostrarEncabezado(string mensaje) {
	cout << "----------------------------------------------------" << endl;
	cout << mensaje << endl;
	cout << "----------------------------------------------------" << endl;
}

//void UICliente::mostrarResultado()
//{
//	string operacion;
//
//	switch (this->tipoOperacion)
//	{
//		case 1:	operacion = "SUMA";
//				break;
//
//		case 2: operacion = "RESTA";
//				break;
//
//		case 3: operacion = "MULTIPLICACION";
//				break;
//
//		case 4: operacion = "DIVISION";
//				break;
//	}
//
//	this->mostrarMensaje("EL RESULTADO DE LA " + operacion + " ES: " + this->resultado, false);
//}

void UICliente::reingresarOpcionMenu()
{
	this->mostrarMensaje("EL VALOR '" + this->entrada + "' NO ES UNA OPCION VALIDA !!!", false);
	this->mostrarMensaje("INGRESE NUEVAMENTE UNA OPCION DEL MENU: ");
	leerOpcionMenu();
}

void UICliente::mostrarMensaje(string msg, bool ingresaDatos)
{
	std::cout << msg;

	if (!ingresaDatos)
		std::cout << std::endl;
}
void UICliente::limpiarPantalla()
{
	system("CLS");
}

bool UICliente::validarOpcionMenu(eMenu opcion)
{
	bool resul = false;

	switch (opcion)
	{
		case MP:	if((this->opcionMenu >= 1)&&(this->opcionMenu <= 2))
						resul = true;
					break;

		case TO:	if((this->opcionMenu >= 1)&&(this->opcionMenu <= 3))
						resul = true;
					break;

		case OP:	if((this->opcionMenu >= 1)&&(this->opcionMenu <= 5))
						resul = true;
					break;

		case XML:	if((this->opcionMenu >= 1)&&(this->opcionMenu <= 2))
						resul = true;
					break;
	}

	return resul;
}

void UICliente::agregarOperando()
{
	this->lstOperandos.push_back(this->entrada);
}

void UICliente::limpiarListaOperandos()
{
	this->lstOperandos.clear();
}

void UICliente::hacerUnaPausa()
{
	string buffer;
	this->mostrarMensaje("\n\nPRESIONE INTRO PARA CONTINUAR...",false);
	getline(cin, buffer);
}
