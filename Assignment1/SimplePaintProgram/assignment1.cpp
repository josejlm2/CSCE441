// OpenGLAssignment1.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <gl/glut.h>
#include <gl/gl.h>
#include <math.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

//GLOBAL VARIABLES
float SIZE =1;
bool QUAD = true;
bool TRIANGLE = false;
bool LINE = false;
bool CIRCLE = false;

void display ( void )
{
	glClear ( GL_COLOR_BUFFER_BIT );
	glFlush ( );//make sure everything is drawn
}

void brushSelection()
{
	if (QUAD == true)
	{
		QUAD = false;
		TRIANGLE = true;
	}
	else if (TRIANGLE == true)
	{
		TRIANGLE = false;
		LINE = true;
	}
	else if (LINE == true)
	{
		LINE = false;
		CIRCLE = true;
	}
	else if (CIRCLE == true)
	{
		CIRCLE = false;
		QUAD = true;
	}
}

void triangle(int x, int y)
{
	glBegin(GL_TRIANGLES);
		glVertex2f(x-(2*SIZE),y-(2*SIZE));
		glVertex2f(x+(2*SIZE),y-(2*SIZE));
		glVertex2f(x,y+(2*SIZE));
	glEnd();
	glFlush ( );
}

void line(int x, int y)
{
	glBegin(GL_LINES);
		glVertex2f(x,y-(2*SIZE));
		glVertex2f(x,y+(2*SIZE));
	glEnd();
	glFlush ( );
}

//draw a quadrilateral
void quad(int x, int y)
{
	//glColor3f ( 1, 0, 0 );
	
	glBegin ( GL_QUADS );
		glVertex2f ( x-(2*SIZE), y+(2*SIZE));
		glVertex2f ( x-(2*SIZE), y-(2*SIZE));
		glVertex2f ( x+(2*SIZE), y-(2*SIZE));
		glVertex2f ( x+(2*SIZE), y+(2*SIZE));
	glEnd ( );
	/*
	glPushMatrix();
		glBegin ( GL_QUADS );
			glVertex2f ( 0-(2*SIZE), 0+(2*SIZE));
			glVertex2f ( 0-(2*SIZE), 0-(2*SIZE));
			glVertex2f ( 0+(2*SIZE), 0-(2*SIZE));
			glVertex2f ( 0+(2*SIZE), 0+(2*SIZE));
		glEnd ( );
	*/

	glPopMatrix();
	//float tempX = x;
	//float tempY = y;
	glFlush ( );
}

void circle(int x, int y)
{
	glBegin(GL_POLYGON);
		for (int i=0; i<=360;i++)
		{
			float temp = i; 
			glVertex2f((2*SIZE)*cos(temp)+x,(2*SIZE)*sin(temp)+y);
		}
	glEnd();
	glFlush();
}


//accept keyboard input
void keyboard ( unsigned char key, int x, int y )
{
	switch ( key )
	{
		//TOOLSs
		case 'b':
			brushSelection();
			break;
		case 'c':
			glutPostRedisplay ( );
			break;
		case 'r':
			
			break;
		case 'a':
			break;


		//RESIZE BRUSH
		case '+':
			if (SIZE != 128)
			{
				SIZE = SIZE*2;
			}
			
			break;
		case '-':
			if (SIZE != 1)
			{
				SIZE = SIZE*.5;
			}
			break;


		//COLORS
		case '1':
			glColor3f ( 1, 0, 0 );//red
			break;
		case '2':
			glColor3f ( 0, 1, 0 );//green
			break;
		case '3':
			glColor3f ( 1, 1, 0 );//blue
			break;
		case '4':
			glColor3f ( 0, 0, 1 );//yellow
			break;
		case '5':
			glColor3f ( 1, 0, 1 );//pink
			break;
		case '6':
			glColor3f ( 0, 1, 1 );//cyan
			break;
		case '7':
			glColor3f ( 1, 1, 1 );//white
			break;


		default:
			break;
	}
}

//initalize
void init ( void )
{
	printf( "OpenGL version: %s\n", (char*)glGetString(GL_VERSION));
    printf( "OpenGL renderer: %s\n", (char*)glGetString(GL_RENDERER));
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, WINDOW_WIDTH-1, WINDOW_HEIGHT-1, 0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_BLEND); // needed for circle blend effect
}

void mouseMove ( int x, int y )
{
	if (QUAD == true)
	{
		quad(x,y);
	}
	else if (TRIANGLE == true)
	{
		triangle(x,y);
	}
	else if (LINE == true)
	{
		line(x,y);
	}
	else if (CIRCLE == true)
	{
		circle(x,y);
	}
}

void mouseClick(int button, int state, int x, int y)
{
	if (QUAD == true)
	{
		quad(x,y);
	}
	else if (TRIANGLE == true)
	{
		triangle(x,y);
	}
	else if (LINE == true)
	{
		line(x,y);
	}
	else if (CIRCLE == true)
	{
		circle(x,y);
	}
}

int main ( int argc, char *argv[] )
{
	glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (WINDOW_WIDTH, WINDOW_HEIGHT); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Jose Manriquez - Assignment 1");
    init ();
    glutDisplayFunc(display);
	glutMotionFunc ( mouseMove );
	glutKeyboardFunc ( keyboard );
	glutMouseFunc(mouseClick);
	glutMainLoop ( );
	return 0;
}
