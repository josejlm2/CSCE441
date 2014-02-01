#include "stdafx.h"
#include <iostream>
using namespace std;


typedef struct node                                                
{                                                               
	int nodeX;
	int nodeY;       // stores point information
    node *next;             // the reference to the next node
}; 


typedef struct edge
{
	float maxY;
	float currentX;
	float xIncr;
};
