#pragma once

class OpJugadorVirtual
{
private:
	int idCliente;
public:
	OpJugadorVirtual(int idCliente);
	~OpJugadorVirtual();
	int getIdCliente();
	void setIdCliente(int idCliente);
	virtual void ejecutarAccion() = 0;
};
