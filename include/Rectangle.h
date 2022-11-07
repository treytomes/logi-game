#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__

#ifdef _WIN32
	#include <SDL.h>
#else
	#include <SDL2/SDL.h>
#endif

class Rectangle: public SDL_Rect {
	public:
		Rectangle(int x, int y, int width, int height);
		Rectangle(SDL_Rect rect) : Rectangle(rect.x, rect.y, rect.w, rect.h) {}

		inline int getX() { return x; }
		inline void setX(int _x) { x = _x; }

		inline int getY() { return y; }
		inline void setY(int _y) { y = _y; }

		inline int getWidth() { return w; }
		inline void setWidth(int width) { w = width; }

		inline int getHeight() { return h; }
		inline void setHeight(int height) { h = height; }

		int getTop();
		int getBottom();
		int getLeft();
		int getRight();

		bool contains(int x, int y);
		void moveTo(int x, int y);
		void moveBy(int x, int y);
};

#endif
