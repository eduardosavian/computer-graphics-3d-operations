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
    0, 1, 2, 3,  // Face 0 (Front)
    1, 5, 6, 2,  // Face 1 (Right)
    5, 4, 7, 6,  // Face 2 (Back)
    4, 0, 3, 7,  // Face 3 (Left)
    3, 2, 6, 7,  // Face 4 (Top)
    4, 5, 1, 0   // Face 5 (Bottom)
    };
}


GLfloat colors[32][3] = {
    {0.0f, 1.0f, 0.0f},    // Green
    {1.0f, 0.5f, 0.0f},    // Orange
    {1.0f, 0.0f, 0.0f},    // Red
    {1.0f, 1.0f, 0.0f},    // Yellow
    {0.0f, 0.0f, 1.0f},    // Blue
    {1.0f, 0.0f, 1.0f},    // Magenta
    {0.5f, 0.5f, 0.5f},    // Gray
    {0.0f, 1.0f, 1.0f},    // Cyan
    {1.0f, 0.0f, 0.5f},    // Violet
    {0.5f, 0.0f, 0.5f},    // Purple
    {0.0f, 0.5f, 0.5f},    // Teal
    {0.5f, 0.5f, 1.0f},    // Sky Blue
    {0.8f, 0.8f, 0.8f},    // Light Gray
    {0.5f, 0.0f, 0.0f},    // Maroon
    {0.0f, 0.5f, 0.0f},    // Lime
    {0.0f, 0.0f, 0.5f},    // Navy
    {0.7f, 0.7f, 0.0f},    // Olive
    {0.5f, 0.0f, 0.5f},    // Indigo
    {1.0f, 0.5f, 0.5f},    // Light Red
    {0.5f, 1.0f, 0.5f},    // Light Green
    {1.0f, 1.0f, 0.5f},    // Light Yellow
    {0.5f, 0.5f, 1.0f},    // Light Blue
    {1.0f, 0.5f, 1.0f},    // Light Magenta
    {0.8f, 0.8f, 0.0f},    // Dark Yellow
    {0.5f, 1.0f, 1.0f},    // Light Cyan
    {1.0f, 0.0f, 0.8f},    // Dark Magenta
    {0.0f, 0.8f, 1.0f},    // Lighter Blue
    {0.7f, 0.0f, 0.7f},    // Dark Purple
    {0.0f, 0.7f, 0.7f},    // Dark Cyan
    {0.7f, 0.7f, 0.7f},    // Dark Gray
    {0.3f, 0.3f, 0.3f},    // Very Dark Gray
    {0.5f, 0.0f, 0.2f}    // Dark Maroon
};


void cube() {
    Solid solid = Solid();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpa o buffer de cor e o de profundidade
    glMatrixMode(GL_MODELVIEW);     //Operar na matriz de ModelView

    srand(time(NULL));
    // Renderiza um cubo com 6 quads diferentes
    glLoadIdentity();                 // Reseta para a matriz identidade
    glTranslatef(0.0f, 0.0f, -7.0f);  // Move para a direta da view o que será desenhado

    glBegin(GL_QUADS);                // Começa a desenhar o cubo
    for (uint i = 0; i < solid.faces.size(); i += 4) {
        // Mude a cor a cada iteração
        int colorIndex = rand() % 32;  // Generate a random index within the range of colors
        glColor3fv(colors[colorIndex]);

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


#endif