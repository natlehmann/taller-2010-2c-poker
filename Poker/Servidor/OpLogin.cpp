#include "OpLogin.h"
#include "Resultado.h"
#include "FabricaOperacionesServidor.h"
#include "MensajesUtil.h"
#include "AccesoDatos.h"

OpLogin::OpLogin(int idCliente, vector<string> parametros): Operacion(idCliente)
{
	this->parametros = parametros;
}

OpLogin::~OpLogin(void)
{
}

bool OpLogin::ejecutarAccion(Socket* socket)
{
	Resultado* resultado = new Resultado();
	string contenido = "";
	string respuesta = "";
	bool error = false;

	AccesoDatos ac;

	string usuario = this->parametros.at(0);
	string password = this->parametros.at(1);
	string esVirtual = this->parametros.at(2);
	string esObservador = this->parametros.at(3);
		
	JugadorModelo* jugador = ac.obtenerJugador(usuario);

	if (jugador)
	{
		// El jugador ingresado existe en la BD --> Se valida password
		if (MensajesUtil::sonIguales(jugador->getPassword(),password))
		{
			// --> Se debe validar que el usuario no se encuentre jugando actualmente
			// OK	--> Se debe agregar el jugador al contexto del juego
			//		--> Se da respuesta OK al cliente
		}
		else
		{
			// Error al ingresar el password
			//respuesta = "Password incorrecto!!!.";
		}
	}
	else
	{
		// El jugador no existe en la BD.
	}

	//resultado->setValor(contenido);
	//resultado->setIdOperacion("");

	if (socket != NULL && resultado!= NULL)
	{
		respuesta = resultado->getValor();

		if(!socket->enviar(respuesta))
			error = true;
	}
	else
		error = true;

	return error;	
}
