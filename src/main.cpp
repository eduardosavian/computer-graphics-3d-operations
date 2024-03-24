#include <iostream>

#include "utils.hpp"
#include "cube.hpp"


int main(int argc, char** argv) {
	setupGL(argc, argv);

    glutDisplayFunc(cube);

    glutReshapeFunc(reshape);
	glutKeyboardFunc(handleKeypress); // Register the keyboard callback function

    initGL();

	return 0;
}
