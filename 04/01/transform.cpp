#include "transform.h"

Shape transform::shift(int _x, int _y, int _z) {
	for (auto& x : shape.getCoord().find("x")->second) {
		x += _x;
	}

	for (auto& y : shape.getCoord().find("y")->second) {
		y += _y;
	}

	if (shape.getCoord().count("z")) {
		for (auto& z : shape.getCoord().find("z")->second) {
			z += _z;
		}
	}

	return shape;
}

Shape transform::scaleX(int _x) {
	for (auto& x : shape.getCoord().find("x")->second) {
		x *= _x;
	}

	return shape;
}

Shape transform::scaleY(int _y) {
	for (auto& y : shape.getCoord().find("y")->second) {
		y *= _y;
	}

	return shape;
}

Shape transform::scaleZ(int _z) {
	if (shape.getCoord().count("z")) {
		for (auto& z : shape.getCoord().find("z")->second) {
			z *= _z;
		}
	}

	return shape;
}

Shape transform::scale(int scale) {
	for (auto& x : shape.getCoord().find("x")->second) {
		x /= scale;
	}

	for (auto& y : shape.getCoord().find("y")->second) {
		y /= scale;
	}

	if (shape.getCoord().count("z")) {
		for (auto& z : shape.getCoord().find("z")->second) {
			z /= scale;
		}
	}

	return shape;
}
