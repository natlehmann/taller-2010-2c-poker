#include "OpUIClienteDejarMesa.h"
#include "DomTree.h"
#include "UICliente.h"
#include "Cliente.h"
#include "XmlParser.h"
#include "RecursosCliente.h"
#include "FabricaOperacionesCliente.h"
#include "MensajesUtil.h"


OpUIClienteDejarMesa::OpUIClienteDejarMesa(void)
{
}

OpUIClienteDejarMesa::~OpUIClienteDejarMesa(void)
{
}

bool OpUIClienteDejarMesa::ejecutarAccion(Ventana* ventana) {

	return this->enviarPedido("OpDejarMesa");

	//bool ok = false;

	//DomTree* tree = new DomTree("operaciones");
	//Elemento* pedido = tree->agregarElemento("pedido");

	//Elemento* operacion = pedido->agregarHijo("operacion");
	//operacion->agregarAtributo("id", "OpDejarMesa");
	//Elemento* params = operacion->agregarHijo("parametros");
	//Elemento* param1 = params->agregarHijo("parametro");
	//
	//param1->agregarAtributo("nombre", "Mensaje");
	//param1->setTexto("DejarMesa");
	//
	//XmlParser* parser = new XmlParser();

	//// Se envia el pedido al servidor
	//Cliente* cliente = UICliente::getCliente();
	//string msjRecibido;

	//if (cliente->enviarRecibir(parser->toString(tree), msjRecibido)) 
	//{
	//	try 
	//	{
	//		if (this->cargarRespuestaServidor(msjRecibido))
	//		{
	//			if (MensajesUtil::sonIguales(this->parametrosRecibidos.at(0), "OK"))
	//			{
	//				ok = true;		
	//			}
	//			else
	//			{
	//				if (parametrosRecibidos.size() > 0)
	//					this->error = parametrosRecibidos.at(0);
	//			}
	//		}
	//	} 
	//	catch (PokerException& e) 
	//	{
	//		RecursosCliente::getLog()->escribir(&(Respuesta)e.getError());
	//	}
	//}
	//else
	//{
	//	RecursosCliente::getLog()->escribir(
	//		"El servidor no devolvio respuesta al intentar dejar la mesa.");
	//}

	//delete(parser);
	//delete(tree);

	//return ok;
}


string OpUIClienteDejarMesa::getError()
{
	return this->error;
}
