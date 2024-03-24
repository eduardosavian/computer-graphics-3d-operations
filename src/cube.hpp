#ifndef CUBE_HPP
#define CUBE_HPP


#include <iostream>
#include <vector>

#include <GL/freeglut.h>
#include <ctime>
#include <cstdlib>
#include <cmath>

struct Cube {
    std::vector<double> vertices;
    std::vector<int> edges;

    Cube();
};

void rotateX(std::vector<double>& vertices, double angle);
void rotateY(std::vector<double>& vertices, double angle);
void displayCube();


#endif