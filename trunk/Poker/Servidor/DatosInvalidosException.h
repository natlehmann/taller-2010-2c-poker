#ifndef DATOSINVALIDOSEXCEPTION_H_
#define DATOSINVALIDOSEXCEPTION_H_

#include "PokerException.h"
#include "Resultado.h"

class DatosInvalidosException: public PokerException {
private:
	Resultado resultado;
public:
	DatosInvalidosException(string mensaje);
	DatosInvalidosException(Resultado& resultado);
	virtual ~DatosInvalidosException() throw();

    Resultado getResultado() const
    {
        return resultado;
    }
};

#endif /* DATOSINVALIDOSEXCEPTION_H_ */
