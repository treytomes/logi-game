#include "Rectangle.h"

Rectangle::Rectangle(int x, int y, int width, int height)
	: _x(x), _y(y), _width(width), _height(height) {
}

int Rectangle::getX() {
	return _x;
}

void Rectangle::setX(int x) {
	_x = x;
}

int Rectangle::getY() {
	return _y;
}

void Rectangle::setY(int y) {
	_y = y;
}

int Rectangle::getWidth() {
	return _width;
}

void Rectangle::setWidth(int width) {
	_width = width;
}

int Rectangle::getHeight() {
	return _height;
}

void Rectangle::setHeight(int height) {
	_height = height;
}

int Rectangle::getTop() {
	return getY();
}

int Rectangle::getBottom() {
	return getY() + getHeight() - 1;
}

int Rectangle::getLeft() {
	return getX();
}

int Rectangle::getRight() {
	return getX() + getWidth() - 1;
}

bool Rectangle::contains(int x, int y) {
	return (getLeft() <= x) && (x <= getRight()) && (getTop() <= y) && (y <= getBottom());
}
