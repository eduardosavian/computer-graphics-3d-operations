#ifndef POLYGON_CPP
#define POLYGON_CPP

#include "polygon.hpp"

void show() {

	glutInitWindowSize(500, 250);

	glutCreateWindow("Desenhando uma linha");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(0, 256, 0, 256, -1, 1);

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);

	glBegin(GL_LINES);
	glVertex2i(10, 10);
	glVertex2i(245, 245);
	glEnd();

	glFlush();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(0);
		break;
	}
}

void idle() {

}

#endif