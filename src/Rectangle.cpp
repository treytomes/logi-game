#include "Rectangle.h"

Rectangle::Rectangle(int _x, int _y, int width, int height) {
	x = _x;
	y = _y;
	w = width;
	h = height;
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

void Rectangle::moveTo(int x, int y) {
	setX(x);
	setY(y);
}

void Rectangle::moveBy(int x, int y) {
	setX(getX() + x);
	setY(getY() + y);
}
