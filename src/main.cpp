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

float rot_ele;
float cameraPosX = 0.0f;
float cameraPosY = 0.0f;
float cameraPosZ = 150.0f;


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

    elephant = glGenLists(1);
    glNewList(elephant, GL_COMPILE);
    {
        glBegin(GL_TRIANGLES);

        for(int i = 0; i < faces.size(); i++)
        {
            vector<int> face = faces[i];
            vector<int> texture_face = texture_faces[i];
            vector<int> normal_face = normal_faces[i];

            for (int j = 0; j < 3; j++)
            {
                // Set normal
                if (normal_face[j] >= 0)
                {
                    glNormal3f(normals[normal_face[j]][0], normals[normal_face[j]][1], normals[normal_face[j]][2]);
                }

                // Set texture coordinate
                if (texture_face[j] >= 0)
                {
                    glTexCoord2f(textures[texture_face[j]][0], textures[texture_face[j]][1]);
                }

                // Set vertex
                glVertex3f(vertices[face[j]][0], vertices[face[j]][1], vertices[face[j]][2]);
            }
        }

        glEnd();
    }
    glEndList();

    file.close();

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
    glTranslatef(0, -40.00, -105);
    glColor3f(1.0, 0.23, 0.27);
    glScalef(0.4, 0.4, 0.4);
    glRotatef(rot_ele, 0, 1, 0);
    glCallList(elephant);
    glPopMatrix();
    rot_ele = rot_ele + 0.6;
    if (rot_ele > 360) rot_ele = rot_ele - 360;
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
    glutInitWindowSize(800, 450);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("Load OBJ");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutTimerFunc(10, timer, 0);
    loadObj(argv[1]);

    glutMainLoop();
    return 0;
}
