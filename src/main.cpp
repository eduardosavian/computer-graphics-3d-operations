#include <iostream>
#include <GL/freeglut.h>

void display();
void idle();
void keyboard(unsigned char key, int x, int y);

int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitWindowSize(500, 250);

	glutCreateWindow("Desenhando uma linha");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(0, 256, 0, 256, -1, 1);

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
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