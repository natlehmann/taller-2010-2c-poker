#ifndef _BOTE_MODELO_H_
#define _BOTE_MODELO_H_

#include <string>


using namespace std;

class BoteModelo
{
public:
	BoteModelo(void);
	virtual ~BoteModelo(void);

	int getId();
	int getCantidad();
};

#endif //_BOTE_MODELO_H_
