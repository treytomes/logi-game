#ifndef __COLOR_H__
#define __COLOR_H__

#include <SDL2/SDL.h>

class Color: public SDL_Color {
	public:
		Color(int _r = 255, int _g = 255, int _b = 255, int _a = 255);
};

#endif
