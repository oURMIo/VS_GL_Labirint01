// glut1.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "GL/glut.h"
#include <stdio.h>

const int windowW = 600;  // -
const int windowH = 800;  // |

const int w = 60, h = 60;
const int N = 9, M = 9;
int m[M][N] = 
{
0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 1, 1, 1, 1, 1, 1, 1, 0,
0, 1, 1, 1, 1, 1, 1, 1, 0,
0, 1, 1, 1, 1, 1, 1, 1, 0,
0, 1, 1, 1, 1, 1, 1, 1, 0,
0, 1, 1, 1, 1, 1, 1, 1, 0,
0, 1, 1, 1, 1, 1, 1, 1, 0,
0, 1, 1, 1, 1, 1, 1, 1, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0,
};

int myX = w*2 + w/2, myY = h * 2 + h/2;

void display()  /// Отрисовка кадра
{
	glClear(GL_COLOR_BUFFER_BIT); // очистка экрана

	for (int i=0; i<M; i++)
		for (int j=0; j<N; j++)
		{
			if (m[i][j] == 1) 			glColor3f(1.0, 1.0, 0.0);
			else if (m[i][j] == 0) 			glColor3f(1.0, 0.0, 0.0);
			else if (m[i][j] == 2) 			glColor3f(1.0, 0.0, 1.0);
			glBegin(GL_POLYGON);
			glVertex3f(i * w,       j * h, 0);
			glVertex3f(i * w + w-2, j * h, 0);
			glVertex3f(i * w + w-2, j * h + h-2, 0);
			glVertex3f(i * w,       j * h + h-2, 0);
			glEnd();
		} 

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(myX - 10, myY - 10, 0.0);
	glVertex3f(myX - 10, myY + 10, 0.0);
	glVertex3f(myX + 10, myY + 10, 0.0);
	glVertex3f(myX + 10, myY - 10, 0.0);
	glEnd();

	glFlush();
	glFinish();
} 

void reshape(int x, int y)
{
	glViewport(0, 0, x, y);
	// "Обнулить" матрицы пересчёта координат
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Установить свою систему координат opengl
	glOrtho(0.0, windowW, 0.0, windowH, -1.0, 1.0);
}

void mouseClick(int button, int state, int x, int y)
{
	if (GLUT_LEFT_BUTTON == button)
	{
;		
	}
}

//void keyboard(unsigned char key, int x, int y)
void keyboard(int key, int x, int y)                  //ДВМЖЕНИЕ
{
	if (GLUT_KEY_LEFT == key) if (m[myY / w][(myX / h) - 1] == 1)  myX -= w ;
	if (GLUT_KEY_RIGHT == key) if (m[myY / w][(myX / h) + 1] == 1)  myX += w;
	if (GLUT_KEY_DOWN == key) if (m[myY / w][(myX / h) - 1] == 1) myY -= h;
	if (GLUT_KEY_UP == key) if (m[myY / w][(myX / h) + 1] == 1) myY += h;
}

void readPole()
{
	FILE *fp;
	fopen_s(&fp, "labirint.txt", "rt");

	for (int j = 0; j<N; j++)
		for (int i = 0; i<M; i++)
			if (!feof(fp))
			{
				fscanf(fp, "%d", &m[i][j]);
			}
	fclose(fp);
}


int _tmain(int argc, _TCHAR* argv[])
{
	glutInit(&argc, (char**)argv);

	readPole();

    glutInitWindowSize(windowW, windowH);
    glutInitWindowPosition(100, 100);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_ALPHA | GLUT_DEPTH);
    glutCreateWindow("Dima");

    glClearColor(0, 0, 0.2, 0);
    glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouseClick);
	//glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboard);


    glutMainLoop();
    return 0;
}

