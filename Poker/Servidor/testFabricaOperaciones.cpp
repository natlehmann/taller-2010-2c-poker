#include "FabricaOperaciones.h"
#include <iostream>
using namespace std;

//int main() {
//	FabricaOperaciones fabrica;
//	vector<double> parametros;
//
//	parametros.push_back(29);
//	parametros.push_back(2);
//
//	DomTree* domTree = new DomTree();
//	Elemento* elementoPedido = domTree->agregarElemento("pedido");
//	Elemento* elementoOperacion = elementoPedido->agregarHijo("operacion");
//	elementoOperacion->agregarAtributo("id","D");
//	Elemento* elementoParametros = elementoPedido->agregarHijo("parametros");
//	Elemento* elementoParametro1 = elementoParametros->agregarHijo("parametro");
//	elementoParametro1->agregarAtributo("nombre","dividendo");
//	elementoParametro1->setTexto("29");
//	Elemento* elementoParametro2 = elementoParametros->agregarHijo("parametro");
//	elementoParametro2->agregarAtributo("nombre","divisor");
//	elementoParametro2->setTexto("2");
//
//	Operacion* operacion = fabrica.newOperacion(domTree);
//	vector<Resultado> resultados = operacion->ejecutar();
//
//	vector<Resultado>::iterator it = resultados.begin();
//	while (it != resultados.end()) {
//		Resultado resultado = *it;
//		cout << resultado.getId() << endl;
//		cout << resultado.getValor() << endl;
//		it++;
//	}
//
//	delete domTree;
//
//	return 0;
//}
