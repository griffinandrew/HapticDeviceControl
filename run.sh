#!/bin/bash

python3 -c "import time, pyfirmata, code; code.interact(local=locals())" // ng

/mnt/c/OpenHaptics/Developer/3.5.0/Quickhaptics/examples/Debug/file_to_arduino.py &
/mnt/c/OpenHaptics/Developer/3.5.0/Quickhaptics/examples/Debug/pickApplesGLUT.exe && fg

#!/bin/python
import time
import pyfirmata
/mnt/c/OpenHaptics/Developer/3.5.0/Quickhaptics/examples/Debug/file_to_arduino.py &

#lol wait i think that I can just create an executable of the python file and then just have them both run concurrently from the script


#the python exec is failing to connect to com port and also load other modules within the envi 




#https://stackoverflow.com/questions/32093559/exe-file-created-by-pyinstaller-not-find-self-defined-modules-while-running?answertab=trending#tab-top
#
#basically the internet is saying need to specify paths of the included modules


pyi-makespec --paths=/path/to/thisdir \
             --paths=/path/to/otherdir myscript.py
             
pyi_makespec --paths =



pyinstaller --noconfirm --onedir --console --add-data "/Users/gheyrich/Documents/Hw 9 ma581 use this one.pdf:." --add-data "/Users/gheyrich/Documents/ma213 hw 6.pdf:."  "/Users/gheyrich/Documents/HW 8 MA581.pdf"
