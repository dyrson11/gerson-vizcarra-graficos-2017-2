#define GLEW_STATIC
#include <bits/stdc++.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include "headers/shader.hpp"
#include "headers/variables.h"
#include "headers/genCube.h"
#include "headers/genLetter.h"
using namespace std;

void reshapefunc(int width,int height)
{
	winwidth=width;
	winheight=height;

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glViewport(0,0,width,height);

}
void init (void)
{
    letter G(6), W(5), V(3), A(5), X(2);
    G.setCoordinates(Gv, g);
    W.setCoordinates(Wv, w);
    V.setCoordinates(Vv, v);
    A.setCoordinates(Av, a);

	glClearColor (0, 0, 0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBN);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * g_vertex_buffer_data.size(), g_vertex_buffer_data.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBN);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * normals.size(), normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(2);

    cout<<normals.size();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);

    shader = LoadShaders("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");
    glUseProgram(shader);
    glUniform3f(glGetUniformLocation(shader, "objectColor"), 0.5f, 0.3f, 1.0f);
    glUniform3f(glGetUniformLocation(shader, "lightColor"), 1.0f, 1.0f, 1.0f);
    glUniform3f(glGetUniformLocation(shader, "lightPos"), 4.0f, 4.0f, 6.0f);
    glUniform3f(glGetUniformLocation(shader, "viewPos"), -2.0f, -2.0f, -3.0f);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

void display (void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindVertexArray(VAO);
    glDrawElements( GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
    glutSwapBuffers();
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
	if (flag>0)
    {
		if (flag>1)
        {
			rotx += 10.0f * (x - mx) / winwidth;
			roty += 10.0f * (y - my) / winheight;
		}

		mx = x;
		my = y;

		flag = 2;
        glUseProgram(shader);
        const GLfloat attrib[] = { -roty, -rotx };
        glVertexAttrib2fv(1, attrib);
        //display();
	}
}

/*Main*/
int main (int argc,char** argv)
{
    winwidth=winheight=512;

    glutInit(&argc,argv);
    glutInitWindowSize(winwidth,winheight);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutCreateWindow("Practica 1 - Ejercicio 1.1");

    if ( glewInit() != GLEW_OK )
    {
        return -1;
    }

    init();
	glutDisplayFunc(display);
    glutReshapeFunc(reshapefunc);
    glutMouseFunc(mousefunc);
    glutMotionFunc(motionfunc);
    glutIdleFunc(display);
	glutMainLoop();
}
