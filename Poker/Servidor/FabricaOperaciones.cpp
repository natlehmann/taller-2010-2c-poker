#include "FabricaOperaciones.h"
#include "Suma.h"
#include "Resta.h"
#include "Multiplicacion.h"
#include "Division.h"
#include "UtilTiposDatos.h"
#include <list>
using namespace std;

FabricaOperaciones::FabricaOperaciones() {}

FabricaOperaciones::~FabricaOperaciones() {}

Operacion* FabricaOperaciones::newOperacion(DomTree* domTree)
{
	string idOperacion;
	vector<double> parametros;

	Elemento* elementoRaiz = domTree->getRaiz();
	list<Elemento*>* hijosRaiz = elementoRaiz->getHijos();
	list<Elemento*>::iterator it = hijosRaiz->begin();
	Elemento* elementoPedido = *it;
	list<Elemento*>* hijosPedido = elementoPedido->getHijos();
	it = hijosPedido->begin();
	Elemento* elementoOperacion = *it;
	idOperacion = elementoOperacion->getAtributo("id");
	it++;
	Elemento* elementoParametros = *it;
	list<Elemento*>* hijosParametros = elementoParametros->getHijos();
	for (it = hijosParametros->begin(); it != hijosParametros->end(); it++) {
		Elemento* elementoParametro = *it;
		string valor = elementoParametro->getTexto();
		parametros.push_back(UtilTiposDatos::stringToDouble(valor));
	}
	
	switch (idOperacion.at(0))
	{
	case 'S':
		return new Suma("S",parametros);
		break;
	case 'R':
		return new Resta("R",parametros);
		break;
	case 'M':
		return new Multiplicacion("M",parametros);
		break;
	case 'D':
		return new Division("D",parametros);
		break;
	}
	return NULL;
}
