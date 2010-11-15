#ifndef _OPUICLIENTE_SOLICITARESTADISTICA_H_
#define _OPUICLIENTE_SOLICITARESTADISTICA_H_

#include "OperacionUICliente.h"

using namespace std;

class OpUIClienteSolicitarEstadistica : public OperacionUICliente
{
	private:
		string archivo;
		string estadistica;
		string error;
	
	protected:
		virtual bool ejecutarAccion(Ventana* ventana);
	
	public:
		OpUIClienteSolicitarEstadistica(vector<string> parametros);
		~OpUIClienteSolicitarEstadistica(void);
		virtual string getError();

		string getArchivo();
		string getFechaActual();
		string getHoraActual();


};

#endif //_OPUICLIENTE_SOLICITARESTADISTICA_H_