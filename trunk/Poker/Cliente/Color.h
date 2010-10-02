#ifndef _COLOR_H__
#define _COLOR_H__

#include "SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

class Color {
private:
	Uint8 red;
	Uint8 green;
	Uint8 blue;

public:
	Color(Uint8 red, Uint8 green, Uint8 blue);
	virtual ~Color(void);

	void setRed(Uint8 red);
	void setGreen(Uint8 green);
	void setBlue(Uint8 blue);

	Uint8 getRed();
	Uint8 getGreen();
	Uint8 getBlue();

	Uint32 toUint32(SDL_Surface* superficie);
};

#endif //_COLOR_H__
