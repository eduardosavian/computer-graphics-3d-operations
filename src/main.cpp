#include <iostream>
#include <fstream>
#include <vector>
#include <GL/freeglut.h>
#include <string>
using namespace std;


// globals
unsigned int elephant;
vector<vector<float>> vertices;
vector<vector<int>> faces;
vector<vector<float>> normals;
vector<vector<float>> textures;
vector<vector<int>> texture_faces;
vector<vector<int>> normal_faces;

float rot_ele = 0.0;
float rot_ele_x = 0.0;
float rot_ele_y = 0.0;
float rot_ele_z = 0.0;
float trans_x = 0.0, trans_y = -40.0, trans_z = -205.0;
float scale_factor = 0.7;
bool lights[3] = { true, true, true }; // Array para controlar as luzes (ativadas/desativadas)

// Defina as posições das luzes
GLfloat light0_position[] = { -50.0, 50.0, -50.0, 1.0 };
GLfloat light1_position[] = { 50.0, 50.0, -50.0, 1.0 };
GLfloat light2_position[] = { 0.0, -50.0, 0.0, 1.0 };

void initLights() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Configure the ambient, diffuse, and specular components of the light
    GLfloat light0_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light0_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);

    // Set the position of the light
    GLfloat light0_position[] = { -50.0, 50.0, -50.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
}

void toggleLights() {
    for (int i = 0; i < 3; ++i) {
        if (lights[i])
            glEnable(GL_LIGHT0 + i);
        else
            glDisable(GL_LIGHT0 + i);
    }
}


void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 'w': // Move object up
            trans_y += 1.0;
            break;
        case 's': // Move object down
            trans_y -= 1.0;
            break;
        case 'a': // Move object left
            trans_x -= 1.0;
            break;
        case 'd': // Move object right
            trans_x += 1.0;
            break;
        case 'q': // Move object closer
            trans_z += 1.0;
            break;
        case 'e': // Move object farther
            trans_z -= 1.0;
            break;
        case 'i': // Rotate object up (around x-axis)
            rot_ele_x += 1.0;
            break;
        case 'k': // Rotate object down (around x-axis)
            rot_ele_x -= 1.0;
            break;
        case 'j': // Rotate object left (around y-axis)
            rot_ele_y -= 1.0;
            break;
        case 'l': // Rotate object right (around y-axis)
            rot_ele_y += 1.0;
            break;
        case 'u': // Rotate object clockwise (around z-axis)
            rot_ele_z += 1.0;
            break;
        case 'o': // Rotate object counterclockwise (around z-axis)
            rot_ele_z -= 1.0;
            break;
        case '+': // Scale up
            scale_factor += 0.1;
            break;
        case '-': // Scale down
            scale_factor -= 0.1;
            break;
        case 27: // ESC key to exit
            exit(0);
            break;
        case '1': // Ativar/desativar luz 1
            lights[0] = !lights[0];
            toggleLights();
            break;
        case '2': // Ativar/desativar luz 2
            lights[1] = !lights[1];
            toggleLights();
            break;
        case '3': // Ativar/desativar luz 3
            lights[2] = !lights[2];
            toggleLights();
            break;
    }
    glutPostRedisplay(); // Redraw scene
}

void loadObj(string fname)
{
    int read;
    float x, y, z;
    ifstream file(fname);
    if (!file.is_open())
    {
        cout << "file not found";
        exit(1);
    }
    else
    {
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
            }
        }
    }

    file.close();
}

void createElephantDisplayList()
{
    elephant = glGenLists(1); // Generate a new display list ID
    glNewList(elephant, GL_COMPILE); // Begin compiling the display list
    glPushMatrix(); // Push the current matrix onto the stack

    glBegin(GL_TRIANGLES); // Begin drawing triangles
    for (int i = 0; i < faces.size(); i++)
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
    }
    glEnd();

    glPopMatrix();
    glEndList();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat)w / (GLfloat)h, 0.1, 1000.0);

    glMatrixMode(GL_MODELVIEW);
}

void drawElephant()
{
    glPushMatrix();


    glTranslatef(trans_x, trans_y, trans_z);


    glRotatef(rot_ele, 0, 1, 0);
    glRotatef(rot_ele_x, 1, 0, 0);
    glRotatef(rot_ele_y, 0, 1, 0);
    glRotatef(rot_ele_z, 0, 0, 1);

    glColor3f(1.0, 0.23, 0.27);
    glScalef(scale_factor, scale_factor, scale_factor);


    glCallList(elephant);

    glPopMatrix();
}

void display(void)
{
    // Set background color to pink
    glClearColor(1.0, 0.75, 0.8, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Enable lighting
    glEnable(GL_LIGHTING);

    // Configure light 0 as a directional light
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    GLfloat light0_direction[] = { 0.0, -1.0, 0.0, 0.0 }; // Directional light pointing downwards
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0_direction);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180.0); // Set cutoff angle to 180 degrees for directional light

    // Set light colors
    GLfloat light0_diffuse[] = { 1.0, 0.0, 0.0, 1.0 }; // Red color for light 0 (directional)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);

    // Draw the elephant
    drawElephant();

    // Swap buffers
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
    glutInitWindowSize(800, 450);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("Load OBJ");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutTimerFunc(10, timer, 0);
    loadObj(argv[1]);
    createElephantDisplayList();

    glutKeyboardFunc(keyboard);
    initLights(); // Inicializa as luzes


    glutMainLoop();
    return 0;
}
