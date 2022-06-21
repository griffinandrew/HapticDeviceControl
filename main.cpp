//Griffin Heyrich
//Hapctic Device Controller
//MBL_BU, Boston, MA
//This is the C++ code that creates and launches the user interface using the quickhaptics api. 
//A servoloop callback is used to get the call get the positon vector of the cursor. 
//The positon vector is processed and broken down into its components and sent to "position1.txt", 
//this is cleared each time before being appended to in order so that only 3 values at a time will be in the file for reading.


//Include all necessary headers
#include <QHHeadersGLUT.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include <atlstr.h>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include "SimpleSerial.h"

//This class carried data into the ServoLoop thread
class DataTransportClass
{
public:
	TriMesh* Model;//Trimesh pointer to hold mesh data
	Cursor* deviceCursor;//Pointer to hold the cursor data
};

//declarations
void writePos2File(hduVector3Dd P_V);
void printVec(hduVector3Dd position);
void sendDevPos(void);
void HLCALLBACK positonCB(HDdouble force[3], HLcache *cache, void *userdata);
void HLCALLBACK stopEffectCB(HLcache *cache, void *userdata);
void HLCALLBACK startEffectCB(HLcache *cache, void *userdata);
void file_verify(void);
using namespace std;


//time1 is a global variable
time_t time1 = time(NULL);

//intialize the haptic device and set up user face for rendering. begin servo loop to get cursor positon
//on start up clear the old file 
int main(int argc, char *argv[])
{
    QHGLUT* DisplayObject = new QHGLUT(argc,argv);//create a display window
    DeviceSpace* OmniSpace = new DeviceSpace;//Find the default Phantom Device
    DisplayObject->tell(OmniSpace);//Tell QuickHaptics about it
    DisplayObject->setBackgroundColor(0.8,0.65,0.4);

	//TriMesh* room = new TriMesh("models/appleBasket/sphere_big.stl", 5.0, 5.0, 5.0, 5.0);
	//room->setTexture("models/appleBasket/wood.jpg");
	//room->setUnDraggable();
	//DisplayObject->tell(room);

	Cursor* OmniCursor = new Cursor("models/appleBasket/pencil.3DS");//Declare a new cursor
	OmniCursor->scaleCursor(0.001);
	TriMesh* ModelTriMeshPointer = OmniCursor->getTriMeshPointer();
	ModelTriMeshPointer->setTexture("models/appleBasket/pencil.JPG");
	DisplayObject->tell(OmniCursor);//tell QuickHaptics about the cursor

	//This function defines the servoloop callback, The servoloop function will be invoked at the servo loop rate(1000 Hz)
	OmniSpace->startServoLoopCallback(startEffectCB, positonCB, stopEffectCB, &DisplayObject);

	//clear the old positions 
	std::ofstream OFS;
	OFS.open("positions1.txt", std::ofstream::out | std::ofstream::trunc);
	OFS.close();

	//Set everything in motion 
    qhStart(); 

    return 0;
}

void printVec(hduVector3Dd position)
{
	printf("Device position: %.3f %.3f %.3f\n", position[0], position[1], position[2]); 
}

//if longer than .1 seconds has past the file is cleared and each position is appended
void writePos2File(hduVector3Dd P_V)
{
	time_t time2 = time(NULL);
	auto sec = difftime(time2, time1);

	if (sec >= .1) // if it has been greater than .1 sec send position to file for py to read and send to ardunio
	{
		// Create a Vector
		hduVector3Dd V = P_V;
		
		std::ofstream clear; //this is just clearing the contents of the file prior to the write, so I only should have 3 elemets in my file at a time
		clear.open("positions1.txt", std::ofstream::out | std::ofstream::trunc);
		
		//open file and write coordinate to a newline
		ofstream myfile("positions1.txt", std::ofstream::app);
		if (myfile.is_open())
		{
			myfile << V[0] << '\n';
			myfile << V[1] << '\n';
			myfile << V[2] << '\n';
			myfile.close();
		}
		else
		{
			cerr << "Error: file not open here!" << endl; 
			exit(1);
		}

		myfile.close();

		time1 = time(NULL); //reset the clock again after pos sent 

	}
	return;
}


//verifies that what is being sent (USED FOR TESTING)
void file_verify(void)
{
	hduVector3Dd V2;
	FILE* file2 = fopen("positions1.txt", "r");

	fread(&V2, sizeof(double), 3, file2);

	fclose(file2);

	cout << "file verification";

	printf("%f, %f, %f \n", V2[0], V2[1], V2[2]);
}

//defines the callback on the device to get the postion at the rate of the servoloop ~1000 hz 
HDCallbackCode HDCALLBACK DevicePositionCallback(void *pUserData)
{
	HDdouble *pPosition = (HDdouble *)pUserData;

	hdBeginFrame(hdGetCurrentDevice());
	hdGetDoublev(HD_CURRENT_POSITION, pPosition);
	hdEndFrame(hdGetCurrentDevice());

	return HD_CALLBACK_DONE;
}

//this sends the position to writePos2Filefunction to send to file then prints the device position 
void sendDevPos(void)
{
	hduVector3Dd position;

	hdScheduleSynchronous(DevicePositionCallback, position,HD_DEFAULT_SCHEDULER_PRIORITY);

	writePos2File(position);

    printf("Device position: %.3f %.3f %.3f\n",
	position[0], position[1], position[2]);
}


// Servo loop thread callback called when the effect is started.
void HLCALLBACK startEffectCB(HLcache *cache, void *userdata)
{
	DataTransportClass *localdataObject = (DataTransportClass *)userdata;
	printf("Custom effect started\n");
}


// Servo loop thread callback called when the effect is stopped.
void HLCALLBACK stopEffectCB(HLcache *cache, void *userdata)
{
	printf("Custom effect stopped\n");
}

//callback to trigger sending positons to file
void HLCALLBACK positonCB(HDdouble force[3], HLcache *cache, void *userdata)
{
	sendDevPos();
}
