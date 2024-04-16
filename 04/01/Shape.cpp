#define _USE_MATH_DEFINES
#include "shape.h"

double Line::calcSquare(coordinates& coord) { return 0; };
double Line::calcVolume(coordinates& coord) { return 0; };


double Square::calcSquare(coordinates& coord) { 
	int a = abs(coord.find("x")->second[0] - coord.find("x")->second[1]);
	int b = abs(coord.find("y")->second[0] - coord.find("y")->second[1]);
	return a * b; 
};
double Square::calcVolume(coordinates& coord) { return 0; };


double Cube::calcSquare(coordinates& coord) {
	int a = abs(coord.find("x")->second[0] - coord.find("x")->second[1]);
	int b = abs(coord.find("y")->second[0] - coord.find("y")->second[1]);
	int c = abs(coord.find("x")->second[0] - coord.find("x")->second[1]);
	return 2 * ((a * b) + (a * c) + (b * c)); 
};
double Cube::calcVolume(coordinates& coord) { 
	int a = abs(coord.find("x")->second[0] - coord.find("x")->second[1]);
	int b = abs(coord.find("y")->second[0] - coord.find("y")->second[1]);
	int c = abs(coord.find("x")->second[0] - coord.find("x")->second[1]);
	return a * b * c; 
};


double Circle::calcSquare(coordinates& coord) { return M_PI * (pow(radius, 2)); };
double Circle::calcVolume(coordinates& coord) { return 0; };


double Cylinder::calcSquare(coordinates& coord) { return M_PI * (pow(radius, 2)) + (2 * radius * height); };
double Cylinder::calcVolume(coordinates& coord) { return M_PI * (pow(radius, 2)) * height; };


Shape::Shape(const int& _type, const coordinates& _coord) {
	coord = _coord;
	type = static_cast<Types>(_type);
	calcData();
}

Shape::Shape(const int& _type, const coordinates& _coord, const double& _radius, const double& _height) {
	coord = _coord;
	type = static_cast<Types>(_type);
	calcData(_radius, _height);
}

void Shape::calcData(const double _radius, const double _height) {
	switch (getType()) {
	case Types::line:
		data = std::make_shared<Line>();
		break;
	case Types::Square:
		data = std::make_shared<Square>();
		break;
	case Types::cube:
		data = std::make_shared<Cube>();
		break;
	case Types::circle:
		data = std::make_shared<Circle>(_radius, _height);
		break;
	case Types::cylinder:
		data = std::make_shared<Cylinder>(_radius, _height);
		break;
	default:
		break;
	}
}

void Shape::printCoord() {
	std::cout << "Print coordinates of shape:\n";
	std::cout << "X: ";
	for (auto& x : getCoord().find("x")->second) {
		std::cout << x << " ";
	}
	std::cout << std::endl;
	std::cout << "Y: ";
	for (auto& y : getCoord().find("y")->second) {
		std::cout << y << " ";
	}
	std::cout << std::endl;
	if (getCoord().count("z")) {
		std::cout << "Z: ";
		for (auto& z : getCoord().find("z")->second) {
			std::cout << z << " ";
		}
	}
	std::cout << std::endl;
}