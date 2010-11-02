#ifndef _OPERACION_UI_CLIENTE_H_
#define _OPERACION_UI_CLIENTE_H_

#include <string>
#include <vector>
#include "Ventana.h"
#include "DomTree.h"
#include "Elemento.h"

using namespace std;

class OperacionUICliente
{
protected:
	vector<string> parametros;

	bool enviarPedido(string nombreOperacion, Ventana* ventana);
	Elemento* agregarOperacion(DomTree* arbol, string nombreOperacion);
	virtual bool enviarMensaje(DomTree* tree, Ventana* ventana);


public:
	OperacionUICliente(void);
	virtual ~OperacionUICliente(void);

	/* Metodo sincronizado */
	virtual bool ejecutar(Ventana* ventana);

	/* Metodo no sincronizado */
	virtual bool ejecutarAccion(Ventana* ventana) = 0;
};

#endif
