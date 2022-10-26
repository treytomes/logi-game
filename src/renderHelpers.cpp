#include "renderHelpers.h"

void renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, Color color) {
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, color);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

	Rectangle textRect(x, y, textSurface->w, textSurface->h);
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

	SDL_DestroyTexture(textTexture);
	SDL_FreeSurface(textSurface);
}
