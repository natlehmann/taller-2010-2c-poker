#include "Imagen.h"
#include "UIException.h"
#include "RecursosAplicacion.h"
#include "ServiciosGraficos.h"
#include "OperacionUICliente.h"
#include "FabricaOperacionesCliente.h"
#include <fstream>

#define BYTES_POR_PIXEL 3

Imagen::Imagen(string nombre) {

	this->nombre = RecursosAplicacion::getClienteConfigProperties()->get(
		"cliente.configuracion.imagenes.path") + nombre;

	ifstream archivoExiste(this->nombre.c_str());
	if (!archivoExiste.good()){

		FabricaOperacionesCliente fab;
		OperacionUICliente* operacion = fab.newOperacion("OpUIClienteSolicitarArchivo", nombre);
		operacion->ejecutar(NULL);
		delete(operacion);
	}

}

Imagen::~Imagen(void)
{
}

void Imagen::dibujarSobreSup(SDL_Surface* superficie, SDL_Rect* posicionEnSup){

	if (this->superficie == NULL) {

		SDL_Surface* imagenInicial = cargarBMP(); 

		this->superficie = imagenInicial;

		if(imagenInicial != NULL) {

			// solo hacer resize si es necesario
			if (imagenInicial->clip_rect.w != this->getAncho() 
				|| imagenInicial->clip_rect.h != this->getAlto()) {
			
					this->superficie = ServiciosGraficos::resizeSuperficie(
						imagenInicial, this->getAncho(), this->getAlto());

					SDL_FreeSurface(imagenInicial);
			}
		}
	}

	//si algo salio mal
	if (this->superficie == NULL) {
		throw UIException("No se pudo cargar la imagen " + this->nombre, "E");
	}

	SDL_BlitSurface(this->superficie, this->getContornoRect(), 
					superficie, posicionEnSup); 

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
	SDL_Surface* superficie = NULL;
	Uint32 rmask = 0x00ff0000;
	Uint32 gmask = 0x0000ff00;
	Uint32 bmask = 0x000000ff;
	Uint32 amask = 0x00000000;

	FILE *archivo = NULL;
	BITMAPFILEHEADER encabezadoArchivo;
	BITMAPINFOHEADER encabezadoMapaDeBits;
	char *imagenStream = NULL;
	
	archivo = fopen(this->nombre.c_str(),"rb"); // "rb" solo lectura, en binario
	if (archivo == NULL)
		return NULL;

	//leo el encabezado del archivo bmp
	fread(&encabezadoArchivo, sizeof(BITMAPFILEHEADER),1,archivo);
	if (ferror(archivo)) {
		fclose(archivo);
		return NULL;
	}

	//si es un bmp entonces el bfType tiene que ser 0x4D42
	if (encabezadoArchivo.bfType != 0x4D42) {
		fclose(archivo);
		return NULL;
	}
	
	//leo la info del encabezado
	fread(&encabezadoMapaDeBits, sizeof(BITMAPINFOHEADER),1,archivo);
	if (ferror(archivo)) {
		fclose(archivo);
		return NULL;
	}

	//tamanio de la imagen sin metadata
	int tamanioEnBytes = encabezadoMapaDeBits.biSizeImage;
	if (tamanioEnBytes < 1)
		return NULL;

	imagenStream = new char[tamanioEnBytes];
	if (!imagenStream) {
		fclose(archivo);
		return NULL;
	}

	//leo los datos de la imagen
	fread(imagenStream,tamanioEnBytes,1,archivo);
	if (ferror(archivo)) {
		delete[] imagenStream;
		fclose(archivo);
		return NULL;
	}
	
	//se invierte verticalmente la imagen
	char *imagenStreamInvertida = invertirBMP(imagenStream, encabezadoMapaDeBits);

	// pitch debe ser multiplo de 4
	int pitch = 3*encabezadoMapaDeBits.biWidth;
	if (pitch % 4 != 0) {
		pitch += 4 - (pitch % 4);
	}
	superficie = SDL_CreateRGBSurfaceFrom(imagenStreamInvertida,encabezadoMapaDeBits.biWidth,
		encabezadoMapaDeBits.biHeight,24,pitch,rmask,gmask,bmask,amask);

	delete[] imagenStream;
	fclose(archivo);
	return superficie;
}


char* Imagen::invertirBMP(char *imagenStream, BITMAPINFOHEADER encabezadoMapaDeBits)
{
	int cantidadFila = encabezadoMapaDeBits.biHeight;

	// el ancho no puede medirse asi porque esto no considera el padding por fila
	//int cantidadXColum = encabezadoMapaDeBits.biWidth * BYTES_POR_PIXEL;
	int cantidadXColum = encabezadoMapaDeBits.biSizeImage/encabezadoMapaDeBits.biHeight;
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
