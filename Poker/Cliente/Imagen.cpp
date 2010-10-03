#include "Imagen.h"
#include "UIException.h"
#include "RecursosAplicacion.h"

#define BYTES_POR_PIXEL 3

Imagen::Imagen(string nombre) {
	// TODO: VER SI ACA VERIFICAMOS QUE LA IMAGEN EXISTA O SE LA PEDIMOS AL SERVIDOR
	this->nombre = RecursosAplicacion::getClienteConfigProperties()->get(
		"cliente.configuracion.imagenes.path") + nombre;

}

Imagen::~Imagen(void)
{
}

void Imagen::dibujarSobreSup(SDL_Surface* superficie, SDL_Rect* posicionEnSup){

	SDL_Surface* imagenInicial = cargarBMP(); 

	// ESTO TAMBIEN SE VA !!!!
	if(imagenInicial != NULL) {
		this->superficie = SDL_DisplayFormat(imagenInicial);

		SDL_BlitSurface(this->getSuperficie(), this->getContornoRect(), 
				superficie, posicionEnSup); 
		//Free the old image 
		SDL_FreeSurface(imagenInicial); 
		SDL_FreeSurface(this->getSuperficie()); 
		this->superficie = NULL;
	
	} else {
		throw UIException("No se pudo cargar la imagen " + this->nombre, "E");
	}
}

void Imagen::dibujarSobreSup(SDL_Surface* superficie) {
	this->dibujarSobreSup(superficie, this->getOffsetRect());
}


string Imagen::getNombre(){
	return this->nombre;
}

void Imagen::setTamanio(long tamanio){
	this->tamanio = tamanio;
}

long Imagen::getTamanio() {
	return this->tamanio;
}

SDL_Surface* Imagen::cargarBMP() {
	SDL_Surface* superficie;
	Uint32 rmask = 0x00ff0000;
	Uint32 gmask = 0x0000ff00;
	Uint32 bmask = 0x000000ff;
	Uint32 amask = 0x00000000;

	FILE *archivo;
	BITMAPFILEHEADER encabezadoArchivo;
	BITMAPINFOHEADER encabezadoMapaDeBits;
	char *imagenStream;
	
	archivo = fopen(this->nombre.c_str(),"rb"); // "rb" solo lectura, en binario
	if (archivo == NULL)
		return NULL;

	//leo el encabezado del archivo bmp
	fread(&encabezadoArchivo, sizeof(BITMAPFILEHEADER),1,archivo);

	//si es un bmp entonces el bfType tiene que ser 0x4D42
	if (encabezadoArchivo.bfType !=0x4D42) {
		fclose(archivo);
		return NULL;
	}
	
	//leo la info del encabezado
	fread(&encabezadoMapaDeBits, sizeof(BITMAPINFOHEADER),1,archivo);

	//tamanio de la imagen sin metadata
	int tamanioEnBytes = encabezadoMapaDeBits.biSizeImage;

	//muevo el puntero a donde estan los datos de la imagen
	fseek(archivo, encabezadoArchivo.bfOffBits, SEEK_SET);

	imagenStream = new char[tamanioEnBytes];
	if (!imagenStream) {
		delete imagenStream;
		fclose(archivo);
		return NULL;
	}

	//leo los datos de la imagen
	fread(imagenStream,tamanioEnBytes,1,archivo);
	if (imagenStream == NULL) {
		fclose(archivo);
		return NULL;
	}
	
	//se invierte verticalmente la imagen
	char *imagenStreamInvetida = invertirBMP(imagenStream, encabezadoMapaDeBits);
	superficie = SDL_CreateRGBSurfaceFrom(imagenStreamInvetida,encabezadoMapaDeBits.biWidth,encabezadoMapaDeBits.biHeight,24,3*encabezadoMapaDeBits.biWidth,rmask,gmask,bmask,amask);

	delete imagenStream;
	fclose(archivo);
	return superficie;
}


char* Imagen::invertirBMP(char *imagenStream, BITMAPINFOHEADER encabezadoMapaDeBits)
{
	
	int cantidadFila = encabezadoMapaDeBits.biHeight;
	int cantidadXColum = encabezadoMapaDeBits.biWidth * BYTES_POR_PIXEL;
	int k = 0;
	int j = 0;
	char *imagenStreamCopia;
	int posicion = 0;
	imagenStreamCopia = new char[encabezadoMapaDeBits.biSizeImage];
	for (int i = 1 ; i <=cantidadFila;i++)
	{
		k = cantidadFila - (i-1);
		posicion = (i-1)*cantidadXColum;
		int w = (k-1)*cantidadXColum;
		for (j=0; j< cantidadXColum; j++)
		{
			imagenStreamCopia[j+posicion] = imagenStream[w];
			w++;
		}
	}
	return imagenStreamCopia;
}