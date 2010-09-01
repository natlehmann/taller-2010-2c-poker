#include <stdlib.h>
#include "common_Parametros.h" 
#include "common_Socket.h"
#include "server_Servidor.h"

int main (int argc, char** argv)
{
	int resul = 0;
	int puerto = 0;
	
	if (Parametros::validarParametrosEntradaServidor(argc, argv, puerto))
	{
		Servidor servidor(puerto);
 			
 		// Se inicia la escucha de los clientes a traves de otro hilo
 		servidor.iniciarConexion();
 			
 		// Se comienza a detectar el ingreso de la "x" de finalizacion
 		servidor.escucharEntradaStandard();
 			 			 
 		// Se cierra todos los hilos
 		servidor.finalizarConexion();
 			 			
	}
	else
 		resul = 1;
 		
 	
 	return resul;
}
