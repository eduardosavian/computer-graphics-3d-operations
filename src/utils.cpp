#ifndef UTILS_CPP
#define UTILS_CPP


#include "utils.hpp"


void InitGL(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitWindowSize(512, 512);

	glutCreateWindow("Drawings");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(0, 256, 0, 256, -1, 1);
}


#endif