#include "OpUIClienteEnviarFoto.h"
#include "DomTree.h"
#include "UICliente.h"
#include "Cliente.h"
#include "XmlParser.h"
#include "RecursosCliente.h"
#include "FabricaOperacionesCliente.h"
#include "MensajesUtil.h"

OpUIClienteEnviarFoto::OpUIClienteEnviarFoto(vector<string> parametros): OperacionUICliente()
{
	this->parametros = parametros;
}

OpUIClienteEnviarFoto::~OpUIClienteEnviarFoto(void)
{
}

bool OpUIClienteEnviarFoto::ejecutarAccion(Ventana* ventana)
{
	bool ok = false;

	string usuario = this->parametros.at(0);
	string nombreFoto = this->parametros.at(1);
	string pathCompleto = this->parametros.at(2);
	
	DomTree* tree = new DomTree("operaciones");
	Elemento* pedido = tree->agregarElemento("pedido");

	Elemento* operacion = pedido->agregarHijo("operacion");
	operacion->agregarAtributo("id", "OpRecibirFoto");

	Elemento* params = operacion->agregarHijo("parametros");
	Elemento* param1 = params->agregarHijo("parametro");
	Elemento* param2 = params->agregarHijo("parametro");
	
	param1->agregarAtributo("nombre", "usuario");
	param1->setTexto(usuario);
	param2->agregarAtributo("nombre", "nombreFoto");
	param2->setTexto(nombreFoto);
	
	XmlParser* parser = new XmlParser();

	Cliente* cliente = UICliente::getCliente();
	string msjRecibido;

	/******************************************************************************/
	// Se envia el nombre de la foto al servidor para grabarla en la BD
	/******************************************************************************/
	if (cliente->enviarRecibir(parser->toString(tree), msjRecibido)) 
	{
		try 
		{
			if (this->cargarRespuestaServidor(msjRecibido))
			{
				if (MensajesUtil::sonIguales(this->parametrosRecibidos.at(0), "OK"))
				{
					/******************************************************************************/
					// Se envia el archivo con la foto
					/******************************************************************************/
					
					// Se abre el archivo de la imagen de la foto
					ifstream::pos_type size;
					ifstream file(pathCompleto.c_str(), ios::in | ios::binary | ios::ate);
					if (file.is_open())
					{
						// Se carga en memoria el archivo, y obtiene el tamanio
						size = file.tellg();
						char* memblock = new char [size];
						file.seekg (0, ios::beg);
						file.read (memblock, size);
						file.close();
												
						string sizeEntero = UtilTiposDatos::enteroAString(size);
						
						// Se envia el tamanio del archivo al servidor
						if(cliente->enviarRecibir(sizeEntero, msjRecibido))
						{
							if (MensajesUtil::sonIguales(msjRecibido.data(), "OK"))
							{
								//Se envia el archivo al servidor
								cliente->enviarRecibir(memblock, msjRecibido, size);

								// Se verifica la ultima respuesta del servidor
								if (MensajesUtil::sonIguales(msjRecibido.data(), "OK"))
								{
									ok = true;
								}
							}
							delete[] memblock;
						}
					}
					else 
					{
						RecursosCliente::getLog()->escribir("No se puede abrir el archivo " + nombreFoto + " para lectura.");
					}
				}
				else
				{
					// parametrosRecibidos.at(0) TIENE LA DESCRIPCION DEL ERROR INTENTAR GRABAR LA FOTO
				}
			}
		} 
		catch (PokerException& e) 
		{
			RecursosCliente::getLog()->escribir(&(Respuesta)e.getError());
		}
	}
	else
	{
		RecursosCliente::getLog()->escribir("El servidor no devolvio respuesta al intentar enviar el nombre de la foto.");
	}

	delete(parser);
	delete(tree);

	return ok;
}


