#!/user/bin/env python
import time
import pyfirmata
from pyfirmata import util, STRING_DATA

board = pyfirmata.Arduino("COM7")
1
def read_file(): 
    #open the file and write to arduino
    f = open("C:\\OpenHaptics\\Developer\\3.5.0\\Quickhaptics\\examples\\pickApples\\pickApplesGLUT\\positions1.txt", "r", encoding ='utf-8') 

    if(f):
        k =  f.read()
        board.send_sysex(STRING_DATA, util.str_to_two_byte_iter(k)) #sends the str
        print(k)
def main():
    while(1):
        read_file()

if __name__ == "__main__":
    main()
    print("connection success")
