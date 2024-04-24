#include <iostream>
#include <fstream>
#include <vector>
#include <GL/freeglut.h>
#include <string>
using namespace std;

// globals

float rotation_angle = 0.0;
float rotation_angle_x = 0.0;
float rotation_angle_y = -45.0;
float rotation_angle_z = 0.0;
float translation_x = 0.0, translation_y = 0.0, translation_z = 0.0;
float scale_factor = 1.0;

struct Object
{
    vector<vector<float>> vertices;
    vector<vector<int>> faces;
    vector<vector<int>> normal_faces;
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
                vector<float> vertice;
                arquivo >> x >> y >> z;
                vertice.push_back(x);
                vertice.push_back(y);
                vertice.push_back(z);
                object.vertices.push_back(vertice);
            }

            if (tipo == "f")
            {
                vector<int> face;
                string v1, v2, v3;
                arquivo >> v1 >> v2 >> v3;

                vector<int> indices1;
                indices1.reserve(3); // Reserve space for 3 indices

                size_t pos1 = v1.find_first_of('/');
                size_t pos2 = v2.find_first_of('/');
                size_t pos3 = v3.find_first_of('/');

                // Extract the first set of vertex indices
                string vf1 = v1.substr(0, pos1);
                string vf2 = v2.substr(0, pos2);
                string vf3 = v3.substr(0, pos3);

                indices1.push_back(stoi(vf1) - 1);
                indices1.push_back(stoi(vf2) - 1);
                indices1.push_back(stoi(vf3) - 1);

                object.faces.push_back(indices1);

                vector<int> indices2;
                indices2.reserve(3); // Reserve space for 3 indices

                // Extract the second set of vertex indices
                vf1 = v1.substr(v1.find_last_of('/') + 1);
                vf2 = v2.substr(v2.find_last_of('/') + 1);
                vf3 = v3.substr(v3.find_last_of('/') + 1);

                indices2.push_back(stoi(vf1) - 1);
                indices2.push_back(stoi(vf2) - 1);
                indices2.push_back(stoi(vf3) - 1);

                object.normal_faces.push_back(indices2);
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
            vector<int> face = object.faces[i];
            vector<int> normal_face = object.normal_faces[i];

            for (int j = 0; j < 3; j++)
            {
                int vertexIndex = face[j];
                int normalIndex = normal_face[j];

                // glNormal3f(
                //     object.vertices[normalIndex][0],
                //     object.vertices[normalIndex][1],
                //     object.vertices[normalIndex][2]);
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
    gluPerspective(100, (GLfloat)w / (GLfloat)h, 0.1, 1000.0);

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