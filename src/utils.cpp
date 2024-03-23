#ifndef UTILS_CPP
#define UTILS_CPP


#include "utils.hpp"


void InitGL(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitWindowSize(512, 512);

	glutCreateWindow("Drawings");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(0, 256, 0, 256, -1, 1);

	// glutDisplayFunc(display);
	// glutKeyboardFunc(keyboard);
	// glutSpecialFunc(keyboard_special);
	// glutTimerFunc(10, redraw, 0);

	glutMainLoop();

    // glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    // glClear(GL_COLOR_BUFFER_BIT);
    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    // glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    // glMatrixMode(GL_MODELVIEW);
    // glLoadIdentity();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //Coloca a cor de background para preto e opaco
    glClearDepth(1.0f);                   // Define o buffer de profundidade para o mais distante possível
    glEnable(GL_DEPTH_TEST);   // Habilita o culling de profundidade
    glDepthFunc(GL_LEQUAL);    // Define o tipo de teste de profundidade
}


#endif