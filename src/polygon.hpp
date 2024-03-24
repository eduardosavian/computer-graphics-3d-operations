#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <iostream>
#include <GL/freeglut.h>
#include <vector>
#include <cmath>


using vertice = std::pair<double, double>;
using lista_vertices = std::vector<vertice>;
using aresta = std::pair<int, int>;
using lista_arestas = std::vector<aresta>;

struct Polygon {
	double tamanhoLado;
	int numLados;
	vertice posicao;
	vertice escala;
	double rotacao;
	lista_vertices vertices;
	lista_arestas arestas;
};

Polygon criar_Polygon(double posicao_x, double posicao_y, double tamanho_lado, int num_lados);
void desenhar(Polygon Polygon);
void movimentar(Polygon& Polygon, double distancia, double angulo);
void escalar(Polygon& Polygon, double escala_x, double escala_y);
void rotacionar(Polygon& Polygon, double angulo);
void display(Polygon pentagono);
void redraw(int value);
void keyboard(unsigned char key, int x, int y);
void keyboard_special(int key, int x, int y);
void smain(int argc, char** argv);

#endif