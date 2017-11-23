// Para compilar en MacOSX
// g++ -o practica01 practica01.cpp -framework OpenGL -framework GLUT

#include <stdlib.h>
#include <stdio.h>
#include <bits/stdc++.h>
#ifdef __APPLE__
#include "GLUT/glut.h"
#else
#include "GL/glut.h"
#endif

#define NUMVTX (10)

static int winwidth,winheight;
static int mx,my;
static int flag=0;
static float rotx=0.0f, roty=0.0f;

GLfloat c[3]={0.22,0.27,0.59};

void cop (GLfloat a[3], GLfloat *b)
{
    a[0] = b[0];
    a[1] = b[1];
    a[2] = b[2];
}

class cube
{
public:
    GLfloat coordinates[24][3];
    GLfloat normals[24][3];

    cube(GLfloat a[3], GLfloat b[3], bool incl)
    {
        cop(coordinates[0], a); cop(coordinates[1], a);
        cop(coordinates[2], a); cop(coordinates[3], a);

        coordinates[0][2] = coordinates[1][2] = a[2] + 0.1;
        coordinates[2][2] = coordinates[3][2] = a[2] - 0.1;
        if(incl == false)
        {
            coordinates[0][0] = coordinates[2][0] = a[0] - 0.1;
            coordinates[1][0] = coordinates[3][0] = a[0] + 0.1;
            cop(normals[0], new GLfloat[3]{0.0f, 1.0f, 0.0f});
            cop(normals[1], new GLfloat[3]{0.0f, 1.0f, 0.0f});
            cop(normals[2], new GLfloat[3]{0.0f, 1.0f, 0.0f});
            cop(normals[3], new GLfloat[3]{0.0f, 1.0f, 0.0f});
        }
        else
        {
            coordinates[0][1] = coordinates[2][1] = a[1] - 0.1;
            coordinates[1][1] = coordinates[3][1] = a[1] + 0.1;
            cop(normals[0], new GLfloat[3]{-1.0f, 0.0f, 0.0f});
            cop(normals[1], new GLfloat[3]{-1.0f, 0.0f, 0.0f});
            cop(normals[2], new GLfloat[3]{-1.0f, 0.0f, 0.0f});
            cop(normals[3], new GLfloat[3]{-1.0f, 0.0f, 0.0f});
        }
        cop(coordinates[4], b); cop(coordinates[5], b);
        cop(coordinates[6], b); cop(coordinates[7], b);

        coordinates[4][2] = coordinates[5][2] = b[2] - 0.1;
        coordinates[6][2] = coordinates[7][2] = b[2] + 0.1;
        if(incl == 0)
        {
            coordinates[4][0] = coordinates[6][0] = b[0] - 0.1;
            coordinates[5][0] = coordinates[7][0] = b[0] + 0.1;
            cop(normals[4], new GLfloat[3]{0.0f, -1.0f, 0.0f});
            cop(normals[5], new GLfloat[3]{0.0f, -1.0f, 0.0f});
            cop(normals[6], new GLfloat[3]{0.0f, -1.0f, 0.0f});
            cop(normals[7], new GLfloat[3]{0.0f, -1.0f, 0.0f});
        }
        else
        {
            coordinates[4][1] = coordinates[6][1] = b[1] - 0.1;
            coordinates[5][1] = coordinates[7][1] = b[1] + 0.1;
            cop(normals[4], new GLfloat[3]{1.0f, 0.0f, 0.0f});
            cop(normals[5], new GLfloat[3]{1.0f, 0.0f, 0.0f});
            cop(normals[6], new GLfloat[3]{1.0f, 0.0f, 0.0f});
            cop(normals[7], new GLfloat[3]{1.0f, 0.0f, 0.0f});
        }
        cop(coordinates[8], coordinates [0]); cop(coordinates[9], coordinates [1]);
        cop(coordinates[10], coordinates [6]); cop(coordinates[11], coordinates [7]);
        cop(normals[8], new GLfloat[3]{0.0f, 0.0f, 1.0f});
        cop(normals[9], new GLfloat[3]{0.0f, 0.0f, 1.0f});
        cop(normals[10], new GLfloat[3]{0.0f, 0.0f, 1.0f});
        cop(normals[11], new GLfloat[3]{0.0f, 0.0f, 1.0f});
        cop(coordinates[12], coordinates [2]); cop(coordinates[13], coordinates [3]);
        cop(coordinates[14], coordinates [4]); cop(coordinates[15], coordinates [5]);
        cop(normals[12], new GLfloat[3]{0.0f, 0.0f, -1.0f});
        cop(normals[13], new GLfloat[3]{0.0f, 0.0f, -1.0f});
        cop(normals[14], new GLfloat[3]{0.0f, 0.0f, -1.0f});
        cop(normals[15], new GLfloat[3]{0.0f, 0.0f, -1.0f});
        cop(coordinates[16], coordinates [0]); cop(coordinates[17], coordinates [2]);
        cop(coordinates[18], coordinates [6]); cop(coordinates[19], coordinates [4]);
        cop(coordinates[20], coordinates [1]); cop(coordinates[21], coordinates [3]);
        cop(coordinates[22], coordinates [7]); cop(coordinates[23], coordinates [5]);

        if(incl == 0)
        {
            cop(normals[16], new GLfloat[3]{-1.0f, 0.0f, 0.0f});
            cop(normals[17], new GLfloat[3]{-1.0f, 0.0f, 0.0f});
            cop(normals[18], new GLfloat[3]{-1.0f, 0.0f, 0.0f});
            cop(normals[19], new GLfloat[3]{-1.0f, 0.0f, 0.0f});
            cop(normals[20], new GLfloat[3]{1.0f, 0.0f, 0.0f});
            cop(normals[21], new GLfloat[3]{1.0f, 0.0f, 0.0f});
            cop(normals[22], new GLfloat[3]{1.0f, 0.0f, 0.0f});
            cop(normals[23], new GLfloat[3]{1.0f, 0.0f, 0.0f});
        }
        else
        {
            cop(normals[16], new GLfloat[3]{0.0f, -1.0f, 0.0f});
            cop(normals[17], new GLfloat[3]{0.0f, -1.0f, 0.0f});
            cop(normals[18], new GLfloat[3]{0.0f, -1.0f, 0.0f});
            cop(normals[19], new GLfloat[3]{0.0f, -1.0f, 0.0f});
            cop(normals[20], new GLfloat[3]{0.0f, 1.0f, 0.0f});
            cop(normals[21], new GLfloat[3]{0.0f, 1.0f, 0.0f});
            cop(normals[22], new GLfloat[3]{0.0f, 1.0f, 0.0f});
            cop(normals[23], new GLfloat[3]{0.0f, 1.0f, 0.0f});
        }
    }
    void render()
    {
        int i = 0;
        for(int j = 0; j < 6; j++)
        {
            glBegin(GL_QUAD_STRIP);
            for (int k = 0; k < 4; k++)
            {
                glColor3fv(c);
                glNormal3fv(normals[i]);
                glVertex3fv(coordinates[i]);
                i++;
            }
            glEnd();
        }
    }
};

