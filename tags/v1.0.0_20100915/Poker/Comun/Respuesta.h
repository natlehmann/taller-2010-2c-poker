#ifndef _RESPUESTA_H_
#define _RESPUESTA_H_

#include <string>

using namespace std;


class Respuesta {

private:
	string id;
	string valor;
	string idOperacion;

public:
	Respuesta();
	Respuesta(string id, string valor, string idOperacion);
	virtual ~Respuesta();

    virtual bool isError();

    string getId() const
    {
        return id;
    }

    string getValor() const
    {
        return valor;
    }

    void setId(string id)
    {
        this->id = id;
    }

    void setValor(string valor)
    {
        this->valor = valor;
    }

    string getIdOperacion() const
    {
        return idOperacion;
    }

    void setIdOperacion(string idOperacion)
    {
        this->idOperacion = idOperacion;
    }

};

#endif /* _RESPUESTA_H_ */
