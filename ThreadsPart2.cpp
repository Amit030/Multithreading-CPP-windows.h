
#include "stdafx.h"
#include <windows.h> 
#include<iostream>
#include <stdio.h>
using namespace std;


struct struct_information{
	HANDLE handler;
	string name;
	int sampleValue_1;
	int sampleValue_2;
	struct_information(HANDLE h,char n[],int x, int y){
		handler=h;
		name=n;
		sampleValue_1=x;
		sampleValue_2=y;
	}
};

//------------------------------------------
// A function to Display the message
// indicating in which tread we are
//------------------------------------------
void DisplayMessage ( 
	char *ThreadName, int Data, int Count)
{


	// Print message using thread-safe functions.
	cout<<"Executing iteration  "<<Count<<" of  "<<ThreadName<<"  having data  "<<Data<<endl;
	Sleep(1000);
}

//-------------------------------------------
// A function that represents Thread number 1
//-------------------------------------------
DWORD WINAPI Thread_no_1( LPVOID lpParam ) 
{

	int     Data = 0;
	int     count = 0;




	// Cast the parameter to the correct
	// data type passed by callee i.e main() in our case.
	struct_information structInformationObject = *((struct_information*)lpParam); 
	string name=structInformationObject.name;
	 Data=structInformationObject.sampleValue_2;
	 HANDLE obj=structInformationObject.handler;

	for (count = 0; count <= 4; count++ )
	{  WaitForSingleObject(obj,INFINITE);
	DisplayMessage (const_cast<char*>(structInformationObject.name.c_str()), Data, count);
	ReleaseMutex(obj);
	}

	return 0; 
} 

//-------------------------------------------
// A function that represents Thread number 2
//-------------------------------------------
DWORD WINAPI Thread_no_2( LPVOID lpParam ) 
{

	int     Data = 0;
	int     count = 0;



	// Cast the parameter to the correct
	// data type passed by callee i.e main() in our case.
	struct_information structInformationObject = *((struct_information*)lpParam); 
	string name=structInformationObject.name;
	Data=structInformationObject.sampleValue_2;
	HANDLE obj=structInformationObject.handler;

	for (count = 0; count <= 4; count++ )
	{  WaitForSingleObject(obj,INFINITE);
	DisplayMessage (const_cast<char*>(name.c_str()), s, count);
	ReleaseMutex(obj);
	}

	return 0; 
} 

//-------------------------------------------
// A function that represents Thread number 3
//-------------------------------------------
DWORD WINAPI Thread_no_3( LPVOID lpParam ) 
{
	int     Data = 0;
	int     count = 0;



	// Cast the parameter to the correct
	// data type passed by callee i.e main() in our case.
	struct_information structInformationObject = *((struct_information*)lpParam); 
	string name=structInformationObject.name;
	Data=structInformationObject.sampleValue_2;
	HANDLE obj=structInformationObject.handler;

	for (count = 0; count <= 4; count++ )
	{  WaitForSingleObject(obj,INFINITE);
	DisplayMessage (const_cast<char*>(name.c_str()), Data, count);
	ReleaseMutex(obj);
	}

	return 0; 
} 


int main()
{
	// Data of Thread 1
	int Data_Of_Thread_1 = 1;
	// Data of Thread 2
	int Data_Of_Thread_2 = 2;
	// Data of Thread 3
	int Data_Of_Thread_3 = 3;
	// variable to hold handle of Thread 1
	HANDLE Handle_Of_Thread_1 = 0;
	// variable to hold handle of Thread 1 
	HANDLE Handle_Of_Thread_2 = 0;
	// variable to hold handle of Thread 1
	HANDLE Handle_Of_Thread_3 = 0;
	// Aray to store thread handles 
	HANDLE Array_Of_Thread_Handles[3];


	//Creating a mutex

	HANDLE hMutex;
	hMutex= CreateMutex(NULL,FALSE,NULL);
	struct_information obj(hMutex,"Amit",2,4);
	struct_information obj2(hMutex,"Sumit",16,32);
	struct_information obj3(hMutex,"Keshav",64,128);

	// Create thread 1.
	Handle_Of_Thread_1 = CreateThread( NULL, 0, 
		Thread_no_1, &obj, 0, NULL);
	if ( Handle_Of_Thread_1 == NULL)
		ExitProcess(Data_Of_Thread_1);

	// Create thread 2.
	Handle_Of_Thread_2 = CreateThread( NULL, 0, 
		Thread_no_2, &obj2, 0, NULL);  
	if ( Handle_Of_Thread_2 == NULL)
		ExitProcess(Data_Of_Thread_2);

	// Create thread 3.
	Handle_Of_Thread_3 = CreateThread( NULL, 0, 
		Thread_no_3, &obj3, 0, NULL);  
	if ( Handle_Of_Thread_3 == NULL)
		ExitProcess(Data_Of_Thread_3);


	// Store Thread handles in Array of Thread
	// Handles as per the requirement
	// of WaitForMultipleObjects() 
	Array_Of_Thread_Handles[0] = Handle_Of_Thread_1;
	Array_Of_Thread_Handles[1] = Handle_Of_Thread_2;
	Array_Of_Thread_Handles[2] = Handle_Of_Thread_3;

	// Wait until all threads have terminated.
	WaitForMultipleObjects( 3, 
		Array_Of_Thread_Handles, TRUE, INFINITE);

	printf("Since All threads executed" 
		" lets close their handles \n");

	// Close all thread handles upon completion.
	CloseHandle(Handle_Of_Thread_1);
	CloseHandle(Handle_Of_Thread_2);
	CloseHandle(Handle_Of_Thread_3);
	getchar();
	return 0;
}

