#include <iostream>
#include <random>
#include "shape.h"
#include "transform.h"

int main() {
    std::map<std::string, std::vector<int>> coord;
    coord["x"] = std::vector<int> {2, 4, 6, 8, 10, 12, 14, 16};
    coord["y"] = std::vector<int> {3, 5, 7, 9, 11, 13, 15, 17};
    coord["z"] = std::vector<int> {18, 19, 20, 21, 22, 23, 24, 25};

    std::cout << "Cube:\n";
    Shape cube(3, coord);
    std::cout << "Square of the cube: " << cube.getSquare() << "\nVolume of the cube: " << cube.getVolume() << std::endl;

    std::cout << "\n\ncylinder:\n";
    Shape cylinder(5, coord, 30, 60);
    std::cout << "Square of the cylinder : " << cylinder.getSquare() << "\nVolume of the cylinder: " << cylinder.getVolume() << std::endl;

    transform cube_t(cube);
    cube_t.scale(4);
    std::cout << "\n\nCube ";
    std::cout << "after change:";
    std::cout << "\nSquare of the cube: " << cube.getSquare() << "\nVolume of the cube: " << cube.getVolume() << std::endl;

    transform cylinder_t(cylinder);
    std::cout << "\n\nCylinder ";
    std::cout << "before shift:\n";
    cylinder.printCoord();
    cylinder_t.shift(4, 8, 16);
    std::cout << "\n\nCylinder ";
    std::cout << "after shift:\n";
    cylinder.printCoord();

    Shape square(2, coord);
    std::cout << "\n\nSqr";
    std::cout << "\nSquare: " << square.getSquare() << "\nVolume of Square: " << square.getVolume() << std::endl;

    return 0;
}