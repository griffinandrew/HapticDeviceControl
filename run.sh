#!/bin/bash

python -m pip install time
python -m pip install pyfirmata

python3 -c "import time, pyfirmata, code; code.interact(local=locals())"

mnt/c/OpenHaptics/Developer/3.5.0/Quickhaptics/examples/Debug/file_to_arduino.py &
mnt/c/OpenHaptics/Developer/3.5.0/Quickhaptics/examples/Debug/pickApplesGLUT.exe && fg
