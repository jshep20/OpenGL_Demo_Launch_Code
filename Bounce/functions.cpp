/*  /*  Author:  Jeffrey Thomas Shepherd
	Date:    09/26/2013
    File:	 functions.h

    This file contains the functions used in Bounce.  */

#include <string.h>
#include "functions.h"

extern GLfloat x1, y1, xStep, yStep, windowWidth, windowHeight;
extern GLsizei rsize;
extern float c, s, kc, kv, kvh, kvw;

/*  Function Name:  RenderScene  
	Purpose:		Called to draw scene.  */

void RenderScene(void)
{
	//  Clear the window with current clearing color

	glClear(GL_COLOR_BUFFER_BIT);

	//  Set rectangle color

	glColor3f(0.2f, 0.7f, 0.3f);

	//  Draw a rectangle

	glRectf(-100, 100, 100, -100);

	//  Set drawing color according to current mouse click

	if(c == 0)
		glColor3f(1.0f, 0.0f, 0.0f);
	else if(c == 1)
		glColor3f(0.0f, 1.0f, 0.0f);
	else if(c == 2)
		glColor3f(0.0f, 0.0f, 1.0f);

	//  Draw a filled rectangle with current color

	glRectf(x1, y1, x1 + rsize, y1 + rsize);

	//  Draw a wire teapot

	glutWireTeapot(50);

	//  Draw in black

	glColor3f(0.0f, 0.0f, 0.0f);

	glBegin(GL_LINES);

	//  Draw x and y axis

	glVertex3f(-200, 0, 0);
	glVertex3f(200, 0, 0);
	glVertex3f(0, -200, 0);
	glVertex3f(0, 200, 0);

	//  Draw tick marks on axes

	for(int i = 0; i < 399; i = i + 25)
	{
		glVertex3f(-200 + i, -5, 0);
		glVertex3f(-200 + i, 5, 0);
	}

	glEnd();

	//  Flush drawing commands

	glutSwapBuffers();

}


/*  Function Name:  TimerFunction  
	Purpose:		Called by GLUT library when idle (window not being resized or moved.)  */

void TimerFunction(int value)
{

	//  Reverse direction when left or right edge is reached

	if((x1 > (windowWidth - rsize)) || (x1 < -99))
		xStep = -xStep;

    //  Reverse direction when top or bottom edge is reached

	if((y1 > (windowHeight - rsize)) || (y1 < -99))
		yStep = -yStep;

	/*  Check bounds.  This is in case the window is made smaller and the rectangle is outside
		the new clipping volume.  */

	if((x1 > (windowWidth - rsize))) 
		x1 = windowWidth - rsize - 1;

	
	if((y1 > (windowHeight - rsize))) 
		y1 = windowHeight - rsize - 1;

	//  Actually move the square

	if(s < 2)
	{
		x1 += xStep;
		y1 += yStep;
	}

	//  Reset coordinate system

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//  Set clipping volume according to key

	if(kc == 0)
		glOrtho(-100.0f, 100.0f, -100.0f, 100.0f, 1.0f, -1.0f);
	else if(kc == 1)
		glOrtho(-200.0f, 200.0f, -200.0f, 200.0f, 1.0f, -1.0f);
	else if(kc == 2)
		glOrtho(-50.0f, 50.0f, -50.0f, 50.0f, 1.0f, -1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//  Redraw scene with the new coordinates

	glutPostRedisplay();
	glutTimerFunc(33 / (s + 1), TimerFunction, 1);	//  s is a delay factor
}

/*  Function Name:  SetupRC  
	Purpose:		Sets up the rendering state.  */

void SetupRC(void)
{
	//  Set clear color to blue

	glClearColor(0.5f, 0.8f, 0.2f, 1.0f);
}


/*  Function Name:  ChangeSize  
	Purpose:		Called by the GLUT library when the window has changed size.  */

void ChangeSize(GLsizei width, GLsizei height)
{
	//  reset viewport and clip

	kv = 1;
	kc = 0;

	//  prevent divide by zero

	if(height == 0)
		height = 1;

	//  Set Viewport to window dimensions

	glViewport(0, 0, width, height);

	kvw = width;
	kvh = height;

	/*  Keep the square, square; this time, save calculated width and height for later use.  */

	if(width <= height)
	{
		windowHeight = 100.0f * height / width;
		windowWidth = 100.0f;
	}
	else
	{
		windowWidth = 100.0f * height / width;
		windowHeight = 100.0f;
	}

	//  Reset coordinate system.

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-100.0f, windowWidth, -100.0f, windowHeight, 1.0f, -1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/*  Function Name:  Key  
	Purpose:		*/

void Key(unsigned char keystrokeValue, int x, int y)
{
	//  c key changes kc value changes clip

	if(keystrokeValue == 'c')
	{
		if(kc < 2)
			kc++;
		else 
			kc = 0;
	}

	//  v key changes kv value changes viewport

	else if(keystrokeValue == 'v')
	{
		if(kv < 1)
		{
			kv = 1;
			glViewport(0, 0, kvw * kv, kvh * kv);
		}
		else
		{
			kv = 0.5;
			glViewport(kvw / 4, kvh / 4, kvw * kv, kvh * kv);
		}
	}
}

/*  Function Name:  Mouse  
	Purpose:		*/

void Mouse(int buttonValue, int buttonState, int xCoordinate, int yCoordinate)
{
	//  Left mouse click changes c value changes color
	
	if(buttonValue == GLUT_LEFT_BUTTON && buttonState == GLUT_DOWN)
	{
		if(c < 2)
			c++;
		else
			c = 0;
	}
	else if(buttonValue == GLUT_RIGHT_BUTTON && buttonState == GLUT_DOWN)
	{
		if(s < 2)
			s++;
		else
			s = 0;
	}
}


	
