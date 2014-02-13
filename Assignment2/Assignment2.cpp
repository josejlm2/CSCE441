

// Assignment2.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include "LinkedList.cpp"
#include <vector>
#include<GL/glut.h>
#include <utility>     
#include <string>
#include <list>

using namespace std;



// GLOBAL VARIABLES
bool START = true, CLIPPING = false;
int StartX, StartY,TempX, TempY;
float tempMaxY=0,tempMinY=400;

node *head = NULL, *nextNode, *prevNode;
/******************************************************************
	Notes:
	Image size is 400 by 400 by default.  You may adjust this if
		you want to.
	You can assume the window will NOT be resized.
	Call clearFramebuffer to clear the entire framebuffer.
	Call setFramebuffer to set a pixel.  This should be the only
		routine you use to set the color (other than clearing the
		entire framebuffer).  drawit() will cause the current
		framebuffer to be displayed.
	As is, your scan conversion should probably be called from
		within the display function.  There is a very short sample
		of code there now.
	You may add code to any of the subroutines here,  You probably
		want to leave the drawit, clearFramebuffer, and
		setFramebuffer commands alone, though.
  *****************************************************************/

#define ImageW 400
#define ImageH 400

float framebuffer[ImageH][ImageW][3];


struct color {
	float r, g, b;		// Color (R,G,B values)
};


// Draws the scene
void drawit(void)
{
   glDrawPixels(ImageW,ImageH,GL_RGB,GL_FLOAT,framebuffer);
}

// Clears framebuffer to black
void clearFramebuffer()
{
	int i,j;

	for(i=0;i<ImageH;i++) {
		for (j=0;j<ImageW;j++) {
			framebuffer[i][j][0] = 0.0;
			framebuffer[i][j][1] = 0.0;
			framebuffer[i][j][2] = 0.0;
		}
	}
}

// Sets pixel x,y to the color RGB
// I've made a small change to this function to make the pixels match
// those returned by the glutMouseFunc exactly - Scott Schaefer 
void setFramebuffer(int x, int y, float R, float G, float B)
{
	// changes the origin from the lower-left corner to the upper-left corner
	y = ImageH - 1 - y;
	if (R<=1.0)
		if (R>=0.0)
			framebuffer[y][x][0]=R;
		else
			framebuffer[y][x][0]=0.0;
	else
		framebuffer[y][x][0]=1.0;
	if (G<=1.0)
		if (G>=0.0)
			framebuffer[y][x][1]=G;
		else
			framebuffer[y][x][1]=0.0;
	else
		framebuffer[y][x][1]=1.0;
	if (B<=1.0)
		if (B>=0.0)
			framebuffer[y][x][2]=B;
		else
			framebuffer[y][x][2]=0.0;
	else
		framebuffer[y][x][2]=1.0;
}

void display(void)
{
	// should not be necessary but some GPUs aren't displaying anything until a clear call.
	glClear ( GL_COLOR_BUFFER_BIT );

	//The next two lines of code are for demonstration only.
	//They show how to draw a line from (0,0) to (100,100)
	/*
	int i;
	for(i=0;i<=100;i++) setFramebuffer(i,i,1.0,1.0,1.0);

	drawit();
	glBegin ( GL_LINES );
		glVertex2f ( 200, 200 );
		glVertex2f ( 400, 400 );
	glEnd ( );
	glFlush ( );*/
}

void resetMaxMinY()
{
	tempMaxY = 0;
	tempMinY = 400;

}


//accept user keyboard input
void keyboard ( unsigned char key, int x, int y )
{
	switch ( key )
	{
		case 'c':
			//clipping mode
			break;
		default:
			break;
	}
}


vector<pair<int, int>> points;
vector<pair<pair<int,int>,pair<int,int>>> edges;
vector<edge *> allEdges;

