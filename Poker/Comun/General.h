#define _SI_  "S"
#define _NO_ "N"
#define _si_  "s"
#define _no_ "n"
#define _ERROR_ -1
#define _PUNTO_ '.'
#define _MENOS_ '-'

#include <string>
#include <ctype.h>

class General
{
	public:
		static int getEntero(std::string valor)
		{
			int resul = -1;
			unsigned int digito = 0;
			unsigned int indice = 0;
			bool salir = false;
			
			if (strlen(valor.data()) > 0)
			{
				while((indice < strlen(valor.data())) && !(salir))
				{
					if (isdigit(valor[indice]))
						indice += 1;
					else
						salir = true;
				}
			}

			if (!salir)
				resul = atoi(valor.data());
			
			return resul;
		};

		static bool esDouble(std::string valor)
		{
			unsigned int digito = 0;
			unsigned int indice = 0;
			bool encontroPunto = false;
			bool negativo = false;
			bool salir = false;
			bool resul = false;
			
			if (strlen(valor.data()) > 0)
			{
				if (valor[indice] == _MENOS_)
				{
					if (strlen(valor.data()) != 1)
					{
						negativo = true;
						indice += 1;					
					}
					else
						salir = false;
				}

				while((indice < strlen(valor.data())) && !(salir))
				{
					if (isdigit(valor[indice]))
						indice += 1;
					else 
						if ((valor[indice]== _PUNTO_)&&(!encontroPunto))
						{						
							encontroPunto = true;
							indice += 1;
						}
						else
							salir = true;
				}
			}

			if (!salir)
				resul = true;
			
			return resul;
		};

		static bool validarSiNo(std::string valor)
		{
			bool resul = false;

			if ((valor == _SI_) || (valor == _NO_)||(valor == _si_) || (valor == _no_))
				resul = true;

			return resul;
		}
};
