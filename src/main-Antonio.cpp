#include <iostream>
#include <fstream>
#include <vector>
#include <GL/freeglut.h>
#include <string>
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
float rotation_angle_y = 0.0;
float rotation_angle_z = 0.0;
float translation_x = 0.0, translation_y = 0, translation_z = -800.0;
float scale_factor = 1.0;
float position_z_offset = 0.0; // Added variable
GLfloat light0_position[] = { 0.0, 0.0, 0.0, 1.0 }; // Define and initialize light position

void initAmbientLight(GLfloat light_position_x, GLfloat light_position_y, GLfloat light_position_z) {
    glDisable(GL_LIGHTING); // Disable lighting before configuring the new light
    glDisable(GL_LIGHT0); // Disable previous light
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Configure the ambient component of the light
    GLfloat light0_ambient[] = { 1.0, 0.0, 0.0, 1.0 }; // Ambient light color (red)
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);

    // Set the position of the light
    GLfloat light0_position[] = { light_position_x, light_position_y, light_position_z, 1.0 }; // Light position
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
}

void initDiffuseLight(GLfloat light_position_x, GLfloat light_position_y, GLfloat light_position_z) {
    glDisable(GL_LIGHTING); // Disable lighting before configuring the new light
    glDisable(GL_LIGHT0); // Disable previous light
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Configure the diffuse component of the light
    GLfloat light0_diffuse[] = { 0.0, 0.0, 1.0, 1.0 }; // Diffuse light color (blue)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);

    // Set the position of the light
    GLfloat light0_position[] = { light_position_x, light_position_y, light_position_z, 1.0 }; // Light position
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
}

void initSpecularLight(GLfloat light_position_x, GLfloat light_position_y, GLfloat light_position_z) {
    glDisable(GL_LIGHTING); // Disable lighting before configuring the new light
    glDisable(GL_LIGHT0); // Disable previous light
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Configure the specular component of the light
    GLfloat light0_specular[] = { 1.0, 1.0, 0.0, 1.0 }; // Specular light color (yellow)
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);

    // Set the position of the light
    GLfloat light0_position[] = { light_position_x, light_position_y, light_position_z, 1.0 }; // Light position
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
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
        case '1': // Initialize ambient light
            initAmbientLight(1.0, 2.0, 3.0);
            cout << "Ambient light enabled" << endl;
            break;
        case '2': // Initialize diffuse light
            initDiffuseLight(-1.0, 0.0, 2.0);
            cout << "Diffuse light enabled" << endl;
            break;
        case '3': // Initialize specular light
            initSpecularLight(0.0, -2.0, -3.0);
            cout << "Specular light enabled" << endl;
            break;
        case '0': // Move light source farther
            rotation_angle_x = 0.0;
            rotation_angle_y = 45.0;
            rotation_angle_z = 0.0;
            translation_x = 0.0, translation_y = -300.0, translation_z = -800.0;
            scale_factor = 1.0;
            cout << "Resert figure" << endl;
            break;
        case 27: // ESC key to exit
            exit(0);
            break;
    }
    cout << "Object Position: (" << translation_x << ", " << translation_y << ", " << translation_z << ")" << " Scale: " << scale_factor << endl;

    glutPostRedisplay(); // Redraw scene
}

void drawBackground() {
    glPushMatrix();
    glLoadIdentity();
    glDisable(GL_LIGHTING); // Disable lighting for the background
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.5, 1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glEnd();
    glPopMatrix();
}

void loadObj(const string& fname) {
    ifstream file(fname);
    if (!file.is_open()) {
        cout << "File not found";
        exit(1);
    } else {
        string type;
        while (file >> type) {
            if (type == "v") {
                float x, y, z;
                file >> x >> y >> z;
                vertices.push_back({x, y, z});
            } else if (type == "vn") {
                float nx, ny, nz;
                file >> nx >> ny >> nz;
                normals.push_back({nx, ny, nz});
            } else if (type == "vt") {
                float u, v;
                file >> u >> v;
                textures.push_back({u, v});
            } else if (type == "f") {
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

void renderObj() {
    object = glGenLists(1);
    glNewList(object, GL_COMPILE);
    glPushMatrix();

    GLfloat cor_verde[] = { 0.0, 1.0, 0.0, 1.0 };
    GLfloat cor_branco[] = { 1.0, 1.0, 1.0, 1.0 };

    glMaterialfv(GL_FRONT, GL_DIFFUSE, cor_verde);
    glMaterialfv(GL_FRONT, GL_SPECULAR, cor_branco);
    glMaterialf(GL_FRONT, GL_SHININESS, 60);

    glBegin(GL_TRIANGLES);
    for (const auto& face : faces) {
        for (int i = 0; i < 3; ++i) {
            int vertex_index = face[i];
            if (vertex_index >= 0 && vertex_index < vertices.size()) {
                glVertex3f(vertices[vertex_index][0], vertices[vertex_index][1], vertices[vertex_index][2] + position_z_offset);
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

    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

    // Draw the object
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
    glutCreateWindow("Load OBJ");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutTimerFunc(10, timer, 0);
    loadObj(argv[1]);
    glutKeyboardFunc(keyboard);
    renderObj();

    glutMainLoop();
    return 0;
}
