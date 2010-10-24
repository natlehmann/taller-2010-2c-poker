#ifndef _MENSAJE_MODELO_H_
#define _MENSAJE_MODELO_H_

#include <string>


using namespace std;

class MensajeModelo
{
public:
	MensajeModelo(void);
	virtual ~MensajeModelo(void);

	int getId();

	string getTexto();
	void setTexto(string mensaje);
};

#endif //_MENSAJE_MODELO_H_
