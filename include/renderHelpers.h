#ifndef __RENDERHELPERS_H__
#define __RENDERHELPERS_H__

#ifdef _WIN32
	#include <SDL.h>
	#include <SDL_ttf.h>
#else
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_ttf.h>
#endif

#include <iostream>
using namespace std;

#include "Color.h"
#include "i18n.h"
#include "Rectangle.h"

inline void setRenderColor(SDL_Renderer* renderer, Color color) {
	if (SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a) != 0) {
		cerr << _("Unable to set render color: ") << SDL_GetError() << endl;
	}
}

inline void setTextureColor(SDL_Texture* texture, Color color) {
	if (SDL_SetTextureColorMod(texture, color.r, color.g, color.b) != 0) {
		cerr << _("Unable to set texture color: ") << SDL_GetError() << endl;
	}
}

void renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, Color color = Color(255, 255, 255));

#endif
