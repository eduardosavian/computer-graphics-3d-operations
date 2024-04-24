#include <iostream>
#include <fstream>
#include <vector>
#include <GL/freeglut.h>
#include <string>
#include "linalg.hpp"
using namespace std;

// globals

float rotation_angle = 0.0;
float rotation_angle_x = 0.0;
float rotation_angle_y = -45.0;
float rotation_angle_z = 0.0;
float translation_x = 0.0, translation_y = 0.0, translation_z = 0.0;
float scale_factor = 1.0;

using vec3 = linalg::vector<float, 3>;
using vec3i = linalg::vector<int, 3>;
using vec2 = linalg::vector<float, 2>;

struct Object
{
    vector<vec3> vertices;
    vector<vec3i> faces;
    vector<vec3i> normal_faces;
};

unsigned int elefante;
Object object;

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    // Movement controls
    case 'w':
        translation_y += 10.0;
        break; // Move object up
    case 's':
        translation_y -= 10.0;
        break; // Move object down
    case 'a':
        translation_x -= 10.0;
        break; // Move object left
    case 'd':
        translation_x += 10.0;
        break; // Move object right
    case 'q':
        translation_z += 10.0;
        break; // Move object closer
    case 'e':
        translation_z -= 10.0;
        break; // Move object farther

    // Rotation controls
    case 'i':
        rotation_angle_x += 10.0;
        break; // Rotate object up (around x-axis)
    case 'k':
        rotation_angle_x -= 10.0;
        break; // Rotate object down (around x-axis)
    case 'j':
        rotation_angle_y -= 10.0;
        break; // Rotate object left (around y-axis)
    case 'l':
        rotation_angle_y += 10.0;
        break; // Rotate object right (around y-axis)
    case 'u':
        rotation_angle_z += 10.0;
        break; // Rotate object clockwise (around z-axis)
    case 'o':
        rotation_angle_z -= 10.0;
        break; // Rotate object counterclockwise (around z-axis)
    // Scaling controls
    case '+':
        scale_factor += 0.1;
        break; // Scale up
    case '-':
        scale_factor -= 0.1;
        break; // Scale down
    }
}
void loadObj(string fname)
{
    float x, y, z;
    ifstream arquivo(fname);
    if (!arquivo.is_open())
    {
        cout << "arquivo nao encontrado";
        exit(1);
    }
    else
    {
        string tipo;
        while (arquivo >> tipo)
        {
            if (tipo == "v")
            {
                vec3 vertice;
                arquivo >> x >> y >> z;
                vertice[0] = x;
                vertice[1] = y;
                vertice[2] = z;
                object.vertices.push_back(vertice);
            }

            if (tipo == "f")
            {
                vec3i face;
                string v1, v2, v3;
                arquivo >> v1 >> v2 >> v3;

                size_t pos1 = v1.find_first_of('/');
                size_t pos2 = v2.find_first_of('/');
                size_t pos3 = v3.find_first_of('/');

                string vf1 = v1.substr(0, pos1);
                string vf2 = v2.substr(0, pos2);
                string vf3 = v3.substr(0, pos3);

                face[0] = stoi(vf1) - 1;
                face[1] = stoi(vf2) - 1;
                face[2] = stoi(vf3) - 1;

                object.faces.push_back(face);

                vec3i normal;

                vf1 = v1.substr(v1.find_last_of('/') + 1);
                vf2 = v2.substr(v2.find_last_of('/') + 1);
                vf3 = v3.substr(v3.find_last_of('/') + 1);

                normal[0] = stoi(vf1) - 1;
                normal[1] = stoi(vf2) - 1;
                normal[2] = stoi(vf3) - 1;

                object.normal_faces.push_back(normal);
            }
        }
        arquivo.close(); // Close the file after reading
    }

    glClear(GL_COLOR_BUFFER_BIT);

    elefante = glGenLists(1);
    glPointSize(2.0);
    glNewList(elefante, GL_COMPILE);
    glPushMatrix();
    GLfloat green[] = {0.0, 1.0, 0.0, 1.0};
    glMaterialfv(GL_FRONT, GL_SPECULAR, green);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, green);
    glMaterialf(GL_FRONT, GL_SHININESS, 60);

    {
        glPushMatrix();
        glBegin(GL_TRIANGLES);
        for (size_t i = 0; i < object.faces.size(); i++)
        {
            vec3i face = object.faces[i];
            vec3i normal_face = object.normal_faces[i];

            for (int j = 0; j < 3; j++)
            {
                int vertexIndex = face[j];
                int normalIndex = normal_face[j];
                //cout << "vertexIndex: " << vertexIndex << " normalIndex: " << normalIndex << endl;
                //cout << "vertex: " << object.vertices[vertexIndex][0] << " " << object.vertices[vertexIndex][1] << " " << object.vertices[vertexIndex][2] << endl;

                glNormal3f(
                    object.vertices[normalIndex][0],
                    object.vertices[normalIndex][1],
                    object.vertices[normalIndex][2]);
                glVertex3f(
                    object.vertices[vertexIndex][0],
                    object.vertices[vertexIndex][1],
                    object.vertices[vertexIndex][2]);
            }
        }
        glEnd();
        glPopMatrix();
        glEndList();
        arquivo.close();
    }
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat)w / (GLfloat)h, 0.5, 2000.0);

    glMatrixMode(GL_MODELVIEW);
}
void drawElephant()
{
    glPushMatrix();
    glTranslatef(translation_x, translation_y, translation_z);
    glRotatef(rotation_angle, 0, 1, 0);
    glRotatef(rotation_angle_x, 1, 0, 0);
    glRotatef(rotation_angle_y, 0, 1, 0);
    glRotatef(rotation_angle_z, 0, 0, 1);
    glColor3f(0.3, 0.23, 0.27);
    glScalef(scale_factor, scale_factor, scale_factor);
    glCallList(elefante);
    glPopMatrix();
}

void display(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    drawElephant();
    glutSwapBuffers();
}

void timer(int value)
{
    glutPostRedisplay();
    glutTimerFunc(10, timer, 0);
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " <obj_file_name>" << endl;
        return 1;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 450);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("Carregar OBJ");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutTimerFunc(10, timer, 0);
    loadObj(argv[1]);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}