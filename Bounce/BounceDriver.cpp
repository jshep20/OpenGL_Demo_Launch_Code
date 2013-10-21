/*  Author:  Jeffrey Thomas Shepherd
	Date:    09/26/2013
    File:	 BounceDriver.cpp

    This is the first in a series of openGL programs that I have authored.  */

#include <windows.h>
#include <gl/glut.h>
#include "functions.h"

//  Global variables

//  Initial square x and y coordinates and square size

GLfloat x1 = 50.0f;
GLfloat y1 = 100.0f;
GLsizei rsize = 25;	

//  Step size in x and y directions
//  (number of pixels to move each time)

GLfloat xStep = 1.0f;
GLfloat yStep = 1.0f;

//  Keep track of windows changing width and height

GLfloat windowWidth;
GLfloat windowHeight;

//  Mouse variables

float c, s;

//  Keyboard variables

float kc, kvh, kvw, kv = 1;

//  Pragma to eliminate console window

#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

//  Main program entry point

void main(void)
{
	//  Use double buffering and set component colors

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	//  Titel bar text

	glutCreateWindow("Jeffrey Thomas Shepherd, OpenGL Demo 1");

	//  Callback functions

	glutDisplayFunc(RenderScene);			//  Draws the scene
	glutReshapeFunc(ChangeSize);			//  Changes the window size
	glutTimerFunc(33, TimerFunction, 1);	//  The timer function is called every 33 milliseconds
	glutKeyboardFunc(Key);					//  Capture keystroke
    glutMouseFunc(Mouse);					//  Capture mouse button activity

	//  Set the color of the window background

	SetupRC();

	/*  The following line starts the OpenGL program running and IS ALWAYS THE LAST LINE in main  */

	glutMainLoop();
}


