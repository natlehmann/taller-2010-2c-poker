#ifndef PARAMETROS_H_
#define PARAMETROS_H_

#define CANT_ARG_CLIENTE  3
#define CANT_ARG_SERVIDOR 1
#include <string>

class Parametros
{
	public:
	
		static bool validarParametrosEntradaServidor(int argc, char** argv, int& puerto)
		{
			bool resul = false;
			
			if (argc == (CANT_ARG_SERVIDOR + 1))
			{
				try
				{
					puerto =  atoi(argv[1]);
					
					resul = true;
				}
				catch (...)
				{
				}
			}
				
			return resul;
		};
		
		static bool validarParametrosEntradaCliente(int argc, char** argv, std::string& ipServidor, int& puerto, int& idCliente)
		{
			bool resul = false;
	
			try
			{
				if (argc == (CANT_ARG_CLIENTE + 1))
				{
					ipServidor = argv[1];
					puerto =  atoi(argv[2]);
					idCliente = atoi(argv[3]);
			
					resul = true;
				}
			}
			catch (...)
			{
			}
	
			return resul;
		};
};

#endif /*PARAMETROS_H_*/
