#ifndef RESULTADO_H_
#define RESULTADO_H_

#include <string>

using namespace std;


class Resultado {

private:
	string id;
	string valor;
	bool error;
	string idOperacion;

public:
	Resultado();
	Resultado(string id, string valor, bool error, string idOperacion);
	virtual ~Resultado();

    bool isError() const
    {
        return error;
    }

    string getId() const
    {
        return id;
    }

    string getValor() const
    {
        return valor;
    }

    void setError(bool error)
    {
        this->error = error;
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

#endif /* RESULTADO_H_ */
