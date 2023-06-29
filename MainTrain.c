#include "AppStore.h"

int compareAppDifferentAddress( Application* a1, Application* a2 )
{
	if( a1 == a2 )
		return 0;
	
	if( strcmp( a1->name, a2->name ) != 0 )
		return 0;

	if( a1->cost != a2->cost )
		return 0;

	if( a1->downloads != a2->downloads )
		return 0;

	return 1;
}

int compareAppStoreDifferentAddress( AppStore* as1, AppStore* as2 )
{
	int i;

	if( as1 == as2 )
		return 0;

	if( strcmp( as1->name, as2->name ) != 0 )
		return 0;

	if( as1->num_of_apps != as2->num_of_apps )
		return 0;

	for( i = 0; i < as1->num_of_apps; ++i )
	{
		if( 0 == compareAppDifferentAddress( as1->apps[i], as2->apps[i] ) )
			return 0;
	}

	return 1;
}

int checkApp( AppStore* as, Application* app )
{
	int i;
	if( NULL == as || NULL == app )
		return 0;

	for( i = 0; i < as->num_of_apps; ++i )
	{
		if( 0 == strcmp( as->apps[i]->name, app->name )
			&& as->apps[i]->cost == app->cost
			&& as->apps[i]->downloads == app->downloads )
			return 1;
	}

	return 0;
}

int checkSortedByCostsArray( AppStore* as, float costs[] )
{
	int i;
	for( i = 0; i < as->num_of_apps; ++i )
	{
		if( as->apps[i]->cost != costs[i] )
			return 0;
	}

	return 1;
}

int main()
{
	int sum = 0;
	float cost1 = 4.99f, cost2 = 19.99f, cost3 = 0.99f, cost4 = 5.5f;
	float arr1[] = { cost3, cost1, cost4, cost2 };
	float arr2[] = { cost1, cost2, cost4, cost3 };
	Application app1 = { "candy crash", cost1, 30 };
	Application app2 = { "clash royal", cost2, 25 };
	Application app3 = { "ynet", cost3, 32 };
	Application app4 = { "sport5", cost4, 20 };
	Application* pItem[3] = { &app1, &app2, &app3 };
	Application* pItem2[4] = { &app1, &app2, &app3, &app4 };
	AppStore s = { pItem, 3, "App Store" };
	AppStore s2 = { pItem2, 4, "Google Play" };
	AppStore* tmpStore = NULL;
	AppStore* myStore;
	Application* p1;
	Application* p2;

	//------------------------------------------------------------------------------------------------------------
	//=============== EX 1 ================// 
	p1 = CreateNewApp( "candy crash", cost1, 30 );
	if( 0 == compareAppDifferentAddress( p1, &app1 ) )
		printf( "Failed Ex1 - CreateNewApp function (-8)\n" );

	//=============== EX 2 ================// 
	p2 = DuplicateApp( &app2 );
	if( 0 == compareAppDifferentAddress( p2, &app2 ) )
		printf( "Failed Ex2 - DuplicateApp function (-8)\n" );

	//=============== EX 3 ================// 
	tmpStore = AddApp( tmpStore, &app1 );
	if( 0 == checkApp( tmpStore, &app1 ) )
		printf( "Failed Ex3 - AddApp function (-8)\n" );

	//=============== EX 4 ================// 
	myStore = DuplicateStore( &s );
	if( 0 == compareAppStoreDifferentAddress( &s, myStore ) )
		printf( "Failed Ex4 - DuplicateStore function (-8)\n" );

	////=============== EX 5 ================// 
	//SortByCost( &s2 );
	//if( 0 == checkSortedByCostsArray( &s2, arr1 ) )
	//	printf( "Failed Ex5 - SortByCost function (-8)\n" );

	////=============== EX 6 ================// 
	//SortByName( &s2 );
	//if( 0 == checkSortedByCostsArray( &s2, arr2 ) )
	//	printf( "Failed Ex6 - SortByName function (-8)\n" );

	////=============== EX 7 ================// 
	//sum = TotalDownloads( &s2 );
	//if( sum != 107 )
	//	printf( "Failed Ex7 - TotalDownloads function (-8)\n" );

	////=============== EX 8 ================// 
	//if( 1 != UpdateDownloads( &s2, "ynet", 10 ) )
	//	printf( "Failed Ex8 - UpdateDownloads function (-8)\n" );
	//else if( s2.apps[3]->downloads != 42 )
	//	printf( "Failed Ex8 - UpdateDownloads function (-8)\n" );

	////=============== EX 9 ================// 
	//if( 0 != UpdateCost( &s2, "lala", 4.5 ) )
	//	printf( "Failed Ex9 - UpdateCost function (-8)\n" );

	////=============== EX 10 ================// 
	//if( 20 != GetAppDownloads( &s2, "sport5" ) )
	//	printf( "Failed Ex10 - GetAppDownloads function (-8)\n" );

	////=============== EX 11+12 ================// 
	//FreeAppStore( myStore );
	//
	//=============== FINISH ================// 
	printf( "\n\ndone\n" );

	return 0;
}