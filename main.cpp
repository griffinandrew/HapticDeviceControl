//Griffin Heyrich
//Hapctic Device Controller
//MBL_BU, Boston, MA
//the function of this block of 

#include <QHHeadersGLUT.h>//Include all necessary headers
#include <string>
#include <stdio.h>
#include <iostream>
#include <atlstr.h>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include "SimpleSerial.h"


class DataTransportClass//This class carried data into the ServoLoop thread
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


int main(int argc, char *argv[])
{
    QHGLUT* DisplayObject = new QHGLUT(argc,argv);//create a display window
    DeviceSpace* OmniSpace = new DeviceSpace;//Find the default Phantom Device
    DisplayObject->tell(OmniSpace);//Tell QuickHaptics about it
    DisplayObject->setBackgroundColor(0.8,0.65,0.4);

	TriMesh* room = new TriMesh("models/appleBasket/sphere_big.stl", 5.0, 5.0, 5.0, 5.0);
	room->setTexture("models/appleBasket/wood.jpg");
	room->setUnDraggable();
	DisplayObject->tell(room);

	Cursor* OmniCursor = new Cursor("models/appleBasket/pencil.3DS");//Declare a new cursor
	OmniCursor->scaleCursor(0.001);
	TriMesh* ModelTriMeshPointer = OmniCursor->getTriMeshPointer();
	ModelTriMeshPointer->setTexture("models/appleBasket/pencil.JPG");
	DisplayObject->tell(OmniCursor);//tell QuickHaptics about the cursor

	//This function defines the servoloop callback, The servoloop function will be invoked at the servo loop rate(1000 Hz)
	OmniSpace->startServoLoopCallback(startEffectCB, positonCB, stopEffectCB, &room);

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


void writePos2File(hduVector3Dd P_V) //hduVector3Dd P_V should be inside
{

	time_t time2 = time(NULL);
	auto sec = difftime(time2, time1);

	if (sec >= .1) // if it has been greater than .5 send position to file for py to read and send to ardunio
	{
		// Create a Vector
		hduVector3Dd V = P_V;
		
		std::ofstream clear; //this is just clearing the contents of the file prior to the write, so I only should have 3 elemets in my file at a time
		clear.open("positions1.txt", std::ofstream::out | std::ofstream::trunc);

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


HDCallbackCode HDCALLBACK DevicePositionCallback(void *pUserData)
{
	HDdouble *pPosition = (HDdouble *)pUserData;

	hdBeginFrame(hdGetCurrentDevice());
	hdGetDoublev(HD_CURRENT_POSITION, pPosition);
	hdEndFrame(hdGetCurrentDevice());

	return HD_CALLBACK_DONE;
}

//thihs sends the position to function to send to file then prints the device position 
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
