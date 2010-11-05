#include "OpUIClienteSubirApuesta.h"
#include "ElementoGrafico.h"
#include "MensajesUtil.h"
#include "TextBox.h"
#include "UtilTiposDatos.h"
#include "PokerException.h"
#include "DomTree.h"
#include "Elemento.h"
#include <typeinfo.h>

OpUIClienteSubirApuesta::OpUIClienteSubirApuesta(vector<string> parametros) : OperacionUICliente(){
	this->parametros = parametros;
}

OpUIClienteSubirApuesta::~OpUIClienteSubirApuesta(void)
{
}

bool OpUIClienteSubirApuesta::ejecutarAccion(Ventana* ventana) {

	string idTextBox = this->parametros.at(0);
	ElementoGrafico* elem = ventana->getPanelComando()->getElementoPorId(idTextBox);

	if (elem != NULL && MensajesUtil::sonIguales(typeid(*elem).name(), "class TextBox")){

		TextBox* textBox = (TextBox*)elem;
		string contenido = textBox->getTexto();
		int numero = UtilTiposDatos::getEntero(contenido);

		if (numero <= 0) {
			ventana->mostrarMensaje("Debe ingresar un numero entero mayor a 0.");

		} else {

			DomTree* tree = new DomTree("operaciones");
			Elemento* operacion = this->agregarOperacion(tree, "OpSubirApuesta");

			Elemento* parametros = operacion->agregarHijo("parametros");
			Elemento* parametro1 = parametros->agregarHijo("parametro");
			parametro1->agregarAtributo("nombre", "fichas");
			parametro1->setTexto(contenido);

			bool resultado = this->enviarMensaje(tree, ventana);

			delete(tree);

			return resultado;
		}

	} else {
		throw PokerException("No se pudo obtener el elemento TextBox para operar en Subir Apuesta.");
	}

	return false;
}
