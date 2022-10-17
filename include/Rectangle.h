#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__

class Rectangle {
	private:
		int _x;
		int _y;
		int _width;
		int _height;

	public:
		Rectangle(int x, int y, int width, int height);

		int getX();
		void setX(int x);

		int getY();
		void setY(int y);

		int getWidth();
		void setWidth(int width);

		int getHeight();
		void setHeight(int height);

		int getTop();
		int getBottom();
		int getLeft();
		int getRight();

		bool contains(int x, int y);
};

#endif
