#include <iostream>
#include <fstream>
#include <vector>
#include <GL/freeglut.h>
#include <string>
using namespace std;

//globals

unsigned int object;
vector<vector<float>> vertices;
vector<vector<int>> faces;
vector<vector<float>> normals;
vector<vector<float>> textures;
vector<vector<int>> texture_faces;
vector<vector<int>> normal_faces;

float rotation_angle = 0.0;
float rotation_angle_x = 0.0;
float rotation_angle_y = 45.0;
float rotation_angle_z = 0.0;
//float translation_x = 0.0, translation_y = .0, translation_z = .0;
//float scale_factor = 1.0;
float translation_x = 0.0, translation_y = -300.0, translation_z = -800.0;
float scale_factor = 1.0;


void initLights() {
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Configure the ambient, diffuse, and specular components of the light
    GLfloat light0_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light0_diffuse[] = { 0.8, 0/8, 0.8, 1.0 };
    GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);

    // Set the position of the light
    GLfloat light0_position[] = { -50.0, 50.0, -50.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    // Define material properties
    GLfloat color_2[] = { 0.0, 1.0, 0.0, 1.0 }; // Define a second color
    GLfloat color_1[] = { 1.0, 1.0, 1.0, 1.0 }; // Define a first color
    GLfloat shininess = 30.0; // Define shininess coefficient

    // Set material properties for the object
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color_1); // Set ambient and diffuse color
    glMaterialfv(GL_FRONT, GL_SPECULAR, color_2); // Set specular color
    glMaterialf(GL_FRONT, GL_SHININESS, shininess); // Set shininess coefficient
}

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 'w': // Move object up
            translation_y += 10.0;
            cout << "Move object up" << endl;
            break;
        case 's': // Move object down
            translation_y -= 10.0;
            cout << "Move object down" << endl;
            break;
        case 'a': // Move object left
            translation_x -= 10.0;
            cout << "Move object left" << endl;
            break;
        case 'd': // Move object right
            translation_x += 10.0;
            cout << "Move object right" << endl;
            break;
        case 'q': // Move object closer
            translation_z += 10.0;
            cout << "Move object closer" << endl;
            break;
        case 'e': // Move object farther
            translation_z -= 10.0;
            cout << "Move object farther" << endl;
            break;
        case 'i': // Rotate object up (around x-axis)
            rotation_angle_x += 10.0;
            cout << "Rotate object up (around x-axis)" << endl;
            break;
        case 'k': // Rotate object down (around x-axis)
            rotation_angle_x -= 10.0;
            cout << "Rotate object down (around x-axis)" << endl;
            break;
        case 'j': // Rotate object left (around y-axis)
            rotation_angle_y -= 10.0;
            cout << "Rotate object left (around y-axis)" << endl;
            break;
        case 'l': // Rotate object right (around y-axis)
            rotation_angle_y += 10.0;
            cout << "Rotate object right (around y-axis)" << endl;
            break;
        case 'u': // Rotate object clockwise (around z-axis)
            rotation_angle_z += 10.0;
            cout << "Rotate object clockwise (around z-axis)" << endl;
            break;
        case 'o': // Rotate object counterclockwise (around z-axis)
            rotation_angle_z -= 10.0;
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
    ifstream file(fname);
    if (!file.is_open()) {
        cout << "arquivo nao encontrado";
        exit(1);
    }
    else {
        string type;
        while (file >> type)
        {

            if (type == "v")
            {
                float x, y, z;
                file >> x >> y >> z;
                vertices.push_back({x, y, z});
            }

            if (type == "vn")
            {
                float nx, ny, nz;
                file >> nx >> ny >> nz;
                normals.push_back({nx, ny, nz});
            }

            if (type == "vt")
            {
                float u, v;
                file >> u >> v;
                textures.push_back({u, v});
            }

            if (type == "f")
            {
                string v1, v2, v3;
                file >> v1 >> v2 >> v3;

                int v1p, v1t, v1n;
                int v2p, v2t, v2n;
                int v3p, v3t, v3n;

                sscanf(v1.c_str(), "%d/%d/%d", &v1p, &v1t, &v1n);
                sscanf(v2.c_str(), "%d/%d/%d", &v2p, &v2t, &v2n);
                sscanf(v3.c_str(), "%d/%d/%d", &v3p, &v3t, &v3n);

                v1p--; v1t--; v1n--;
                v2p--; v2t--; v2n--;
                v3p--; v3t--; v3n--;

                faces.push_back({v1p, v2p, v3p});
                texture_faces.push_back({v1t, v2t, v3t});
                normal_faces.push_back({v1n, v2n, v3n});

                // vector<int> face;
                // string x, y, z;
                // file >> x >> y >> z;
                // int fp = stoi(x.substr(0, x.find("/"))) - 1;
                // int fs = stoi(y.substr(0, y.find("/"))) - 1;
                // int ft = stoi(z.substr(0, z.find("/"))) - 1;
                // face.push_back(fp);
                // face.push_back(fs);
                // face.push_back(ft);
                // faces.push_back(face);
            }
        }
    }
    

    object = glGenLists(1);
    glPointSize(2.0);
    glNewList(object, GL_COMPILE);
    {
        glPushMatrix();
        glBegin(GL_TRIANGLES);

        for(int i = 0; i < faces.size(); i++)
        {
            vector<int> face = faces[i];
            vector<int> texture_face = texture_faces[i];

            for (int j = 0; j < 3; j++)
        {
            int vertex_index = face[j];
            int texture_index = texture_face[j];

            if (texture_index >= 0 && texture_index < textures.size())
            {
                float u = textures[texture_index][0];
                float v = textures[texture_index][1];
                glTexCoord2f(u, v);
            }

            if (vertex_index >= 0 && vertex_index < vertices.size())
            {
                glVertex3f(vertices[vertex_index][0], vertices[vertex_index][1], vertices[vertex_index][2]);
            }
        }

            // glVertex3f(vertices[face[0]][0], vertices[face[0]][1], vertices[face[0]][2]);
            // glVertex3f(vertices[face[1]][0], vertices[face[1]][1], vertices[face[1]][2]);

            // glVertex3f(vertices[face[1]][0], vertices[face[1]][1], vertices[face[1]][2]);
            // glVertex3f(vertices[face[2]][0], vertices[face[2]][1], vertices[face[2]][2]);

            // glVertex3f(vertices[face[2]][0], vertices[face[2]][1], vertices[face[2]][2]);
            // glVertex3f(vertices[face[0]][0], vertices[face[0]][1], vertices[face[0]][2]);

        }
        glEnd();

    }
    glPopMatrix();
    glEndList();
    file.close();

}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat)w / (GLfloat)h, 0.1, 10000.0);

    glMatrixMode(GL_MODELVIEW);
}

void drawObject()
{
    glPushMatrix();
    glTranslatef(translation_x, translation_y, translation_z);
    glRotatef(rotation_angle, 0, 1, 0);
    glRotatef(rotation_angle_x, 1, 0, 0);
    glRotatef(rotation_angle_y, 0, 1, 0);
    glRotatef(rotation_angle_z, 0, 0, 1);
    glColor3f(0.3, 0.23, 0.27);
    glScalef(scale_factor, scale_factor, scale_factor);
    glCallList(object);
    glPopMatrix();
}
void display(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    drawObject();
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
    initLights();

    glutMainLoop();
    return 0;
}