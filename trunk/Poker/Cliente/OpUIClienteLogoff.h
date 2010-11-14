#ifndef _OPUICLIENTE_LOGOFF_H_
#define _OPUICLIENTE_LOGOFF_H_

#include "OperacionUICliente.h"

using namespace std;

class OpUIClienteLogoff : public OperacionUICliente
{
	private:
		//int sesionId;
		//int cantFichas;
		string error;

	protected:
		virtual bool ejecutarAccion(Ventana* ventana);

	public:
		OpUIClienteLogoff(vector<string> parametros);
		virtual ~OpUIClienteLogoff(void);

		virtual string getError();
		//int getSesionId();
		//int getCantFichas();
};

#endif //_OPUICLIENTE_LOGOFF_H_
