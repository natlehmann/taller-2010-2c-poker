#ifndef _OPUICLIENTE_SOLICITARESTADISTICA_H_
#define _OPUICLIENTE_SOLICITARESTADISTICA_H_

#include "OperacionUICliente.h"

using namespace std;

class OpUIClienteSolicitarEstadistica : public OperacionUICliente
{
private:
			string pathArchivo;
protected:
			virtual bool ejecutarAccion(Ventana* ventana);
public:
			OpUIClienteSolicitarEstadistica(vector<string> parametros);
			~OpUIClienteSolicitarEstadistica(void);
			string getPathArchivo();
			void setPathArchivo(string path);

};

#endif //_OPUICLIENTE_SOLICITARESTADISTICA_H_