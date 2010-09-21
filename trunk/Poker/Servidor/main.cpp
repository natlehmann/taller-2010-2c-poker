#include "SDL.h" 
#include <vld.h>
#include "UIServidor.h"


int main (int argc, char** argv)
{
	UIServidor ui;

	ui.iniciarAplicacion();

	return 0;

	//SDL_Surface *image, *screen;
	//SDL_Rect dest, source;
	//SDL_Event event;
	//int done = 0;
	//atexit(SDL_Quit);
	//
	//// Iniciar SDL
	//if (SDL_Init(SDL_INIT_VIDEO) < 0) 
	//{
	//	printf("No se pudo iniciar SDL: %s\n",SDL_GetError());
	//	exit(1);
	//}
	//
	//// Activamos modo de video
	////screen = SDL_SetVideoMode(640,480,24,SDL_HWSURFACE);
	////screen = SDL_SetVideoMode(800,600,24,SDL_HWSURFACE);
	////screen = SDL_SetVideoMode(1024,768,24,SDL_HWSURFACE);
	//screen = SDL_SetVideoMode(1280,768,24,SDL_HWSURFACE);

	//if (screen == NULL) 
	//{
	//	printf("No se puede inicializar el modo gráfico: \n",SDL_GetError());
	//	exit(1);
	//}
	//
	//// Cargamos gráfico
	//image = SDL_LoadBMP("C:\\nave.bmp");
	//
	//if ( image == NULL ) 
	//{
	//	string  err = SDL_GetError();
	//	printf("No pude cargar gráfico: %s\n", SDL_GetError());
	//	exit(1);
	//}

	//// Definimos donde dibujaremos el gráfico y lo copiamos a la pantalla.
	//dest.x = 50;
	//dest.y = 50;
	//dest.w = image->w;
	//dest.h = image->h;
	////dest.w = 100;
	////dest.h = 100;
	////source.x = 100;
	////source.y = 100;
	////source.w = 100;
	////source.h = 100;

	//SDL_BlitSurface(image, NULL, screen, &dest);
	////SDL_BlitSurface(image, &source, screen, &dest);

	//// Mostramos la pantalla
	//SDL_Flip(screen);

	//// liberar superficie
	//SDL_FreeSurface(image);
	//
	//// Esperamos la pulsación de una tecla para salir
	//while(done == 0) 
	//{
	//	while ( SDL_PollEvent(&event) ) 
	//	{
	//		if ( event.type == SDL_KEYDOWN )
	//		done = 1;
	//	}
	//}
	//
	//return 0;
}
