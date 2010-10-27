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

	virtual bool ejecutarAccion(Socket* socket) = 0;


public:
	Operacion(int idCliente);
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

    virtual bool ejecutar(Socket* socket);

};

#endif /* OPERACION_H_ */
