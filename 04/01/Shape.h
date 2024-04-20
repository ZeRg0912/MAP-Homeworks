#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <memory>
#include <cmath>

using coordinates = std::map<std::string, std::vector<int>>;

enum class Types { line = 1, Square, cube, circle, cylinder };

class Figure {
public:
	virtual double calcSquare(coordinates& coord) = 0;
	virtual double calcVolume(coordinates& coord) = 0;
	double height = 0;
	double radius = 0;
};

class Line : public Figure {
public:
	double calcSquare(coordinates& coord) override;
	double calcVolume(coordinates& coord) override;
};

class Square : public Figure {
public:
	double calcSquare(coordinates& coord) override;
	double calcVolume(coordinates& coord) override;
};

class Cube : public Figure {
public:
	double calcSquare(coordinates& coord) override;
	double calcVolume(coordinates& coord) override;
};

class Circle : public Figure {
public:
	Circle(const double& _radius, const double& _height) : radius(_radius), height(_height) {};
	double calcSquare(coordinates& coord) override;
	double calcVolume(coordinates& coord) override;
	double height = 0;
	double radius = 0;
};

class Cylinder : public Figure {
public:
	Cylinder(const double& _radius, const double& _height) : radius(_radius), height(_height) {};
	double calcSquare(coordinates& coord) override;
	double calcVolume(coordinates& coord) override;
	double height = 0;
	double radius = 0;
};

class Shape {
private:
	Types type;
	coordinates coord;
	std::shared_ptr<Figure> data;
	void calcData(const double radius = 0, const double height = 0);

public:
	Shape() = default;
	Shape(const int& _type, const coordinates& _coord);
	Shape(const int& _type, const coordinates& _coord, const double& radius, const double& height);

	Types& getType() { return type; }
	coordinates& getCoord() { return coord; };
	void printCoord();
	double getSquare() { return data->calcSquare(coord); }
	double getVolume() { return data->calcVolume(coord); }
	double getHeight() { return data->height; }
	double getRadius() { return data->radius; }
};