// accept user mouse input
void mouseClick(int button, int state, int x, int y)
{
	
	//If left button is clicked for the first time, START drawing polygon
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && START == true)
	{
		edge edge1;//create edge structure
		cout<<endl<<"START POLYGON"<<endl;
		StartX=x;
		StartY=y;
		TempX = x;
		TempY = y;
		glBegin ( GL_POINTS );
			glVertex2f ( x, y );
		glEnd;
		//setFramebuffer(x,y,1.0,1.0,1.0);
		//drawit();
		glFlush();
		START = false;
	}
	
	//If left button is pressed, Draw a line from previous point to the next point
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && START == false)
	{
		glBegin ( GL_LINES );
		glVertex2f ( TempX, TempY );
			glVertex2f ( x, y );
		glEnd ( );
		glFlush();
		TempX=x;
		TempY=y;
		points.push_back(make_pair(x,y));//store point in vector
	}
	

	
	//If right button is pressed, END polygon, close the figure, and scan polygon
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && START == false)
	{
		//Draw last two lines
		glBegin ( GL_LINES );
			glVertex2f ( TempX, TempY );
			glVertex2f ( x, y );
			glVertex2f ( StartX, StartY);
		glEnd ( );
		glBegin ( GL_LINES );
			glVertex2f ( x, y );
			glVertex2f ( StartX, StartY);
		glEnd ( );

		glFlush();
		START = true;

		//store last two points in vector
		points.push_back(make_pair(x,y));
		points.push_back(make_pair(StartX,StartY));
		
		//count edges, print out results
		int tempCounter=0;
		for( std::vector<pair<int,int>>::const_iterator i = points.begin(); i != points.end(); ++i)
		{
			pair<int, int> result1 = (*i);
			cout<<"VERTEX: ("<<result1.first<<", "<<result1.second<<")"<<endl;
			tempCounter++;
		}
		cout<<"END POLYGON"<<endl;
		
		//store poinst into the edges vector
		cout<<endl<<"EDGES"<<endl;
		for (int i=0; i<tempCounter-1;i++)
		{
			edges.push_back(make_pair(points.at(i++),points.at(i)));
			i--;
		}
		

		//print out edge results
		int lineCounter=1;
		for( std::vector<pair<pair<int,int>,pair<int,int>>>::const_iterator i = edges.begin(); i != edges.end(); ++i)
		{
			//Temp Variables
			pair<pair<int,int>, pair<int,int>> result = (*i);
			float x1 = result.first.first;
			float y1 = result.first.second;
			float x2 = result.second.first;
			float y2 = result.second.second;
			
			float tempY = min(y1,y2);
			tempMinY = min(tempMinY,tempY);
			tempY = max(y1,y2);
			tempMaxY = max(tempMaxY, tempY);
			
			
			//printout Edges
			cout<<"EDGES"<<lineCounter<<": ("<<x1<<", "<<y1<<") -> ("<<x2<<", "<<y2<<")"<<endl;
			++lineCounter;

			//Convert lines into Edges ready for Active Edge List
			edge *temp;
			temp = (edge*)malloc(sizeof(edge));
			temp->maxY = max(y1,y2);
			temp->minY = min(y1,y2);
			if (y1<y2)
			{
				temp->currentX = x1;
			}
			else
			{
				temp->currentX = x2;
			}
			temp->xIncr = (x2-x1)/(y2-y1);
			allEdges.push_back(temp);

		}

		cout<<endl<<"EDGE STRUCTURE"<<endl;
		for( std::vector<edge *>::const_iterator i = allEdges.begin(); i != allEdges.end(); ++i)
		{
			edge *result = (*i);
			cout<<"MaxY: "<<result->maxY<<endl;
			cout<<"MinY: "<<result->minY<<endl;
			cout<<"CurrentX: "<<result->currentX<<endl;
			cout<<"xIncr: "<< result->xIncr<<endl<<endl;	
		
		}
		
		cout<<endl<<"SCAN LINE"<<endl;
		cout<<"MAX Y: "<< tempMaxY<<endl;
		cout<<"MIN Y: "<< tempMinY<<endl;

		vector<list<edge *>> activeEdgeTable;
		activeEdgeTable.resize(tempMaxY);

		for (int k=tempMinY; k<=tempMaxY;k++)
		{
			for( std::vector<edge *>::const_iterator i = allEdges.begin(); i != allEdges.end(); ++i)
			{
				edge *result = (*i);

				if (result->minY == k)//add edge to list
				{
					
					/*if (activeEdgeTable.at(k).front == NULL)
					{
						list<edge *> a;
						a.push_back(*i);
						activeEdgeTable.at(k).merge(a);		
					}
					else*/
					activeEdgeTable.at(k).push_back(*i);
					cout<<"k"<<k<<" ";
				}

			/*cout<<"MaxY: "<<result->maxY<<endl;
			cout<<"MinY: "<<result->minY<<endl;
			cout<<"CurrentX: "<<result->currentX<<endl;
			cout<<"xIncr: "<< result->xIncr<<endl<<endl;	
		*/
			}	
			//activeEdgetable.at(i);
		
		}
		
		//Clear vectors
		points.clear();
		edges.clear();
		allEdges.clear();
		resetMaxMinY();
	}
	
}




void polygonAlgorithm()
{
	int line = 0;
	int height;
	while (line<height)
	{
		//add edges to active edge list from active edge table starting at line

		//remove edges that end at line
		//fill pixels
		//increment x-value on edges in Active Edge List
		line++;
	}

	


}



void init(void)
{
	gluOrtho2D ( 0, ImageW - 1, ImageH - 1, 0 );
	clearFramebuffer();
	drawit();
}

int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(ImageW,ImageH);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Jose Manriquez - Homework 2");
	init();	
	
	glutDisplayFunc(display);
	glutKeyboardFunc (keyboard);
	glutMouseFunc(mouseClick);
	glutMainLoop();
	return 0;
}
