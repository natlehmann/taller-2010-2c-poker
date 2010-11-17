#include "Imagen.h"
#include "UIException.h"
#include "RecursosCliente.h"
#include "ServiciosGraficos.h"
#include "OperacionUICliente.h"
#include "FabricaOperacionesCliente.h"
#include "MensajesUtil.h"
#include <fstream>


Imagen::Imagen(string nombre) {

	this->nombre = RecursosCliente::getConfig()->get(
		"cliente.configuracion.imagenes.path") + nombre;

	this->nombreSinPath = nombre;

	ifstream archivoExiste(this->nombre.c_str());
	if (!archivoExiste.good()){

		FabricaOperacionesCliente fab;
		OperacionUICliente* operacion = fab.newOperacion("OpUIClienteSolicitarArchivo", nombre);
		operacion->ejecutarAccion(NULL);
		delete(operacion);
	}

}

Imagen::Imagen(string nombre, bool solicitarImagen) {

	this->nombre = RecursosCliente::getConfig()->get(
		"cliente.configuracion.imagenes.path") + nombre;

	this->nombreSinPath = nombre;

	string jugDefault = RecursosCliente::getConfig()->get("cliente.tema.default.jugador.imagen.default");
	string jugAusente = RecursosCliente::getConfig()->get("cliente.tema.default.jugador.ausente.imagen");

	if (!MensajesUtil::sonIguales(nombre, jugDefault) && !MensajesUtil::sonIguales(nombre, jugAusente)){

		ifstream archivoExiste(this->nombre.c_str());
		if (!archivoExiste.good() || solicitarImagen){

			FabricaOperacionesCliente fab;
			OperacionUICliente* operacion = fab.newOperacion("OpUIClienteSolicitarArchivo", nombre);
			operacion->ejecutarAccion(NULL);
			delete(operacion);
		}
	}

}

Imagen::~Imagen(void)
{
}

void Imagen::dibujarSobreSup(SDL_Surface* superficie, SDL_Rect* posicionEnSup){

	//genera la superficie
	this->generarSuperficie();

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

void Imagen::generarSuperficie() {
	if (this->superficie == NULL) 
	{
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
}



string Imagen::getNombre(){
	return this->nombre;
}


SDL_Surface* Imagen::cargarBMP() {

	BITMAPFILEHEADER encabezadoArchivo;
	BITMAPINFOHEADER encabezadoMapaDeBits;
	char *imagenStream = NULL;
	
	ifstream archivo(this->nombre.c_str(), ios::in | ios::binary);
	if (archivo.fail() || archivo.bad())
		return NULL;

	//leo el encabezado del archivo bmp
	archivo.read((char*)&encabezadoArchivo, sizeof(BITMAPFILEHEADER));
	if (archivo.fail() || archivo.bad()) {
		archivo.close();
		return NULL;
	}

	//si es un bmp entonces el bfType tiene que ser 0x4D42
	if (encabezadoArchivo.bfType != 0x4D42) {
		archivo.close();
		return NULL;
	}
	
	//leo la info del encabezado
	archivo.read((char*)&encabezadoMapaDeBits, sizeof(BITMAPINFOHEADER));
	if (archivo.fail() || archivo.bad()) {
		archivo.close();
		return NULL;
	}

	//tamanio de la imagen sin metadata
	int tamanioEnBytes = encabezadoMapaDeBits.biSizeImage;
	if (tamanioEnBytes < 1) {
		archivo.close();
		return NULL;
	}

	imagenStream = new char[tamanioEnBytes];
	if (!imagenStream) {
		archivo.close();
		return NULL;
	}

	//leo los datos de la imagen
	archivo.read(imagenStream,tamanioEnBytes);
	if (archivo.fail() || archivo.bad()) {
		delete[] imagenStream;
		archivo.close();
		return NULL;
	}
	
	//se invierte verticalmente la imagen
	char *imagenStreamInvertida = invertirBMP(imagenStream, encabezadoMapaDeBits);

	//el pitch debe ser multiplo de 4
	int pitch = encabezadoMapaDeBits.biWidth * ServiciosGraficos::getBytesPerPixel();
	if (pitch % 4 != 0) {
		pitch += 4 - (pitch % 4);
	}

	SDL_Surface* superficie = SDL_CreateRGBSurfaceFrom(
		imagenStreamInvertida,
		encabezadoMapaDeBits.biWidth,
		encabezadoMapaDeBits.biHeight,
		ServiciosGraficos::getBitsPerPixel(),
		pitch,
        ServiciosGraficos::getRmask(), 
		ServiciosGraficos::getGmask(),
        ServiciosGraficos::getBmask(), 
		ServiciosGraficos::getAmask());

	delete[] imagenStream;
	archivo.close();
	return superficie;
}


char* Imagen::invertirBMP(char *imagenStream, BITMAPINFOHEADER encabezadoMapaDeBits)
{
	int cantidadFilas = encabezadoMapaDeBits.biHeight;
	int bytesPorColumna = encabezadoMapaDeBits.biSizeImage/encabezadoMapaDeBits.biHeight;
	int offsetFila = 0;
	int offsetColumna = 0;
	char *imagenStreamCopia = new char[encabezadoMapaDeBits.biSizeImage];
	for (int i = 0 ; i < cantidadFilas ; i++) {
		offsetFila = i * bytesPorColumna;
		offsetColumna = (cantidadFilas - i - 1) * bytesPorColumna;
		for (int j = 0 ; j < bytesPorColumna ; j++) {
			imagenStreamCopia[j + offsetFila] = imagenStream[offsetColumna];
			offsetColumna++;
		}
	}
	return imagenStreamCopia;
}

string Imagen::getNombreSinPath(){
	return this->nombreSinPath;
}
