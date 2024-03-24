#include <iostream>

#include "utils.hpp"
#include "solid.hpp"


int main(int argc, char** argv) {
	setupGL(argc, argv);

    glutDisplayFunc(cube2);
    glutReshapeFunc(reshape);

    initGL();
    glutMainLoop();

	return 0;
}
