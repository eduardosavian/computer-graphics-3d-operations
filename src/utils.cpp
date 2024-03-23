#ifndef UTILS_CPP
#define UTILS_CPP

#include "utils.hpp"




// void keyboard(unsigned char key, int x, int y) {
// 	std::cout << key;
// 	switch (key) {
// 	case 27:
// 		exit(0);
// 		break;
// 	case ' ':

// 		break;
// 	}
// }

// void keyboard_special(int key, int x, int y) {
// 	std::cout << key;
// 	switch (key) {
// 	case GLUT_KEY_DOWN:

// 		break;

// 	case GLUT_KEY_UP:

// 		break;

// 	case GLUT_KEY_RIGHT:

// 		break;

// 	case GLUT_KEY_LEFT:

// 		break;

// 	}
// }

// void redraw(int value) {
// 	glutPostRedisplay();
// 	glutTimerFunc(delay, redraw, 0);
// }


// void desenhar() {
// 	glColor3f(0.0, 0.0, 0.0);
// 	glBegin(GL_LINES);
// 	glVertex2f(2, 2);
// 	glVertex2f(10,10);
// 	glEnd();
// }

// void display(void) {
// 	glClear(GL_COLOR_BUFFER_BIT);

// 	desenhar();

// 	glFlush();
// }


// void InitGL(int argc, char** argv) {
//     glutInit(&argc, argv);

//     glutInitWindowSize(512, 512);

// 	glutCreateWindow("Drawings");
// 	glClearColor(1.0, 1.0, 1.0, 1.0);
// 	glOrtho(0, 256, 0, 256, -1, 1);

//     glutDisplayFunc(display);


//     glutDisplayFunc(display);
// 	glutKeyboardFunc(keyboard);
// 	glutSpecialFunc(keyboard_special);
// 	glutTimerFunc(10, redraw, 0);

// 	glutMainLoop();
// }


#endif