#ifndef GENERADORRESPUESTA_H_
#define GENERADORRESPUESTA_H_
#include <list>
#include "Resultado.h"
#include "XMLParser.h"

using namespace std;

class GeneradorRespuesta
{
	private:
		list<Resultado*> listaResultados;

	public:
		GeneradorRespuesta();
		void agregarResultado(Resultado* resultado);
		string obtenerRespuesta();
};


#endif /*GENERADORRESPUESTA_H_*/