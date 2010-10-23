#ifndef OPERACION_H_
#define OPERACION_H_

#include "Socket.h"
#include "Respuesta.h"
#include "Resultado.h"
#include "Error.h"
#include <string>
#include <vector>

using namespace std;


class Operacion {

protected:
	string id;
	vector<string> parametros;
	int idCliente;

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

	int getIdCliente() const
    {
		return idCliente;
    }

    void setIdCliente(int idCliente)
    {
        this->idCliente = idCliente;
    }

    virtual bool ejecutar(Socket* socket) = 0;

};

#endif /* OPERACION_H_ */
