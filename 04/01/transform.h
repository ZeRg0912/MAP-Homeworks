#pragma once
#include"shape.h"

class transform {
private:

public:
	Shape& shape;
	transform(Shape& _shape) : shape(_shape) {};
	Shape shift(int x, int y, int z);
	Shape scaleX(int x);
	Shape scaleY(int y);
	Shape scaleZ(int z);
	Shape scale(int scale);
};

