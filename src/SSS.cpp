#include <GL/glut.h>


void initGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //Coloca a cor de background para preto e opaco
    glClearDepth(1.0f);                   // Define o buffer de profundidade para o mais distante possível
    glEnable(GL_DEPTH_TEST);   // Habilita o culling de profundidade
    glDepthFunc(GL_LEQUAL);    // Define o tipo de teste de profundidade
}


void display() {
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

    // Renderiza uma pirâmide com 4 triângulos
    glLoadIdentity();                  // Reseta a matriz de modelview
    glTranslatef(-1.5f, 0.0f, -6.0f);  // Move para a esquerda na tela o que será desenhado

    glBegin(GL_TRIANGLES);           // Começa a desenhar a pirâmide com  4 triângulos
       // Frente
    glColor3f(1.0f, 0.0f, 0.0f);     // Vermelho
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);     // Verde
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glColor3f(0.0f, 0.0f, 1.0f);     // Azul
    glVertex3f(1.0f, -1.0f, 1.0f);

    // Direita
    glColor3f(1.0f, 0.0f, 0.0f);     // Vermelho
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);     // Azul
    glVertex3f(1.0f, -1.0f, 1.0f);
    glColor3f(0.0f, 1.0f, 0.0f);     // Verde
    glVertex3f(1.0f, -1.0f, -1.0f);

    // Trás
    glColor3f(1.0f, 0.0f, 0.0f);    // Vermelho
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);     // Verde
    glVertex3f(1.0f, -1.0f, -1.0f);
    glColor3f(0.0f, 0.0f, 1.0f);     // Azul
    glVertex3f(-1.0f, -1.0f, -1.0f);

    // Esquerda
    glColor3f(1.0f, 0.0f, 0.0f);       // Vermelho
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);       // Azul
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glColor3f(0.0f, 1.0f, 0.0f);       // Verde
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glEnd();

    glutSwapBuffers();  // Double Buffer, troca o atual pelo que está aguardando
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


int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE); // Double buffer

    glutInitWindowSize(640, 480);
    glutInitWindowPosition(50, 50);

    glutCreateWindow("3D Shapes");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    initGL();
    glutMainLoop();
    return 0;
}
