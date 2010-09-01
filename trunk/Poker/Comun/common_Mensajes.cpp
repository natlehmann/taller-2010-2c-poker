#include "common_Mensajes.h"

Mensajes::Mensajes()
{
}

Mensajes::~Mensajes()
{
}

int Mensajes::identificarCliente(string& msjCli)
{
	int idCli = -1;
	string cmd = "";
	
	if(msjCli.length() <= MAX_LONG_MSJ)
	{
		parsearMsj(msjCli, cmd, idCli);
		
		if ((cmd.compare(SOY) != 0) || (idCli < 0) || (idCli > CANTCLIENTES-1))
			idCli = -1;
	}

	return idCli;
}

string Mensajes::responderMsjClie(string &msjCli, string &cmd, int &idPersona)
{
	string respuesta = ERRORS;
	
	if(msjCli.length() <= (MAX_LONG_MSJ + 1))
	{
		parsearMsj(msjCli, cmd, idPersona);
	
		if (cmd.compare(ENTRA) == 0)
  		{
 			if ((idPersona >= 0) && (idPersona <= CANTPERSONAS-1)) 
				respuesta = SI;
 		}
 		else if (cmd.compare(SALE) == 0)
 		{
 			if ((idPersona >= 0) && (idPersona <= CANTPERSONAS-1)) 
				respuesta = SI;
 		}
 		else if (cmd.compare(FIN) == 0)
 		{
 			if (idPersona == -1) 
				respuesta = FIN;
 		}
	}
	
	return respuesta;
}

bool Mensajes::validarBienvenida(const string& msjSrv)
{
	if (msjSrv.compare(msjBienvenida()) == 0)
		return true;
	else
		return false;
}

string Mensajes::msjSOY(const int idCliente)
{
	stringstream streamOut;
	streamOut << SOY << " " << idCliente << '\n';
	return streamOut.str();
}

bool Mensajes::validarMsjServ(const string& msjSrv)
{
	bool respuesta = false;
	
	if(msjSrv.length() <= (MAX_LONG_MSJ + 1))
	{
		if (msjSrv.compare(msjERROR())==0||msjSrv.compare(msjSI()) == 0||msjSrv.compare(msjNO())== 0||msjSrv.compare(msjFIN())==0)
  			respuesta = true;
	}
	
	return respuesta;
}

void Mensajes::parsearMsj(string &msj, string &cmd, int &id)
{
	istringstream iss(msj, istringstream::out);
 	iss >> cmd >> id;
}
