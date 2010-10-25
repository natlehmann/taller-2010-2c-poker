#ifndef _MENSAJE_MODELO_H_
#define _MENSAJE_MODELO_H_

#include <string>


using namespace std;

class MensajeModelo
{
private:
	int id;
	string texto;

public:
	MensajeModelo(int id, string texto = "");
	virtual ~MensajeModelo(void);

	int getId();

	string getTexto();
	void setTexto(string texto);
};

#endif //_MENSAJE_MODELO_H_
