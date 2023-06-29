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
		applicationStore = (AppStore*)malloc(sizeof(AppStore));
		if (applicationStore == NULL) {
			return NULL;
		}
		/*
		* this section allocates space for the default name,
		* and copies the letters into it.
		*/
		int n = strlen(DEFAULT_NAME);
		char* name = (char*)malloc((n + 1) * sizeof(char));
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
		applicationStore->apps = NULL;
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


AppStore* DuplicateStore(AppStore* source){
	/*
	* Steps:
	* 1.Allocate enough memory for the 3 fields: Application** apps,
	* int num_of_aps,char* name.Essentialy, 2 pointers and an integer.
	* 2.allocate memory for name, and str_cpy from source->name.
	* 3.set duplicate's num_of_apps to be the same as the source's.
	* 4.now, allocate num_of_apps times sizeof(Application*) for the apps themselves.
	* 5.use DuplicateApplication function to copy the apps.
	* 6.return the duplicate store.
	*/

	//1.
	AppStore* duplicateStore = (AppStore*)malloc(sizeof(AppStore));
	if (duplicateStore == NULL) {
		return NULL;
	}

	//2
	char* dup_name = (char*)malloc((strlen(source->name) + 1) * sizeof(char));
	if (!dup_name) {
		free(duplicateStore);
		return NULL;
	}
	strcpy_s(dup_name, strlen(source->name) + 1, source->name);
	duplicateStore->name = dup_name;

	//3
	duplicateStore->num_of_apps = source->num_of_apps;

	//4
	Application** dup_apps = (Application**)malloc(duplicateStore->num_of_apps * sizeof(Application*));
	
	//5
	for (int i = 0; i < duplicateStore->num_of_apps; i++) {
		Application* dupApp = DuplicateApp(source->apps[i]);
		if (dupApp == NULL) {
			for (int j = 0; j < i; j++) {
				free(dup_apps[i]);
			}
			free(dup_apps);
			free(dup_name);
			free(duplicateStore);
		}
		dup_apps[i] = dupApp;
	}
	duplicateStore->apps = dup_apps;
	return duplicateStore;
}

void SortByCost(AppStore* as){
	Application** apps = as->apps;
	int n = as->num_of_apps;
	/*
	* Buuble-sort, comparison function here is on the costs
	*/
	for (int i = 0; i < n-1; i++) {
		for(int j=0;j<n-i-1;j++){
			if ((apps[j]->cost) > (apps[j + 1]->cost)) {
				Application* temp = apps[j];
				apps[j] = apps[j + 1];
				apps[j + 1] = temp;
			}
		}
	}
}


void SortByName(AppStore* as){
	Application** apps = as->apps;
	int n = as->num_of_apps;
	/*
	* Buuble-sort, comparison func is str_cmp on the names
	*/
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (strcmp((apps[j]->name), (apps[j + 1]->name))>0) {
				Application* temp = apps[j];
				apps[j] = apps[j + 1];
				apps[j + 1] = temp;
			}
		}
	}
}

int TotalDownloads(AppStore* as){
	int sum = 0;
	for (int i = 0; i < as->num_of_apps; i++) {
		sum += as->apps[i]->downloads;
	}
	return sum;
}

int UpdateDownloads(AppStore* as, char* name, int toAdd){
	for (int i = 0; i < as->num_of_apps; i++) {
		if (strcmp(as->apps[i]->name, name) == 0) {
			as->apps[i]->downloads += toAdd;
			return 1;
		}
	}
	return 0;
}
int UpdateCost(AppStore* as, char* name, float newCost){
	for (int i = 0; i < as->num_of_apps; i++) {
		if (strcmp(as->apps[i]->name, name) == 0) {
			as->apps[i]->cost = newCost;
			return 1;
		}
	}
	return 0;
}
int GetAppDownloads(AppStore* as, char* name){
	for (int i = 0; i < as->num_of_apps; i++) {
		if (strcmp(as->apps[i]->name, name) == 0) {
			return as->apps[i]->downloads;
		}
	}
	return 0;
}
void FreeAppStore(AppStore* as){
	for (int i = 0; i < as->num_of_apps; i++) {
		FreeApp(as->apps[i]);
	}
	free(as->apps);
	free(as->name);
	free(as);
}