#include "OpUIClienteSolicitarArchivo.h"
#include "DomTree.h"
#include "DomTreeFactory.h"
#include "Elemento.h"
#include "UICliente.h"
#include "Cliente.h"
#include "XmlParser.h"
#include "PokerException.h"
#include "RecursosAplicacion.h"
#include "Respuesta.h"
#include "Mesa.h"
#include "Jugador.h"
#include "Imagen.h"
#include "FabricaDeElementosGraficos.h"

OpUIClienteSolicitarArchivo::OpUIClienteSolicitarArchivo(vector<string> parametros) : OperacionUICliente(){
	this->parametros = parametros;
}

OpUIClienteSolicitarArchivo::~OpUIClienteSolicitarArchivo(void){
}

void OpUIClienteSolicitarArchivo::ejecutar(Ventana* ventana){

	string nombreArchivo = parametros.at(0);
	string pathDestino = RecursosAplicacion::getClienteConfigProperties()->get("cliente.configuracion.imagenes.path");

	//arma el xml de solicitud de archivo
	DomTree* tree = new DomTree("operaciones");
	Elemento* pedido = tree->agregarElemento("pedido");
	Elemento* operacion = pedido->agregarHijo("operacion");
	operacion->agregarAtributo("id", "OpEnviarArchivo");
	Elemento* parametros = operacion->agregarHijo("parametros");
	Elemento* parametro = parametros->agregarHijo("parametro");
	parametro->agregarAtributo("nombre", "nombreArchivo");
	parametro->setTexto(nombreArchivo);

	XmlParser* parser = new XmlParser();
	string mensaje = parser->toString(tree);

	delete(tree);
	delete(parser);

	//envia el pedido al servidor
	Cliente* cliente = UICliente::getCliente();
	cliente->enviarMsj(mensaje);
	
	//recibe la longitud del archivo solicitado
	if (cliente->recibirMsj(mensaje))
	{
		//valida y convierte el string con en tamanio del archivo a un entero
		int size = UtilTiposDatos::stringAEntero(mensaje);
		if (size != -1)
		{
			//envia el mensaje de recibido ok
			cliente->enviarMsj("OK");

			//recibe el archivo solicitado
			if (cliente->recibirMsj(mensaje, size))
			{
				//arma el path de destino
				string pathCompleto = pathDestino;
				pathCompleto.append(nombreArchivo);
				ofstream newfile(pathCompleto.c_str(), ios::out | ios::binary); 
			
				if(newfile.is_open()) 
				{ 
					//graba el archivo en el disco
					newfile.write(mensaje.data(), size); 
					newfile.close();

					//return true;
				}
				else
				{
					RecursosAplicacion::getLogErroresCliente()->escribir("Error al escribir el archivo " + pathCompleto);
					//return false;
				}
			}
		}
		else
			RecursosAplicacion::getLogErroresCliente()->escribir("Error al recibir el archivo " + nombreArchivo);
	}
}