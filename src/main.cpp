#include <iostream>
#include <fstream>
#include <vector>
#include <GL/freeglut.h>
#include <string>
using namespace std;

//globals

unsigned int elefante;
vector<vector<float>> vertices;
vector<vector<int>> faces;
float rot_ele;

float rotation_angle = 0.0;
float rotation_angle_x = 0.0;
float rotation_angle_y = 45.0;
float rotation_angle_z = 0.0;
//float translation_x = 0.0, translation_y = .0, translation_z = .0;
//float scale_factor = 1.0;
float translation_x = 0.0, translation_y = -300.0, translation_z = -800.0;
float scale_factor = 1.0;

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 'w': // Move object up
            translation_y += 1.0;
            cout << "Move object up" << endl;
            break;
        case 's': // Move object down
            translation_y -= 1.0;
            cout << "Move object down" << endl;
            break;
        case 'a': // Move object left
            translation_x -= 1.0;
            cout << "Move object left" << endl;
            break;
        case 'd': // Move object right
            translation_x += 1.0;
            cout << "Move object right" << endl;
            break;
        case 'q': // Move object closer
            translation_z += 1.0;
            cout << "Move object closer" << endl;
            break;
        case 'e': // Move object farther
            translation_z -= 1.0;
            cout << "Move object farther" << endl;
            break;
        case 'i': // Rotate object up (around x-axis)
            rotation_angle_x += 1.0;
            cout << "Rotate object up (around x-axis)" << endl;
            break;
        case 'k': // Rotate object down (around x-axis)
            rotation_angle_x -= 1.0;
            cout << "Rotate object down (around x-axis)" << endl;
            break;
        case 'j': // Rotate object left (around y-axis)
            rotation_angle_y -= 1.0;
            cout << "Rotate object left (around y-axis)" << endl;
            break;
        case 'l': // Rotate object right (around y-axis)
            rotation_angle_y += 1.0;
            cout << "Rotate object right (around y-axis)" << endl;
            break;
        case 'u': // Rotate object clockwise (around z-axis)
            rotation_angle_z += 1.0;
            cout << "Rotate object clockwise (around z-axis)" << endl;
            break;
        case 'o': // Rotate object counterclockwise (around z-axis)
            rotation_angle_z -= 1.0;
            cout << "Rotate object counterclockwise (around z-axis)" << endl;
            break;
        case '+': // Scale up
            scale_factor += 0.1;
            cout << "Scale up" << endl;
            break;
        case '-': // Scale down
            scale_factor -= 0.1;
            cout << "Scale down" << endl;
            break;
        case 27: // ESC key to exit
            exit(0);
            break;
    }
    glutPostRedisplay(); // Redraw scene
}



void loadObj(string fname)
{
    int read;
    float x, y, z;
    ifstream arquivo(fname);
    if (!arquivo.is_open()) {
        cout << "arquivo nao encontrado";
        exit(1);
    }
    else {
        string tipo;
        while (arquivo >> tipo)
        {

            if (tipo == "v")
            {
                vector<float> vertice;
                float x, y, z;
                arquivo >> x >> y >> z;
                vertice.push_back(x);
                vertice.push_back(y);
                vertice.push_back(z);
                vertices.push_back(vertice);
            }

            if (tipo == "f")
            {
                vector<int> face;
                string x, y, z;
                arquivo >> x >> y >> z;
                int fp = stoi(x.substr(0, x.find("/"))) - 1;
                int fs = stoi(y.substr(0, y.find("/"))) - 1;
                int ft = stoi(z.substr(0, z.find("/"))) - 1;
                face.push_back(fp);
                face.push_back(fs);
                face.push_back(ft);
                faces.push_back(face);
            }
        }
    }


    elefante = glGenLists(1);
    glPointSize(2.0);
    glNewList(elefante, GL_COMPILE);
    {
        glPushMatrix();
        glBegin(GL_LINES);

        for(int i = 0; i < faces.size(); i++)
        {
            vector<int> face = faces[i];

            glVertex3f(vertices[face[0]][0], vertices[face[0]][1], vertices[face[0]][2]);
            glVertex3f(vertices[face[1]][0], vertices[face[1]][1], vertices[face[1]][2]);

            glVertex3f(vertices[face[1]][0], vertices[face[1]][1], vertices[face[1]][2]);
            glVertex3f(vertices[face[2]][0], vertices[face[2]][1], vertices[face[2]][2]);

            glVertex3f(vertices[face[2]][0], vertices[face[2]][1], vertices[face[2]][2]);
            glVertex3f(vertices[face[0]][0], vertices[face[0]][1], vertices[face[0]][2]);

        }
        glEnd();

    }
    glPopMatrix();
    glEndList();
    arquivo.close();

}


void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat)w / (GLfloat)h, 0.1, 10000.0);

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

void timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(10, timer, 0);
}

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        cout << "Usage: " << argv[0] << " <obj_file_name>" << endl;
        return 1;
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
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