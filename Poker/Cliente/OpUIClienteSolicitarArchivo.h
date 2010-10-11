#ifndef _OPUICLIENTE_SOLICITARARCHIVO_H_
#define _OPUICLIENTE_SOLICITARARCHIVO_H_

#include "OperacionUICliente.h"
#include <string>
#include <vector>

using namespace std;

class OpUIClienteSolicitarArchivo : public OperacionUICliente
{
	protected:
		vector<string> parametros;
	public:
		OpUIClienteSolicitarArchivo(vector<string> parametros);
		virtual ~OpUIClienteSolicitarArchivo(void);

	virtual bool ejecutar(Ventana* ventana);
};

#endif
