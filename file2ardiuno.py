import time
import pyfirmata
from pyfirmata import Arduino, util, STRING_DATA


def read_file(): 
    #open the file and write to arduino
    f = open("C:\\OpenHaptics\\Developer\\3.5.0\\Quickhaptics\\examples\\pickApples\\pickApplesGLUT\\positions1.txt", "r", encoding ='utf-8') 

    if(f): #if file open
        print("reading")
        k =  f.read()
        board.send_sysex(STRING_DATA, util.str_to_two_byte_iter(k)) #sends the str
        print(k)
        time.sleep(0.1) #sends item every .1 seconds to file for read 

def main():
    while(1):
        read_file()

if __name__ == "__main__":
    main()
    board = pyfirmata.Arduino('COM3')
    print("connection success")
