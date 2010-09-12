#ifndef DATOSINVALIDOSEXCEPTION_H_
#define DATOSINVALIDOSEXCEPTION_H_

#include "PokerException.h"
#include "Error.h"

class DatosInvalidosException: public PokerException {

public:
	DatosInvalidosException(string mensaje);
	DatosInvalidosException(Error& error);
	virtual ~DatosInvalidosException() throw();
	
};

#endif /* DATOSINVALIDOSEXCEPTION_H_ */
