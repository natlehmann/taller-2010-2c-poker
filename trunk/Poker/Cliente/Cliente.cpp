#include "Cliente.h"
#include "UtilTiposDatos.h"
#include "DomTree.h"
#include "XmlParser.h"
#include <fstream>

bool Cliente::conectado = false;
string Cliente::ipServidor = "";
Socket* Cliente::sock = NULL;

Cliente::Cliente()
{
}

Cliente::~Cliente()
{

}

bool Cliente::iniciarConexion(const int puerto, const string& ipServidor)
{
	Cliente::conectado = false;
	Cliente::ipServidor = ipServidor;
	Cliente::sock = new Socket(1,puerto);

	if (Cliente::sock->conectar(ipServidor))
		Cliente::conectado = true;
	return Cliente::conectado;
}

bool Cliente::finalizarConexion()
{
	if (Cliente::sock->cerrar())
	{
		delete(Cliente::sock);
		Cliente::conectado = false;
	}
	return Cliente::conectado;
}

bool Cliente::estaConectado()
{
	return Cliente::conectado;
}

bool Cliente::recibirMsj(string& msjRecibido)
{
	return Cliente::sock->recibir(msjRecibido);
}

bool Cliente::enviarMsj(const string msj)
{
	return Cliente::sock->enviar(msj, msj.length());
}

bool Cliente::solicitarArchivo(string& nombreArchivo, string& pathDestino)
{
	//arma el xml de solicitud de archivo
	DomTree* tree = new DomTree("operaciones");
	Elemento* pedido = tree->agregarElemento("pedido");

	Elemento* operacion = pedido->agregarHijo("operacion");
	operacion->agregarAtributo("id", "OpEnviarImagen");
	Elemento* nombre = operacion->agregarHijo("nombre");
	nombre->setTexto(nombreArchivo);

	XmlParser* parser = new XmlParser();
	string mensaje = parser->toString(tree);

	delete(tree);
	delete(parser);

	//envia al servidor la peticion
	Cliente::enviarMsj(mensaje);
	
	//recibe la longitud del archivo solicitado
	if (Cliente::recibirMsj(mensaje))
	{
		//valida y convierte el string con en tamanio del archivo a un entero
		int size = UtilTiposDatos::stringAEntero(mensaje);
		if (size != -1)
		{
			//envia el mensaje de recibido ok
			Cliente::enviarMsj("OK");

			//recibe el archivo solicitado
			if (Cliente::sock->recibir(mensaje, size))
			{
				//arma el path de destino
				string destino = pathDestino;
				destino.append(nombreArchivo);
				ofstream newfile(destino.c_str(), ios::out | ios::binary); 
			
				if(newfile.is_open()) 
				{ 
					//graba el archivo en el disco
					newfile.write(mensaje.data(), size); 
					newfile.close();

					return true;
				}
			}
		}
	}

	return false;
}

string Cliente::getSocketError()
{
	return Cliente::sock->getError();
}
