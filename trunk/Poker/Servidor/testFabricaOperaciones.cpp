#include "FabricaOperacionesServidor.h"
#include "DatosInvalidosException.h"
#include "ParserException.h"
#include <iostream>
using namespace std;

//int main() {
//	FabricaOperacionesServidor fabrica;
//	vector<double> parametros;
//
//	parametros.push_back(29);
//	parametros.push_back(2);
//
//	DomTree* domTree = new DomTree();
//	vector<Resultado> resultados;
//	try {
//		Elemento* elementoPedido = domTree->agregarElemento("pedido");
//		Elemento* elementoOperacion = elementoPedido->agregarHijo("operacion");
//		elementoOperacion->agregarAtributo("id","S");
//		Elemento* elementoParametros = elementoPedido->agregarHijo("parametros");
//		Elemento* elementoParametro1 = elementoParametros->agregarHijo("parametro");
//		elementoParametro1->agregarAtributo("nombre","sum");
//		elementoParametro1->setTexto("-29.00");
//		Elemento* elementoParametro2 = elementoParametros->agregarHijo("parametro");
//		elementoParametro2->agregarAtributo("nombre","sum");
//		elementoParametro2->setTexto("7");
//
//		Operacion* operacion = fabrica.newOperacion(domTree);
//		resultados = operacion->ejecutar();
//	}catch(ParserException& ex ) {
//		cout << ex.getMensaje() << endl;
//	}catch(DatosInvalidosException& ex ) {
//		Resultado res = ex.getResultado();
//		cout << res.getValor() + "  " + res.getIdOperacion() + "  " + res.getId() << endl;
//	}catch(PokerException& ex ) {
//		cout << ex.getMensaje() << endl;
//	}catch(exception& ex ) {
//		cout << ex.what() << endl;
//	}
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
