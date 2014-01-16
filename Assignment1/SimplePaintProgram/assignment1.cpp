// OpenGLAssignment1.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <gl/glut.h>
#include <gl/gl.h>
#include <math.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

//GLOBAL VARIABLES
float SIZE = 1;
float ROTATE_ANGLE = 0;
float TRANSPARENCY_LEVEL = 0.2;
bool isTRANS = false;
bool isQUAD = true;
bool isTRIANGLE = false;
bool isLINE = false;
bool isCIRCLE = false;


void changeRotateAngle()
{
	if (ROTATE_ANGLE == 360)
	{
		ROTATE_ANGLE = 10;
	}
	else 
		ROTATE_ANGLE += 10;
}

void brushSelection()
{
	if (isQUAD == true)
	{
		isQUAD = false;
		isTRIANGLE = true;
	}
	else if (isTRIANGLE == true)
	{
		isTRIANGLE = false;
		isLINE = true;
	}
	else if (isLINE == true)
	{
		isLINE = false;
		isCIRCLE = true;
	}
	else if (isCIRCLE == true)
	{
		isCIRCLE = false;
		isQUAD = true;
	}
}


void quad(int x, int y)
{
	
	isTRANS = false;
	glTranslatef(x, y, 0);
	glRotatef(ROTATE_ANGLE,0,0,1);
	
	glBegin ( GL_QUADS );
		glVertex2f (-SIZE, SIZE);
		glVertex2f (-SIZE,-SIZE);
		glVertex2f (SIZE, -SIZE);
		glVertex2f (SIZE, SIZE);
	glEnd ( );
	glFlush ( );
	
	glRotatef(ROTATE_ANGLE,0,0,-1);
	glTranslatef(-x, -y, 0);
}

void triangle(int x, int y)
{
	glTranslatef(x, y, 0);
	glRotatef(ROTATE_ANGLE,0,0,1);
		
	glBegin(GL_TRIANGLES);
		glVertex2f(-SIZE,-SIZE);
		glVertex2f(SIZE,-SIZE);
		glVertex2f(0,SIZE);
	glEnd();
	glFlush ( );

	glRotatef(ROTATE_ANGLE,0,0,-1);
	glTranslatef(-x, -y, 0);
}

void line(int x, int y)
{
	glTranslatef(x, y, 0);
	glRotatef(ROTATE_ANGLE,0,0,1);
	
	glBegin(GL_LINES);
		glVertex2f(0,-SIZE);
		glVertex2f(0,SIZE);
	glEnd();
	glFlush ( );

	glRotatef(ROTATE_ANGLE,0,0,-1);
	glTranslatef(-x, -y, 0); 
}

void circle(int x, int y)
{
	glBegin(GL_TRIANGLE_FAN);
		for (int i=0; i<=360;i++)
		{
			float temp = i; 
			glVertex2f(SIZE*cos(temp)+x,SIZE*sin(temp)+y);
		}
	glEnd();
	glFlush();
}



//initalize
void init ( void )
{
	printf( "OpenGL version: %s\n", (char*)glGetString(GL_VERSION));
    printf( "OpenGL renderer: %s\n", (char*)glGetString(GL_RENDERER));
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, WINDOW_WIDTH-1, WINDOW_HEIGHT-1, 0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

void display ( void )
{
	glClear ( GL_COLOR_BUFFER_BIT );
	glFlush ( );//make sure everything is drawn
}

void mouseClick(int button, int state, int x, int y)
{
	if (isQUAD == true)
	{
		quad(x,y);	
	}
	else if (isTRIANGLE == true)
	{
		triangle(x, y);
	}
	else if (isLINE == true)
	{
		line(x,y);
	}
	else if (isCIRCLE == true)
	{
		circle(x,y);
	}
}

void mouseMove ( int x, int y )
{
	if (isQUAD == true)
	{
		quad(x,y);
	}
	else if (isTRIANGLE == true)
	{
		triangle(x,y);
	}
	else if (isLINE == true)
	{
		line(x,y);
	}
	else if (isCIRCLE == true)
	{
		circle(x,y);
	}
}


void keyboard ( unsigned char key, int x, int y )
{
	switch ( key )
	{
		//TOOLSs
		case 'b':
			brushSelection();
			break;
		case 'c':
			glutPostRedisplay( );
			break;
		case 'r':
			changeRotateAngle();
			break;
		case 'a':
			TRANSPARENCY_LEVEL = 0.1;
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
			glColor4f ( 1, 0, 0, TRANSPARENCY_LEVEL);//red
			break;
		case '2':
			glColor4f ( 0, 1, 0, TRANSPARENCY_LEVEL);//green
			glFlush();
			break;
		case '3':
			glColor4f ( 1, 1, 0, TRANSPARENCY_LEVEL);//blue
			break;
		case '4':
			glColor4f ( 0, 0, 1, TRANSPARENCY_LEVEL);//yellow
			break;
		case '5':
			glColor4f ( 1, 0, 1, TRANSPARENCY_LEVEL);//pink
			break;
		case '6':
			glColor4f ( 0, 1, 1, TRANSPARENCY_LEVEL);//cyan
			break;
		case '7':
			glColor4f ( 1, 1, 1, TRANSPARENCY_LEVEL);//white
			break;

		default:
			break;
	}
}


int main ( int argc, char *argv[] )
{
	glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (WINDOW_WIDTH, WINDOW_HEIGHT); 
    glutInitWindowPosition (200, 100);
    glutCreateWindow ("Jose Manriquez - Assignment 1");
	glEnable(GL_BLEND); // needed for circle blend effect
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_POINT_SMOOTH);
            glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
            glEnable(GL_LINE_SMOOTH);
            glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
            glEnable(GL_POLYGON_SMOOTH);
            glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glClearColor (0.0, 0.0, 0.0, 0.0);
	init ();
    glutDisplayFunc(display);
	glutMouseFunc(mouseClick);
	glutMotionFunc ( mouseMove );
	glutKeyboardFunc ( keyboard );
	glutMainLoop ( );
	return 0;
}
