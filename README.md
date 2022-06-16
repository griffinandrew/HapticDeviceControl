# HapticDeviceController


## Abstract ##
This repo contains the code to use the quickhaptics phantom omni as a surgerical controller for mapping the coordinates of a spherical 3D interface. The user interacts with the interface using the phatom omni cursor to map its position to the appraopriate volume on a 0-100 scale creating movements in the robot using the 3 pumps. The pumps are controlled by an ardiuno uno controller. 

## main.cpp 

This is the C++ code that creates and launches the user interface using the quickhaptics api. A servoloop callback is used to get the call get the positon vector of the cursor. The positon vector is processed and broken down into its components and sent to "position1.txt", this is cleared each time before being appended to in order so that only 3 values at a time will be in the file for reading

## file2arduino.py

This python code is used due to the inability to open the serial communciaton port on two console apps at the same time, resulting in the usage of the before mentioned file technique. This file uses pyfirmata to communicate with the arduino, reading in each position and sending it to the ardiuno for processesing by the pumps and being displayed by the lcd screen. 

#### ldek
