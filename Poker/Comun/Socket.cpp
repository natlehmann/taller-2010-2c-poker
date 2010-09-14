#include "Socket.h"
#include "MensajesUtil.h"
 
Socket::Socket()
{
}

Socket::Socket(const int sockfd)
{	
	this->valido = true;
	this->sockfd = sockfd;
	this->cantConexiones = 0;
	this->msgError = "";
}

Socket::Socket(const int cantConexiones, const int puerto)
{
	this->valido = false;
	this->sockfd = -1;
	this->cantConexiones = cantConexiones;
	this->puerto = puerto;
	this->msgError = "";
}

Socket::~Socket()
{
}

bool Socket::inicializarConexiones()
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 0), &wsaData) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Socket::abrir()
{
	int fd = -1;
	bool resul = true;
	//WSADATA wsaData;

	//if (WSAStartup(MAKEWORD(2, 0), &wsaData) == 0)
	//{
	if (!esValido())
	{
		fd = ::socket(AF_INET, SOCK_STREAM, 0);
	
		if (fd != -1)
		{
			this->sockfd = fd;
			this->valido = true;
		}	
		else
			resul = false;
	}
	//}
	return resul;
}

bool Socket::bindear()
{
	struct sockaddr_in direccion;

	direccion.sin_family = AF_INET;
	direccion.sin_port = htons(this->puerto);
	direccion.sin_addr.s_addr = INADDR_ANY;
	
	if(::bind(this->sockfd, (struct sockaddr*)&direccion, sizeof(direccion))!=-1)
		return true;
	else
		return false;
}

bool Socket::cvtLPW2stdstring(string& s, const LPWSTR pw, UINT codepage)
{    
	bool res = false;    
	char* p = 0;    
	int bsz;     
	bsz = WideCharToMultiByte(codepage,0,pw,-1,0,0,0,0);    
	
	if (bsz > 0) 
	{        
		p = new char[bsz];        
		int rc = WideCharToMultiByte(codepage,0,pw,-1,p,bsz,0,0);       
		if (rc != 0) 
		{            
			p[bsz-1] = 0;
			s = p;
			res = true;        
		}    
	}    
	
	delete [] p;    
	return res;
}

string Socket::generarMensajeError()
{
    string mensaje;
	int errCode = WSAGetLastError();
    LPWSTR errString = NULL;

    FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER |
                 FORMAT_MESSAGE_FROM_SYSTEM, // use windows internal message table
                 0,       // 0 since source is internal message table
                 errCode, // this is the error code returned by WSAGetLastError()
                          // Could just as well have been an error code from generic
                          // Windows errors from GetLastError()
                 0,       // auto-determine language to use
                 (LPWSTR)&errString, // this is WHERE we want FormatMessage
                                    // to plunk the error string.  Note the
                                    // peculiar pass format:  Even though
                                    // errString is already a pointer, we
                                    // pass &errString (which is really type LPSTR* now)
                                    // and then CAST IT to (LPSTR).  This is a really weird
                                    // trip up.. but its how they do it on msdn:
                                    // http://msdn.microsoft.com/en-us/library/ms679351(VS.85).aspx
                 0,                 // min size for buffer
                 0 );               // 0, since getting message from system tables
	
	if (!this->cvtLPW2stdstring(mensaje, errString, CP_ACP))
		mensaje = "mensaje de socket desconocido";

    LocalFree( errString ) ;
	
	return mensaje;
}

bool Socket::escuchar()
{	
	bool resul = false;
	
	if (abrir())
	{
		if (bindear())
		{
			if(::listen(this->sockfd, this->cantConexiones)!=-1)
				resul = true;
			else
				this->msgError = "Se produjo un error al intentar escuchar el socket";
		}
		else
			this->msgError = "Se produjo un error al intentar bindear el socket";
	}
	else
		this->msgError = "Se produjo un error al intentar abrir el socket";
		
	return resul;
}

Socket* Socket::aceptar()
{	
	int clientefd;
	int longCliente;
	struct sockaddr_in dirCliente;
	Socket* sockCliente = NULL;
	
	longCliente = sizeof(dirCliente);
	
	clientefd = ::accept(this->sockfd, (struct sockaddr*)&dirCliente, &longCliente);
	
	if (clientefd != -1)
	{
		this->valido = true;
		sockCliente = new Socket(clientefd); 
	}

	return sockCliente;
}

bool Socket::conectar(const string& host)
{
	struct hostent* he;
	struct sockaddr_in direccion;
	bool resul = false;
	WSADATA wsaData;
	//int error = 0;

	if (WSAStartup(MAKEWORD(2, 0), &wsaData) == 0)
	{
		if ((he=gethostbyname(host.c_str()))!=NULL)
		{
			if (abrir())
			{
				direccion.sin_family = AF_INET;
				direccion.sin_port = htons(this->puerto);
				direccion.sin_addr.s_addr = ((struct in_addr*)(he->h_addr))->s_addr; 
				
				if(::connect(this->sockfd,(struct sockaddr *)&direccion, sizeof (direccion))!=-1)
					resul = true;
				else
					this->msgError = this->generarMensajeError();
			}
			else
				this->msgError = "Se produjo un error al intentar abrir el socket";
		}
		else
			this->msgError = "Se produjo un error al intentar obtener el nombre del host";
	}
	else
		this->msgError = "Se produjo un error: WSAStartup() failed";

	return resul;
}


bool Socket::enviar(const string msg, const int longMsg)
{
	int cantEnviado = 0;
	int Aux = 0;
	bool sigue = true;
	bool error = false;
	
	while ((sigue)&&(cantEnviado < longMsg))
	{
		Aux = ::send(this->sockfd, msg.c_str(), longMsg, 0);
	
		if (Aux < 0)
		{
			error = true;
			sigue = false;
			this->msgError = "Se produjo una interrupcion en el envio de los datos";
		}
		else
			cantEnviado += Aux; 
	}
	
	return !error;
}
 
bool Socket::recibir(string& msg)
{
	msg = "";
	char buf[MAXRECV+1];
	int cantRecibido = 0;
	int Aux = 0;
	bool sigue = true;
	bool error = false;
	 
	while ((sigue)&&(msg.find('\0') == string::npos))
	{
		Aux = ::recv(this->sockfd, buf, MAXRECV, 0);
		
		if (Aux < 0)
		{
			error = true;
			sigue = false;
			this->msgError = "Se produjo una interrupcion en la recepcion de los datos";
		}
		else if (Aux >= 0)
		{
			cantRecibido += Aux;
			msg.append(buf, Aux);
		
			if (Aux < MAXRECV) {
				sigue = false;	
			}
		}

	}
	
	return !error;
}

bool Socket::cerrar()
{
	if(::closesocket(this->sockfd)!= -1)
		return true;
	else
		return false;
}

bool Socket::shutdown()
{
	if(::shutdown(this->sockfd, 2)!=-1)
		return true;
	else
		return false;
}
 
bool Socket::esValido()
{
	return this->valido;
}

bool Socket::limpiarConexiones()
{
	int resul = 0;

	resul = WSACleanup();

	if (resul==0)
		return true;
	else
		return false;
}

string Socket::getError()
{
	return this->msgError;
}
