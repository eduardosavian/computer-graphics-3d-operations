#ifndef SOLID_HPP
#define SOLID_HPP

#include <iostream>
#include <vector>

#include <GL/freeglut.h>

struct Solid {
    std::vector<double> vertices;
    std::vector<int> faces;

    Solid();

};

void cube();
void cube2();
#endif