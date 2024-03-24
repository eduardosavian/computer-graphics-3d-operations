#ifndef UTILS_HPP
#define UTILS_HPP


#include <GL/freeglut.h>


void setupGL(int argc, char** argv);
void initGL();
void display();
void reshape(GLsizei width, GLsizei height);
void handleKeypress(unsigned char key, int x, int y);

#endif