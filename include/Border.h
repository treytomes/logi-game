#ifndef __BORDER_H__
#define __BORDER_H__

#include "Color.h"
#include "Rectangle.h"
#include <SDL2/SDL.h>

class Border {
	private:
		Color _borderColor;
		Color _backgroundColor;
		Rectangle* _rect;

	public:
		Border(Rectangle rect);
		Border(int x, int y, int width, int height);
		~Border();
		void render(SDL_Renderer* renderer);

		inline Rectangle* getRect() { return _rect; }
		inline Color getBorderColor() { return _borderColor; }
		inline void setBorderColor(Color c) { _borderColor = c; }
		void setBorderColor(int r, int g, int b, int a = 255);
		inline Color getBackgroundColor() { return _backgroundColor; }
		inline void setBackgroundColor(Color c) { _backgroundColor = c; }
		void setBackgroundColor(int r, int g, int b, int a = 255);
};

#endif
