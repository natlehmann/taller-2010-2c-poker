#ifndef _ERROR_H__
#define _ERROR_H__

#include <string>
#include "Respuesta.h"

using namespace std;

class Error : public Respuesta
{
public:
	Error(void);
	Error(string id, string valor, string idOperacion);
	virtual ~Error(void);

	virtual bool isError();
};

#endif
