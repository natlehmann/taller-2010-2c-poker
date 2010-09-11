
#include "GeneradorRespuesta.h"
#include "DomTree.h"
#include "DomTreeFactory.h"

using namespace std;

GeneradorRespuesta::GeneradorRespuesta(void)
{
}

void GeneradorRespuesta::agregarResultado(Resultado* resultado)
{
	listaResultados.push_back(resultado);
}

string GeneradorRespuesta::obtenerRespuesta()
{
	string respuesta;
	Parser* parser = new XmlParser();
		
	DomTree* tree = new DomTree();
			
	Elemento* e = tree->agregarElemento("respuesta");

	list<Resultado*>::iterator it = listaResultados.begin();
	//Le pregunto al primero si es error, si es un error lo son todos

	Resultado* resultado = *it;
	
	Elemento* e2 = NULL;

	if (resultado->isError())
		{
			if((resultado->getIdOperacion()).size()==0)
			{
				e2 = e->agregarHijo("operacion");
				e2->agregarAtributo("id","");
			}
			else
			{
				e2 = e->agregarHijo("operacion");
				e2->agregarAtributo("id",resultado->getIdOperacion());
			}
			e2 = e->agregarHijo("errores");	
		}
	else
		{
			//Si se cual operacion es la informo
			e2 = e->agregarHijo("resultados");
		}	

	for (it = listaResultados.begin(); it != listaResultados.end(); it++) 
	{
		resultado = *it;
		Elemento *e3 = NULL;
		if (resultado->isError())
		{
			e3 = e2->agregarHijo("error");
			e3->agregarAtributo("tipo",resultado->getId());
			e3->setTexto(resultado->getValor());
		}
		else
		{
			e3 = e2->agregarHijo("resultado");
			e3->agregarAtributo("nombre",resultado->getId());
			e3->setTexto(resultado->getValor());
		}	
	}
	respuesta = parser->toString(tree);
	return respuesta;
}