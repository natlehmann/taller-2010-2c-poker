#include "OpComprarFichas.h"
#include "AccesoDatos.h"
#include "GeneradorRespuesta.h"
#include "Respuesta.h"
#include "UtilTiposDatos.h"

OpComprarFichas::OpComprarFichas(int idCliente, vector<string> parametros): Operacion(idCliente)
{
	this->parametros = parametros;
}

OpComprarFichas::~OpComprarFichas(void)
{
}

bool OpComprarFichas::ejecutarAccion(Socket* socket)
{
	bool error = false;
	bool ok = true;
	string respuesta = "";
	
	string usuario = this->parametros.at(0);
	string cantFichas = this->parametros.at(1);
	
	AccesoDatos ad;
	
	if (ad.validarCantFichasJugador(usuario))
	{
		// El jugador ingresado tiene menos de 100 fichas 
		if (ad.validarCantFichasCompradasHoy(usuario, UtilTiposDatos::stringAEntero(cantFichas)))
		{
			// El jugador ingresado compro menos de 2000 fichas el dia de hoy
			if (ad.grabarCompraFichas(usuario, UtilTiposDatos::stringAEntero(cantFichas)))
			{
				// OK	--> Se da respuesta OK al cliente
				respuesta = "OK";
			}
			else
			{
				respuesta = "Se produjo un error al grabar la compra de fichas:" + ad.getMensajeError();
				ok = false;
			}
		}
		else
			respuesta = "No puede comprar fichas porque ya supero las 2000 fichas diarias";
	}
	else
	{
		// El jugador no puede comprar porque tiene mas de 100 fichas
		respuesta = "No puede comprar fichas porque no tiene menos de 100 fichas!!!";
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
	
	return error;	
}

