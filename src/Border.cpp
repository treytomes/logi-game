#include "Border.h"
#include "renderHelpers.h"

Border::Border(Rectangle rect)
	: _borderColor(255, 255, 255), _backgroundColor(255, 255, 255), _rect(new Rectangle(rect)) {
}

Border::Border(int x, int y, int width, int height)
	: Border(Rectangle(x, y, width, height)) {
}

Border::~Border() {
	if (_rect != nullptr) {
		delete _rect;
		_rect = nullptr;
	}
}

void Border::render(SDL_Renderer* renderer) {
	setRenderColor(renderer, _backgroundColor);
	SDL_RenderFillRect(renderer, _rect);

	setRenderColor(renderer, _borderColor);
	SDL_RenderDrawLine(renderer, _rect->getLeft(), _rect->getTop(), _rect->getLeft(), _rect->getBottom());
	SDL_RenderDrawLine(renderer, _rect->getRight(), _rect->getTop(), _rect->getRight(), _rect->getBottom());
	SDL_RenderDrawLine(renderer, _rect->getLeft(), _rect->getTop(), _rect->getRight(), _rect->getTop());
	SDL_RenderDrawLine(renderer, _rect->getLeft(), _rect->getBottom(), _rect->getRight(), _rect->getBottom());
}

void Border::setBorderColor(int r, int g, int b, int a) {
	_borderColor.r = r;
	_borderColor.g = g;
	_borderColor.b = b;
	_borderColor.a = a;
}

void Border::setBackgroundColor(int r, int g, int b, int a) {
	_backgroundColor.r = r;
	_backgroundColor.g = g;
	_backgroundColor.b = b;
	_backgroundColor.a = a;
}
