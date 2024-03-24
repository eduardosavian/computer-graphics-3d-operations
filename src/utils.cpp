#ifndef UTILS_CPP
#define UTILS_CPP

#include "utils.hpp"


void setupGL(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE); // Double buffer

    glutInitWindowSize(640, 640);
    glutInitWindowPosition(50, 50);

    glutCreateWindow("3D Shapes");
}

void initGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //Coloca a cor de background para preto e opaco
    glClearDepth(1.0f);                   // Define o buffer de profundidade para o mais distante possível
    glEnable(GL_DEPTH_TEST);   // Habilita o culling de profundidade
    glDepthFunc(GL_LEQUAL);    // Define o tipo de teste de profundidade
}


//Função de redesenhou prioriza o aspecto da projeção
void reshape(GLsizei width, GLsizei height) {
    if (height == 0) height = 1;
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}


#endif