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
			sesion = ad.grabarInicioSesion(usuario, esObservador, esVirtual);
			
			if (sesion > 0)
			{	
				// OK	--> Se da respuesta OK al cliente
				respuesta = "OK";
			}
			else
			{
				respuesta = "Se ha producido un error al intentar iniciar sesion: " + ad.getMensajeError();
				ok = false;
			}
		}
		else
		{
			// Error al ingresar el password
			respuesta = "Password Incorrecto!!!";
		}
	}
	else
	{
		// El jugador no existe en la BD.
		respuesta = "El usuario ingresado no existe!!!";
	}

	/******************************************************************/
	string msjRetorno = "";
	GeneradorRespuesta generador = GeneradorRespuesta();

	if (ok)
	{
		Resultado* resultado = new Resultado("", respuesta, "OpLogin");
		generador.agregarRespuesta(resultado);
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
