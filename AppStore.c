#include "AppStore.h"
#define DEFAULT_NAME "Colman Store"

AppStore* AddApp(AppStore* applicationStore, Application* app){
	int as_was_NULL = 0;//For free() purposes, in case of later malloc/realloc fails.
	if (applicationStore == NULL) {
		as_was_NULL = 1;
		/*
		* First, need to allocate memory the size of all of
		* the fields in AppStore, as specified in the header file
		*/
		applicationStore = malloc(
			sizeof(Application**)+sizeof(int)+sizeof(char*)
		);
		if (applicationStore == NULL) {
			return NULL;
		}
		/*
		* this section allocates space for the default name,
		* and copies the letters into it.
		*/
		int n = strlen(DEFAULT_NAME);
		char* name = malloc((n + 1) * sizeof(char));
		if (name == NULL) {
			free(applicationStore);
			return NULL;
		}
		strcpy_s(name, n + 1, DEFAULT_NAME);
		applicationStore->name = name;
		/*
		* End of name field shenanigans
		*/
		applicationStore->num_of_apps = 0;
		/*
		* From here on, we need to do the same as in the case where applicationStore
		* isn't NULL, but there is no application in the store with the name
		* app->name, so I will not continue in this block, in order to avoid
		* code duplication.
		*/
	}
	/*
	* First, I need to go over all the applications in applicationStore->apps,
	* and see if any of their names match the function paramater's name,
	* which is app->name
	*/
	for (int i = 0; i < applicationStore->num_of_apps; i++) {
		/*
		* if app is found in appstore, increase download count, and return appstore.
		*/
		if (strcmp((applicationStore->apps)[i]->name, app->name) == 0) {
			app->downloads++;
			return applicationStore;
		}
	}
	/*
	* else, need to reallocate applicationStore->apps, with applicationStore->num_of_apps+1
	*/
	Application** newAppList = realloc(applicationStore->apps,
		(applicationStore->num_of_apps + 1) * sizeof(Application));
	/*
	* if failed, need to free any previously dynamically allocated memory.
	* for this purpose, I created the boolean flag, as_was_NULL
	*/
	if(newAppList==NULL){
		if(as_was_NULL){
			free(applicationStore->name);
			free(applicationStore);
		}
		return NULL;
	}
	/*
	* Now, to duplicate the app into the last place of the apps array of pointers.
	* Again, might fail, and again will need to free memory if as_was_NULL == 1
	*/
	Application* copyOfAppToBeAdded = DuplicateApp(app);
	if(copyOfAppToBeAdded==NULL){
		if (as_was_NULL) {
			free(applicationStore->name);
			free(applicationStore);
		}
		free(newAppList);//Was not set as the apps field of applicationStore just yet.
		return NULL;
	}
	/*
	* Finally, can add the app to the list, and be done with this exercise.
	* First, to set the last app to the copy of the app:
	*/
	newAppList[applicationStore->num_of_apps] = copyOfAppToBeAdded;
	/*
	* Now, to set the apps field of applicationStore to be newAppList, and increase
	* applicationStore number of apps:
	*/
	applicationStore->apps = newAppList;
	applicationStore->num_of_apps++;
	return applicationStore;
}


AppStore* DuplicateStore(AppStore* source){}
void SortByCost(AppStore* as){}
void SortByName(AppStore* as){}
int TotalDownloads(AppStore* as){}
int UpdateDownloads(AppStore* as, char* name, int toAdd){}
int UpdateCost(AppStore* as, char* name, float newCost){}
int GetAppDownloads(AppStore* as, char* name){}
void FreeAppStore(AppStore* as){}