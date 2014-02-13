#include "stdafx.h"
#include <iostream>
using namespace std;

typedef struct edge
{
	float maxY;
	float minY;
	float currentX;
	float xIncr;
};


typedef struct node                                                
{             
	edge edges;       // stores point information
    node *next;       // the reference to the next node
}; 