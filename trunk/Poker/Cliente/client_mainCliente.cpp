#include <stdlib.h>
#include <string>
#include "common_Socket.h"
#include "common_Mensajes.h"
#include "common_Cliente.h"
#include "common_Parametros.h"

using namespace std;

int main (int argc, char** argv)
{
	string ipServidor;
	int idCliente = -1;
	int puerto = 0;
	int resul = 0;
	string msjRecibido;
	string cmd;
	bool error = true;
	bool fin = false;
	
	if (Parametros::validarParametrosEntradaCliente(argc, argv, ipServidor, puerto, idCliente))
	{
		Cliente cliente(idCliente, puerto, ipServidor);
		
		// Se intenta iniciar la conexion con el servidor
 		if (cliente.iniciarConexion())
 		{
 			// Se recibe la bienvenida del Servidor
			msjRecibido = cliente.recibirMsj(); 			
 			
 			if (Mensajes::validarBienvenida(msjRecibido))
 			{
 				// Se envia la identificacion del cliente
 				if (cliente.enviarMsj(Mensajes::msjSOY(idCliente)))
 				{
 					// Se recibe respuesta del Servidor
					msjRecibido = cliente.recibirMsj();
					
					if (Mensajes::validarMsjServ(msjRecibido))
					{
						error = false;
						while ((!error) && (!fin))
						{
							// Lectura de la entrada standard
							getline(cin,cmd);
							cmd += "\n";
							
							// Se envia el comando ingresado por el cliente						
							if (cliente.enviarMsj(cmd))
							{
								// Se recibe respuesta del Servidor
								msjRecibido = cliente.recibirMsj();
								
								if (Mensajes::validarMsjServ(msjRecibido))
								{	// Envio de la respuesta a la salida standard
									cout << msjRecibido;
									
									if (msjRecibido.compare(Mensajes::msjERROR())==0)
										error = true;
									else if (msjRecibido.compare(Mensajes::msjFIN())==0)
											fin = true;
								}
								else
									error = true;
							}
							else
								error = true;
						}
						
						if (error)
							cout << Mensajes::msjERROR();						
					}
				}			
 			}
 			
 			cliente.finalizarConexion();
  		}
	}

	if (error)
		resul = 1;
	
 	return resul;
}
