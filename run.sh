#!/bin/bash

python3 -m pip install time
python3 -m pip install pyfirmata

python3 -c "import time, pyfirmata, code; code.interact(local=locals())"

mnt/c/OpenHaptics/Developer/3.5.0/Quickhaptics/examples/Debug/file_to_arduino.py &
mnt/c/OpenHaptics/Developer/3.5.0/Quickhaptics/examples/Debug/pickApplesGLUT.exe && fg

#!/bin/python
import time
import pyfirmata
mnt/c/OpenHaptics/Developer/3.5.0/Quickhaptics/examples/Debug/file_to_arduino.py &






#lol wait i think that I can just create an executable of the python file and then just have them both run concurrently from the script
