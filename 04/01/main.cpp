#include <iostream>
#include <random>
#include "shape.h"
#include "transform.h"

int main() {
    std::map<std::string, std::vector<int>> coord;
    coord["x"] = std::vector<int> {1, 4, 6, 9, 3, 12, 5, 12};
    coord["y"] = std::vector<int> {9, 6, 1, 7, 2, 13, 12, 21};
    coord["z"] = std::vector<int> {1, 11, 12, 21, 6, 8, 3, 5};

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