class letter
{
public:
    std::vector<cube> body;
    int size;
    letter(int size)
    {
        this->size = size - 1;
    }
    void setCoordinates(GLfloat v[][3], bool pos[])
    {
        cube *a = NULL;
        for(int i = 0; i < size; i++)
        {
            if((pos[i] == false && v[i][1] < v[i+1][1]) || (pos[i] == true && v[i][0] > v[i+1][0]))
            {
                a = new cube(v[i + 1], v[i], pos[i]);
            }
            else
            {
                a = new cube(v[i], v[i + 1], pos[i]);
            }
            body.push_back(*a);
        }
    }
    void render(float pos)
    {
        glTranslatef(pos, 0.0f, 0.0f);
        for (int i = 0; i < size; i++)
    	{
    		body[i].render();
    	}
    }
};
GLfloat Gv[6][3]={{1,1,0.5}, {-1,1,0.5}, {-1,-1,0.5}, {1,-1,0.5}, {1,0,0.5}, {0,0,0.5}};
GLfloat Wv[5][3]={{-1,1,0.5}, {-0.25,-1,0.5}, {0,0,0.5}, {0.25,-1,0.5}, {1,1,0.5}};
GLfloat Vv[3][3]={{-1,1,0.5}, {0,-1,0.5}, {1,1,0.5}};
GLfloat Av[5][3]={{-1,-1,0.5}, {0,1,0.5}, {1,-1,0.5}, {0.5,0,0.5}, {-0.5,0,0.5}};

letter G(6), W(5), V(3), A(5);
const GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 2.0f, 3.0f, 1.0f };

const GLfloat mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat mat_diffuse[] = { 0.0f, 1.0f, 0.0f, 1.0f };

//GLfloat global_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };

void init()
{
    bool g[5] = {true, false, true, false, true};
    bool w[4] = {false, false, false, false};
    bool v[2] = {false, false};
    bool a[4] = {false, false, false, true};
    G.setCoordinates(Gv, g);
    W.setCoordinates(Wv, w);
    V.setCoordinates(Vv, v);
    A.setCoordinates(Av, a);
}
void drawgraphix()
{
	int i;
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glPushMatrix();

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHT0);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

	glTranslatef(0.0f,0.0f,-3.0f);
	glRotatef(rotx,0.0f,1.0f,0.0f);
	glRotatef(roty,1.0f,0.0f,0.0f);
    G.render(-3);
    W.render(2);
    V.render(2);
    A.render(2);
	glPopMatrix();
	glutSwapBuffers();
}

void reshapefunc(int width,int height)
{
	winwidth=width;
	winheight=height;

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);

	glViewport(0,0,width,height);

	glMatrixMode(GL_PROJECTION);
    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
	glLoadIdentity();
	gluPerspective(90.0,(float)width/height,1.0,10.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0f,0.0f,3.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f);

}

void mousefunc(int button,int state,int x,int y)
{
	if (button == GLUT_LEFT_BUTTON)
    {
		if (state == GLUT_DOWN)
        {
			flag = 1;
		} else {
			flag=0;
		}
	}
}

void motionfunc(int x,int y)
{
	if (flag>0) {
		if (flag>1) {
			rotx += 360.0f * (x - mx) / winwidth;
			roty += 360.0f * (y - my) / winheight;
		}

		mx = x;
		my = y;
		//drawgraphix();

		flag = 2;
	}
}

void keyboardfunc(unsigned char key,int x,int y)
{
	if (key=='q' || key==27) exit(0);
}


void idlefunc()
{
	glutPostRedisplay();
}

int main(int argc,char **argv)
{
   winwidth=winheight=512;
   init();
   glutInit(&argc,argv);
   glutInitWindowSize(winwidth,winheight);
   glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
   glutCreateWindow("Practica 1 - Ejercicio 1.1");

   glutDisplayFunc(drawgraphix);
   glutReshapeFunc(reshapefunc);
   glutMouseFunc(mousefunc);
   glutMotionFunc(motionfunc);
   glutKeyboardFunc(keyboardfunc);
   glutIdleFunc(idlefunc);

   glutMainLoop();

   return(0);
}
