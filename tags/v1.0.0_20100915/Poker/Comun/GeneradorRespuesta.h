#ifndef GENERADORRESPUESTA_H_
#define GENERADORRESPUESTA_H_
#include <list>
#include <vector>
#include "Resultado.h"
#include "Error.h"
#include "Respuesta.h"
#include "XMLParser.h"

using namespace std;

class GeneradorRespuesta
{
	private:
		list<Respuesta*> listaResultados;
		list<Error*> listaErrores;

	public:
		GeneradorRespuesta();
		virtual ~GeneradorRespuesta();
		void agregarRespuesta(const Error* error);
		void agregarRespuesta(Respuesta* respuesta);
		void agregarRespuestas(vector<Respuesta*> respuestas);
		string obtenerRespuesta();
		void limpiar();
};


#endif /*GENERADORRESPUESTA_H_*/
