#ifndef POLYGON_CPP
#define POLYGON_CPP


#include "polygon.hpp"


Polygon polygon;

int delay = 10;

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	desenhar(polygon);

	glFlush();
}

void keyboard(unsigned char key, int x, int y) {
	std::cout << key;
	switch (key) {
	case 27:
		exit(0);
		break;
	case ' ':
		escalar(polygon, 1.1, 1.1);
		break;
	}
}

void keyboard_special(int key, int x, int y) {
	std::cout << key;
	switch (key) {
	case GLUT_KEY_DOWN:
		movimentar(polygon, 10, (270 / 180.0) * 3.1416);
		break;

	case GLUT_KEY_UP:
		movimentar(polygon, 10, (90 / 180.0) * 3.1416);
		break;

	case GLUT_KEY_RIGHT:
		movimentar(polygon, 10, (0 / 180.0) * 3.1416);
		break;

	case GLUT_KEY_LEFT:
		movimentar(polygon, 10, (180 / 180.0) * 3.1416);
		break;

	}
}

void redraw(int value) {
	glutPostRedisplay();
	glutTimerFunc(delay, redraw, 0);
}

Polygon criar_Polygon(double posicao_x, double posicao_y, double tamanho_lado, int num_lados) {
	Polygon novo_Polygon;
	novo_Polygon.numLados = num_lados;
	novo_Polygon.posicao.first = posicao_x;
	novo_Polygon.posicao.second = posicao_y;
	novo_Polygon.tamanhoLado = tamanho_lado;

	novo_Polygon.escala.first = 1;
	novo_Polygon.escala.second = 1;

	novo_Polygon.rotacao = 0;

	float angulo = 0;
	float passo_angulo = ((360 / float(num_lados)) * 3.1415926536) / 180.0;

	float apothem = tamanho_lado / (2 * tan(3.1416 / float(num_lados)));
	posicao_x -= tamanho_lado / 2.0;
	posicao_y -= apothem;

	novo_Polygon.vertices.push_back(vertice(posicao_x, posicao_y));
	std::cout << "Vertices:\n";
	std::cout << 0 << " - " << posicao_x << " - " << posicao_y << "\n";
	for (int i = 1; i < num_lados; i++) {
		posicao_x = posicao_x + tamanho_lado * cos(angulo);
		posicao_y = posicao_y + tamanho_lado * sin(angulo);
		novo_Polygon.vertices.push_back(vertice(posicao_x, posicao_y));
		std::cout << i << " - " << posicao_x << " - " << posicao_y << "\n";
		angulo += passo_angulo;
	}

	std::cout << "Arestas:\n";
	for (int i = 0; i < num_lados; i++) {
		novo_Polygon.arestas.push_back(aresta(i, (i + 1) % num_lados));
		std::cout << i << " - " << (i + 1) % num_lados << "\n";
	}


	return novo_Polygon;
}

void movimentar(Polygon& Polygon, double distancia, double angulo) {
	
}

void escalar(Polygon& Polygon, double escala_x, double escala_y) {
	
}

void rotacionar(Polygon& Polygon, double angulo) {

}

void desenhar(Polygon Polygon) {
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	for (int i = 0; i < Polygon.arestas.size(); i++) {
		float v_o = Polygon.arestas[i].first;
		float v_d = Polygon.arestas[i].second;
		glVertex2f(Polygon.vertices[v_o].first, Polygon.vertices[v_o].second);
		glVertex2f(Polygon.vertices[v_d].first, Polygon.vertices[v_d].second);
	}
	glEnd();
}



void smain(int argc, char** argv) {
    polygon = criar_Polygon(128, 128, 30, 5);

	glutInit(&argc, argv);

	glutInitWindowSize(512, 512);

	glutCreateWindow("Drawings");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(0, 256, 0, 256, -1, 1);

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboard_special);
	glutTimerFunc(10, redraw, 0);

	glutMainLoop();
}
#endif