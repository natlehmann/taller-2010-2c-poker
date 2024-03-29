#include "OpLogin.h"
#include "Resultado.h"
#include "FabricaOperacionesServidor.h"
#include "MensajesUtil.h"
#include "AccesoDatos.h"
#include "GeneradorRespuesta.h"
#include "Respuesta.h"

OpLogin::OpLogin(int idCliente, vector<string> parametros): Operacion(idCliente)
{
	this->parametros = parametros;
}

OpLogin::~OpLogin(void)
{
}

bool OpLogin::ejecutarAccion(Socket* socket)
{
	bool error = false;
	bool ok = true;
	bool logueado = false;
	string respuesta = "";
	int sesion;

	string usuario = this->parametros.at(0);
	string password = this->parametros.at(1);
	string esVirtual = this->parametros.at(2);
	string esObservador = this->parametros.at(3);
	
	AccesoDatos ad;
	JugadorModelo* jugador = ad.obtenerJugador(usuario);

	if (jugador)
	{
		// El jugador ingresado existe en la BD --> Se valida password
		if (MensajesUtil::sonIguales(jugador->getPassword(), password))
		{
			//if (ad.validarUltimaSesionCerrada(usuario))
			//{
				sesion = ad.grabarInicioSesion(usuario, esObservador, esVirtual);
				
				if (sesion > 0)
				{	
					// OK	--> Se da respuesta OK al cliente
					respuesta = "OK";
					logueado = true;
				}
				else
				{
					respuesta = "Se ha producido un error al intentar iniciar sesion: " + ad.getMensajeError();
					ok = false;
				}

			//}
			//else
			//{
			//	respuesta = "El usuaro ya esta logueado.";
			//	ok = false;
			//}

		}
		else
		{
			// Error al ingresar el password
			respuesta = "Password Incorrecto!!!";
			ok = false;
		}
	}
	else
	{
		// El jugador no existe en la BD.
		respuesta = "El usuario ingresado no existe!!!";
		ok = false;
	}

	/******************************************************************/
	string msjRetorno = "";
	GeneradorRespuesta generador = GeneradorRespuesta();

	if (ok)
	{
		// Se envia el "OK"
		Resultado* resultado = new Resultado("", respuesta, "OpLogin");
		generador.agregarRespuesta(resultado);

		if (logueado) 
		{
			// Se envia el id de sesion
			resultado = new Resultado("", MensajesUtil::intToString(sesion), "OpLogin");
			generador.agregarRespuesta(resultado);

			// Se envia la cantidad de fichas
			resultado = new Resultado("", MensajesUtil::intToString(jugador->getFichas()), "OpLogin");
			generador.agregarRespuesta(resultado);
		}
	}
	else
	{
		Error* error1 = new Error("", respuesta, "OpLogin");
		generador.agregarRespuesta(error1);
	}
	
	string resul = generador.obtenerRespuesta();
	/******************************************************************/

	if (socket != NULL && !MensajesUtil::esVacio(resul))
	{
		if(!socket->enviar(resul)) 
			error = true;
	}
	else 
		error = true;

	delete(jugador);

	return error;	
}
