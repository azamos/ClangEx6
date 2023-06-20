#ifndef __APPLICATION_H
#define __APPLICATION_H

#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Application
{
	char* name;		//the name of the application
	float cost;		//the cost of the application in dollars
	int downloads;	//how many users downloaded the app
}Application;

Application* CreateNewApp( char* _name, float _cost, int _downloads );
Application* DuplicateApp( Application* source );
void FreeApp( Application* app );

#endif