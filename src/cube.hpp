#ifndef CUBE_HPP
#define CUBE_HPP


#include <iostream>
#include <vector>

#include <GL/freeglut.h>
#include <ctime>
#include <cstdlib>


struct Cube {
    std::vector<double> vertices;
    std::vector<int> edges;

    Cube();
};


void cube();


#endif