//Griffin Heyrich
//Hapctic Device Controller
//MBL_BU, Boston, MA

#include <QHHeadersGLUT.h>//Include all necessary headers
#include <string>
#include <stdio.h>
#include <iostream>
#include <atlstr.h>
#include <fstream>
#include <cstdlib>



//im not sure if i will need this class declaration or not
class DataTransportClass//This class carried data into the ServoLoop thread
{
public:
  TriMesh* Model;//Trimesh pointer to hold mesh data
  Cursor* deviceCursor;//Pointer to hold the cursor data
};


//declarations
void callbackCursorTest(unsigned int ShapeID);
void serializeVectorTest(hduVector3Dd P_V);
void write_to_file(void);
void getPos(void);
void printVec(hduVector3Dd position);
void PrintDevPos(void);
void HLCALLBACK positonCB(HDdouble force[3], HLcache *cache, void *userdata);
void HLCALLBACK stopEffectCB(HLcache *cache, void *userdata);
void HLCALLBACK startEffectCB(HLcache *cache, void *userdata);
using namespace std;

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
  OmniCursor->scaleCursor(0.001);//Scale the cursor because it is too large, not sure what the proper scale would be in this case
  TriMesh* ModelTriMeshPointer = OmniCursor->getTriMeshPointer();//dont think i will need this
  ModelTriMeshPointer->setTexture("models/appleBasket/pencil.JPG");
  DisplayObject->tell(OmniCursor);//tell QuickHaptics about the cursor

  //OmniSpace->touchCallback(callbackCursorTest, room);

//startServoLoopCallback(void(HLCALLBACK *startServoLoopCallback)(HLcache *, void *), void(HLCALLBACK *MainServoLoopCallback)(HDdouble force[6], HLcache *, void *), void(HLCALLBACK *StopServoLoopCallback)(HLcache *, void *), void *userData)
//This function defines the servoloop callback, The servoloop function will be invoked at the servo loop rate(1000 Hz)
  OmniSpace->startServoLoopCallback(startEffectCB, positonCB, stopEffectCB, &room);

//DisplayObject->preDrawCallback();

    qhStart(); //Set everything in motion

    return 0;
}

//int serial_port = open("\\\\.\\COM3", O_RDWR);


void printVec(hduVector3Dd position)
{
  printf("Device position: %.3f %.3f %.3f\n", position[0], position[1], position[2]);
}


void writeToPort(hduVector3Dd P_V) 
  hduVector3Dd V = P_V;

  FILE* file = fopen("\\\\.\\COM3", "w+"); // going to need to change to serial port as file type 

  if (file == NULL) 
  {
    cerr << "Error: file not open!" << endl;
    //std::cout << "file not open!";
    exit(1);
  }

  char textmsg[] = { "am i in the file" };

  fwrite(textmsg, sizeof(char), sizeof(textmsg), file); // in theory this should be printed into the file a shit load of time

  fwrite((double*)(&V), sizeof(double), 3, file); // what is being written is not correct

  fclose(file);

  return;
}

//this is whats being called
void serializeVectorTest(hduVector3Dd P_V) //hduVector3Dd P_V should be inside
{
  hduVector3Dd V = P_V;

  FILE* file = fopen("postions.txt", "w+"); // going to need to change to serial port as file type


  //file2 is for testing if it is the file type matters at all when writing 
  FILE* file2 = fopen("postions.bin", "w+");

  if (file == NULL) 
  {
    cerr << "Error: file not open!" << endl;
    //std::cout << "file not open!";
    exit(1);
  }

  if (file2 == NULL) 
  {
    cerr << "Error: file2 not open!" << endl;
    //std::cout << "file not open!";
    exit(1);
  }

  char textmsg[] = { "am i in the file" };

  fwrite(textmsg, sizeof(char), sizeof(textmsg), file); // in theory this should be printed into the file a shit load of time

  fwrite(textmsg, sizeof(char), sizeof(textmsg), file2);

  fwrite((double*)(&V), sizeof(double), 3, file2); // what is being written is not correct

  fwrite((double*)(&V), sizeof(double), 3, file); // what is being written is not correct

  fclose(file);

  fclose(file2);

  return;
}


HDCallbackCode HDCALLBACK DevicePositionCallback(void *pUserData)
{
  HDdouble *pPosition = (HDdouble *)pUserData;

  hdBeginFrame(hdGetCurrentDevice());
  hdGetDoublev(HD_CURRENT_POSITION, pPosition);
  hdEndFrame(hdGetCurrentDevice());

  return HD_CALLBACK_DONE;
}

void PrintDevPos(void)
{
  //Sleep(500); // this helps but now wont render which is wack
  hduVector3Dd position;

  hdScheduleSynchronous(DevicePositionCallback, position,
  HD_DEFAULT_SCHEDULER_PRIORITY);

  serializeVectorTest(position);

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

//this just defines what to do within the servoloop
//i am simply just calling the callback to retreive and write the position of the cursor
void HLCALLBACK positonCB(HDdouble force[3], HLcache *cache, void *userdata)
{
  PrintDevPos();
}


///////////////////////////////////////////////////////////////////////////////////////////
//this section of the file will be in ardunio and will not be included in this file in 


double Byte1 = 0.0;   // for incoming serial data
double Byte2 = 0.0;
double Byte3 = 0.0;

void setup() {
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
}

void loop() 
{

  //add a sleep timer to only read in data every ~.5s 
  Sleep(500); 

  // send data only when you receive data:
  if (Serial.available() > 0)
  {
  // read the incoming byte:
  Byte1 = Serial.read();
  Byte2 = Serial.read();
  Byte3 = Serial.read();
  double  curPos[3] = [Byte1, Byte2, Byte3]; 


  //this is just used for testing if the vector is indeed correct
  for(int i = 0; i < 3; i++)
  {
    Serial.println(myArray[i]);
  }

  }
}

