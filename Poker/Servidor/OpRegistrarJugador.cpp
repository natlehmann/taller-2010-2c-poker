#include "OpRegistrarJugador.h"
#include "AccesoDatos.h"
#include "GeneradorRespuesta.h"
#include "Respuesta.h"

OpRegistrarJugador::OpRegistrarJugador(int idCliente, vector<string> parametros): Operacion(idCliente)
{
	this->parametros = parametros;
}

OpRegistrarJugador::~OpRegistrarJugador(void)
{
}

bool OpRegistrarJugador::ejecutarAccion(Socket* socket)
{
	bool error = false;
	bool ok = true;
	string respuesta = "";
	
	string usuario = this->parametros.at(0);
	string password = this->parametros.at(1);
	string nombre = this->parametros.at(2);
	string apellido = this->parametros.at(3);
	
	AccesoDatos ad;
	JugadorModelo* jugador = ad.obtenerJugador(usuario);

	if (!jugador)
	{
		// El jugador ingresado no existe en la BD --> Se graba
		if (ad.grabarNuevoJugador(usuario, password, nombre, apellido))
		{
			// OK	--> Se da respuesta OK al cliente
			respuesta = "OK";
		}
		else
		{
			respuesta = "Se ha producido un error al intentar registrar el jugador: " + ad.getMensajeError();
			ok = false;
		}
	}
	else
	{
		// El jugador existe en la BD.
		respuesta = "El usuario ingresado ya existe";
	}

	/******************************************************************/
	string msjRetorno = "";
	GeneradorRespuesta generador = GeneradorRespuesta();

	if (ok)
	{
		Resultado* resultado = new Resultado("", respuesta, "OpRegistrarJugador");
		generador.agregarRespuesta(resultado);
	}
	else
	{
		Error* error1 = new Error("", respuesta, "OpRegistrarJugador");
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



