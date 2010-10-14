#ifndef OPERACION_H_
#define OPERACION_H_

#include "Socket.h"
#include "Respuesta.h"
#include "Resultado.h"
#include "Error.h"
#include <string>

using namespace std;


class Operacion {

protected:
	string id;

public:
	Operacion();
	virtual ~Operacion();

    string getId() const
    {
        return id;
    }

    void setId(string id)
    {
        this->id = id;
    }

    virtual bool ejecutar(Socket* socket) = 0;

};

#endif /* OPERACION_H_ */
