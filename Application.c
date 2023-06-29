#include "Application.h"

Application* CreateNewApp(char* _name, float _cost, int _downloads){
	int n = strlen(_name);
	/*
	* an instance of Application is made of a char pointer, a float and an int,
	* thus the required memory size is as written in the commas below:
	*/
	Application* newApp = (Application*)malloc(sizeof(char*) + sizeof(float) + sizeof(int));
	if (newApp == NULL) {
		return NULL;
	}
	/*
	* Now, to allocate space for the name(not to be confused with _name)
	* property of this instance of Application
	*/
	char* namePointer = (char*)malloc((n + 1) * sizeof(char));//+1, for '/0';
	if (namePointer == NULL) {
		free(newApp);//Was already allocated, have to free it.
		return NULL;
	}
	strcpy_s(namePointer, (n + 1), _name);
	/*
	* Now, to initialize the fields
	*/
	newApp->name = namePointer;
	newApp->cost = _cost;
	newApp->downloads = _downloads;
	
	return newApp;
}

Application* DuplicateApp(Application* source){
	/*
	* I will simply use the function from the previous excercise,
	* and suplly it the fields from the source as paramaters
	*/
	Application* duplicatedApp = CreateNewApp(source->name, source->cost, source->downloads);
	return duplicatedApp;
}
void FreeApp(Application* app){}