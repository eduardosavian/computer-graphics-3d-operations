#ifndef SOLID_CPP
#define SOLID_CPP


#include "solid.hpp"

Solid::Solid() {
    // Define the 8 vertices of the cube
    vertices = {
        -1.0, -1.0, -1.0,  // Vertex 0
        1.0, -1.0, -1.0,  // Vertex 1
        1.0,  1.0, -1.0,  // Vertex 2
        -1.0,  1.0, -1.0,  // Vertex 3
        -1.0, -1.0,  1.0,  // Vertex 4
        1.0, -1.0,  1.0,  // Vertex 5
        1.0,  1.0,  1.0,  // Vertex 6
        -1.0,  1.0,  1.0   // Vertex 7
    };

    // Define the 6 faces of the cube, each face is made up of 2 triangles
    faces = {
        0, 1, 2, 2, 3, 0,  // Face 0
        4, 5, 6, 6, 7, 4,  // Face 1
        0, 1, 5, 5, 4, 0,  // Face 2
        2, 3, 7, 7, 6, 2,  // Face 3
        0, 4, 7, 7, 3, 0,  // Face 4
        1, 5, 6, 6, 2, 1   // Face 5
    };
}

Solid solid = Solid();

void cube2() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpa o buffer de cor e o de profundidade
    glMatrixMode(GL_MODELVIEW);     //Operar na matriz de ModelView

    // Renderiza um cubo com 6 quads diferentes
    glLoadIdentity();                 // Reseta para a matriz identidade
    glTranslatef(0.0f, 0.0f, -7.0f);  // Move para a direta da view o que será desenhado

    glBegin(GL_QUADS);                // Começa a desenhar o cubo
    for (uint i = 0; i < solid.faces.size(); i += 4) {
        // Define os vértices em ordem anti-horária com a face apontando para cima
        // Mude a cor a cada iteração
        if (i == 0) {
            glColor3f(0.0f, 1.0f, 0.0f);     // Verde
        } else if (i == 4) {
            glColor3f(1.0f, 0.5f, 0.0f);     // Laranja
        } else if (i == 8) {
            glColor3f(1.0f, 0.0f, 0.0f);     // Vermelho
        } else if (i == 12) {
            glColor3f(1.0f, 1.0f, 0.0f);     // Amarelo
        } else if (i == 16) {
            glColor3f(0.0f, 0.0f, 1.0f);     // Azul
        } else if (i == 20) {
            glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
        }

        // Draw the vertices for the current face
        for (uint j = 0; j < 4; ++j) {
            int vertexIndex = solid.faces[i + j];
            double x = solid.vertices[vertexIndex * 3];
            double y = solid.vertices[vertexIndex * 3 + 1];
            double z = solid.vertices[vertexIndex * 3 + 2];
            glVertex3d(x, y, z);
        }
    }


    
    glEnd();

    glutSwapBuffers();  // Double Buffer, troca o atual pelo que está aguardando

}

void cube() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpa o buffer de cor e o de profundidade
    glMatrixMode(GL_MODELVIEW);     //Operar na matriz de ModelView

    // Renderiza um cubo com 6 quads diferentes
    glLoadIdentity();                 // Reseta para a matriz identidade
    glTranslatef(1.5f, 0.0f, -10.0f);  // Move para a direta da view o que será desenhado

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

    glutSwapBuffers();  // Double Buffer, troca o atual pelo que está aguardando
}

#endif