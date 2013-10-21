/*  Author:  Jeffrey Thomas Shepherd
	Date:    09/26/2013
    File:	 functions.h

    This file contains the function prototypes used in Bounce.  */

#include <gl\glut.h>

void RenderScene(void);
void TimerFunction(int value);
void SetupRC(void);
void ChangeSize(GLsizei width, GLsizei height);
void Key(unsigned char keystrokeValue, int x, int y);
void Mouse(int buttonValue, int buttonState, int xCoordinate, int yCoordinate);
