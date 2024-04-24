#include <iostream>
#include <fstream>
#include <vector>
#include <GL/freeglut.h>
#include <string>
#include <cmath>
using namespace std;

// Globals
unsigned int object;
vector<vector<float>> vertices;
vector<vector<int>> faces;
vector<vector<float>> normals;
vector<vector<float>> textures;
vector<vector<int>> texture_faces;
vector<vector<int>> normal_faces;

float rotation_angle = 0.0;
float rotation_angle_x = 0.0;
float rotation_angle_y = -45.0;
float rotation_angle_z = 0.0;
float translation_x = 0.0, translation_y = 0.0, translation_z = 0.0;
float scale_factor = 1.0;

void initLight()
{
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat qaAmbientLight[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat qaDiffuseLight[] = {0.8, 0.8, 0.8, 1.0};
    GLfloat qaSpecularLight[] = {1.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);

    GLfloat qaLightPosition[] = {0.6, 0.6, 0.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);
}

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
    case '1':
        static bool diffuseEnabled = true;
        if (diffuseEnabled)
            glDisable(GL_LIGHT0); // Disable diffuse light
        else
            glEnable(GL_LIGHT0); // Enable diffuse light
        diffuseEnabled = !diffuseEnabled;
        break;

    // Toggle specular light
    case '2':
        static bool specularEnabled = true;
        if (specularEnabled)
            glDisable(GL_LIGHTING); // Disable specular light
        else
            glEnable(GL_LIGHTING); // Enable specular light
        specularEnabled = !specularEnabled;
        break;

    // Toggle ambient light
    case '3':
        static bool ambientEnabled = true;
        if (ambientEnabled)
        {
            GLfloat qaAmbientLight[] = {0.2, 0.2, 0.2, 1.0};  // Adjust ambient light color and intensity here
            glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight); // Restore ambient light
        }
        else
        {
            GLfloat qaNoAmbient[] = {0.0, 0.0, 0.0, 1.0};
            glLightfv(GL_LIGHT0, GL_AMBIENT, qaNoAmbient); // Set ambient light to zero
        }
        ambientEnabled = !ambientEnabled;
        break;

    // Reset
    case '0': // Reset figure
        rotation_angle_x = 0.0;
        rotation_angle_y = 45.0;
        rotation_angle_z = 0.0;
        translation_x = 0.0, translation_y = 0.0, translation_z = -800.0;
        scale_factor = 1.0;
        break;

    // Exit
    case 27:
        exit(0);
        break; // ESC key to exit
    }
    cout << "Object Position: (" << translation_x << ", " << translation_y << ", " << translation_z << ")"
         << " Scale: " << scale_factor << endl;

    glutPostRedisplay(); // Redraw scene
}

void loadObj(const string &fname)
{
    ifstream file(fname);
    if (!file.is_open())
    {
        cout << "File not found";
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
            else if (type == "vn")
            {
                float nx, ny, nz;
                file >> nx >> ny >> nz;
                normals.push_back({nx, ny, nz});
            }
            else if (type == "vt")
            {
                float u, v;
                file >> u >> v;
                textures.push_back({u, v});
            }
            else if (type == "f")
            {
                string v1, v2, v3;
                file >> v1 >> v2 >> v3;

                vector<int> indices1;
                indices1.reserve(3); // Reserve space for 6 indices (2 sets of vertex indices)

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

                texture_faces.push_back(indices1);

                vector<int> indices2;
                indices2.reserve(3); // Reserve space for 6 indices (2 sets of vertex indices)

                // Extract the second set of vertex indices
                vf1 = v1.substr(v1.find_last_of('/') + 1);
                vf2 = v2.substr(v2.find_last_of('/') + 1);
                vf3 = v3.substr(v3.find_last_of('/') + 1);

                indices2.push_back(stoi(vf1) - 1);
                indices2.push_back(stoi(vf2) - 1);
                indices2.push_back(stoi(vf3) - 1);

                normal_faces.push_back(indices2);
            }
        }
    }
    file.close();

    cout << "Vertices: " << vertices.size() << endl;
    cout << "Faces: " << faces.size() << endl;
    cout << "Normals: " << normals.size() << endl;
    cout << "Textures: " << textures.size() << endl;
    cout << "Texture Faces: " << texture_faces.size() << endl;
    cout << "Normal Faces: " << normal_faces.size() << endl;
}

void renderObj()
{
    glClear(GL_COLOR_BUFFER_BIT);
    object = glGenLists(1);
    glNewList(object, GL_COMPILE);
    glPushMatrix();

    GLfloat green[] = {0.0, 1.0, 0.0, 1.0};
    glMaterialfv(GL_FRONT, GL_SPECULAR, green);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, green);
    glMaterialf(GL_FRONT, GL_SHININESS, 60);

    glBegin(GL_TRIANGLES);
    for (size_t i = 0; i < texture_faces.size(); ++i)
    {
        const auto &face = texture_faces[i];
        for (int j = 0; j < 3; ++j)
        {
            int vertex_index = face[j];
            int normal_index = normal_faces[i][j];
            if (vertex_index < vertices.size())
            {
                glNormal3f(normals[normal_index][0], normals[normal_index][1], normals[normal_index][2]);
                glVertex3f(vertices[vertex_index][0], vertices[vertex_index][1], vertices[vertex_index][2]);
            }
            else
            {
                cout << vertex_index << " out of range" << vertices.size() << endl;
            }
        }
        // Set the normal for the whole face
        
        
    }
    glEnd();

    glEnd();

    glEnd();

    glPopMatrix();
    glEndList();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
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
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("Load OBJ");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutTimerFunc(10, timer, 0);
    loadObj(argv[1]);
    renderObj();
    initLight();
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
