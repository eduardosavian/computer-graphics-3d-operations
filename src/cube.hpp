#ifndef CUBE_HPP
#define CUBE_HPP



#include <vector>

#include <GL/freeglut.h>

struct Cube {
    std::vector<double> vertices;
    std::vector<int> edges;

    Cube();
    void rotateX(std::vector<double>& vertices, double angle);
    void rotateY(std::vector<double>& vertices, double angle);
    void rotateZ(std::vector<double>& vertices, double angle);
};

void displayCube();


#endif