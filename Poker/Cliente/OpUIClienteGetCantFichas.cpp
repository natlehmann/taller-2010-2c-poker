#include "OpUIClienteGetCantFichas.h"
#include "XmlParser.h"
#include "Cliente.h"
#include "UICliente.h"
#include "UtilTiposDatos.h"
#include "RecursosCliente.h"

OpUIClienteGetCantFichas::OpUIClienteGetCantFichas(vector<string> parametros) : OperacionUICliente()
{
	this->parametros = parametros;
	this->cantidadFichas = 0;
}

OpUIClienteGetCantFichas::~OpUIClienteGetCantFichas(void)
{
}

bool OpUIClienteGetCantFichas::ejecutarAccion(Ventana* ventana)
{
	bool ok = false;

	string usuario = this->parametros.at(0);
	
	DomTree* tree = new DomTree("operaciones");
	Elemento* pedido = tree->agregarElemento("pedido");

	Elemento* operacion = pedido->agregarHijo("operacion");
	operacion->agregarAtributo("id", "OpGetCantidadFichas");

	Elemento* params = operacion->agregarHijo("parametros");
	Elemento* param1 = params->agregarHijo("parametro");
	
	param1->agregarAtributo("nombre", "usuario");
	param1->setTexto(usuario);
	
	XmlParser* parser = new XmlParser();

	// Se envia el pedido al servidor
	Cliente* cliente = UICliente::getCliente();
	string msjRecibido;

	if (cliente->enviarRecibir(parser->toString(tree), msjRecibido)) 
	{
		try 
		{
			if (this->cargarRespuestaServidor(msjRecibido))
			{
				this->cantidadFichas = UtilTiposDatos::getEntero(this->parametrosRecibidos.at(0));
			
			} else {
				this->cantidadFichas = -1;
			}
		} 
		catch (PokerException& e) 
		{
			RecursosCliente::getLog()->escribir(&(Respuesta)e.getError());
		}
	}
	else
	{
		RecursosCliente::getLog()->escribir(
			"El servidor no devolvio respuesta al intentar determinar la cantidad de fichas del jugador.");
	}

	delete(parser);
	delete(tree);

	return ok;

}

int OpUIClienteGetCantFichas::getCantidadFichas() {
	return this->cantidadFichas;
}
