#ifndef _OPUICLIENTE_LOGIN_H_
#define _OPUICLIENTE_LOGIN_H_

#include "OperacionUICliente.h"

using namespace std;

class OpUIClienteLogin : public OperacionUICliente
{
	private:
		int sesionId;
		int cantFichas;
		string error;

	protected:
		virtual bool ejecutarAccion(Ventana* ventana);

	public:
		OpUIClienteLogin(vector<string> parametros);
		virtual ~OpUIClienteLogin(void);

		virtual string getError();
		int getSesionId();
		int getCantFichas();
};

#endif //_OPUICLIENTE_LOGIN_H_
