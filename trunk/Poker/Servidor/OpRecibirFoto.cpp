#include "OpRecibirFoto.h"
#include "AccesoDatos.h"
#include "GeneradorRespuesta.h"
#include "Respuesta.h"
#include "UtilTiposDatos.h"
#include "RecursosServidor.h"

OpRecibirFoto::OpRecibirFoto(int idCliente, vector<string> parametros): Operacion(idCliente)
{
	this->parametros = parametros;
}

OpRecibirFoto::~OpRecibirFoto(void)
{
}

bool OpRecibirFoto::ejecutarAccion(Socket* socket)
{
	bool error = false;
	bool ok = true;
	string respuesta = "";
	string mensajeRecibido = "";
	
	string usuario = this->parametros.at(0);
	string nombreFoto = this->parametros.at(1);
	
	AccesoDatos ad;
	
	if (ad.actualizarNombreImagen(usuario, nombreFoto))
	{
		// OK	--> Se da respuesta OK al cliente
		respuesta = "OK";
	}
	else
	{
		respuesta = "Se produjo un error al grabar el nombre de la foto:" + ad.getMensajeError();
		ok = false;
	}

	/**************************************************************************************/
	string msjRetorno = "";
	GeneradorRespuesta generador = GeneradorRespuesta();

	if (ok)
	{
		Resultado* resultado = new Resultado("", respuesta, "OpRecibirFoto");
		generador.agregarRespuesta(resultado);
	}
	else
	{
		Error* error1 = new Error("", respuesta, "OpRecibirFoto");
		generador.agregarRespuesta(error1);
	}
	
	string resul = generador.obtenerRespuesta();
	/**************************************************************************************/

	error = true;

	if (socket != NULL && !MensajesUtil::esVacio(resul))
	{
		if(socket->enviar(resul))
		{
			// Se espera recibir la longitud de la foto
			if(socket->recibir(mensajeRecibido))
			{
				// Valida y convierte el string con el tamanio del archivo a un entero
				int size = UtilTiposDatos::stringAEntero(mensajeRecibido);
				if (size != -1)
				{
					// Envia el mensaje de recibido ok 
					if(socket->enviar("OK"))
					{
						// Recibe el archivo solicitado
						if(socket->recibir(mensajeRecibido, size))
						{
							// Arma el path de destino
							string pathCompleto = RecursosServidor::getConfig()->get("servidor.pathImagenes");
							// El path completo es la concatenacion del usuario + el nombre de la foto
							pathCompleto.append(usuario + "_" + nombreFoto);
							ofstream newfile(pathCompleto.c_str(), ios::out | ios::binary); 
													
							if(newfile.is_open()) 
							{ 
								//Graba el archivo en el disco
								newfile.write(mensajeRecibido.data(), size); 
								newfile.close();
								
								// Se envia el ultimo mensaje al cliente indicando el envio del archivo se completo correctamente
								socket->enviar("OK");

								error = false;
							}		
						}
					}
		
				}
			}
		}
	}
	
	return error;	
}


