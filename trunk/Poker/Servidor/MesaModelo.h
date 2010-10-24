#ifndef _MESA_MODELO_H_
#define _MESA_MODELO_H_

#include <string>


using namespace std;

class MesaModelo
{
public:
	MesaModelo(void);
	virtual ~MesaModelo(void);

	int getId();
	string getFondo();
};

#endif //_MESA_MODELO_H_
