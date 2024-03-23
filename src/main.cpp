#include <iostream>

#include "utils.hpp"
#include "polygon.hpp"
#include "solid.hpp"


int main(int argc, char** argv) {
	InitGL(argc, argv);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpa o buffer de cor e o de profundidade
    glMatrixMode(GL_MODELVIEW);     //Operar na matriz de ModelView

    // Renderiza um cubo com 6 quads diferentes
    glLoadIdentity();                 // Reseta para a matriz identidade
    glTranslatef(1.5f, 0.0f, -7.0f);  // Move para a direta da view o que será desenhado

    glBegin(GL_QUADS);                // Começa a desenhar o cubo
       // Face de cima (y = 1.0f)
       // Define os vértice em ordem anti-horário com a face apontando para cima
    glColor3f(0.0f, 1.0f, 0.0f);     // Verde
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);

    // Face de cima (y = -1.0f)
    glColor3f(1.0f, 0.5f, 0.0f);     // Laranja
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);

    // Face da frente  (z = 1.0f)
    glColor3f(1.0f, 0.0f, 0.0f);     // Vermelho
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);

    // Face de trás (z = -1.0f)
    glColor3f(1.0f, 1.0f, 0.0f);     // Amarelo
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);

    // Face esquerda (x = -1.0f)
    glColor3f(0.0f, 0.0f, 1.0f);     // Azul
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    // Face direita (x = 1.0f)
    glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glEnd();

	return 0;
}