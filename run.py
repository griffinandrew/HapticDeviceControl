#Griffin Heyrich
#June 2022
#BU_MBL
#the purpose of this segment of code is to get rid of the need to run both main.cpp and file_2_ardiuno.py from each respective enviornment and instead
#have just one script that activates both with 1 click

import subprocess
import multiprocessing 
from multiprocessing import Pool
import os 
import threading 
import file2arduino
 

haptic = "C:\\OpenHaptics\\Developer\\3.5.0\\Quickhaptics\\examples\\Debug\\pickApplesGLUT.exe"

f2p= "//ad/eng/users/g/h/gheyrich/Desktop/file_to_arduino.py"


def run():
    #p1 = subprocess.Popen(["C:\\OpenHaptics\\Developer\\3.5.0\\Quickhaptics\\examples\\Debug\\pickApplesGLUT.exe"])
    p2 = subprocess.call(['python.exe','//ad/eng/users/g/h/gheyrich/Desktop/file_to_arduino.py', 'C:\\OpenHaptics\\Developer\\3.5.0\\Quickhaptics\\examples\\Debug\\pickApplesGLUT.exe'])

   # subprocess.run("python3 fi.py & python3 script2.py", shell=True)

def run_os():
    #os.system("C:\\OpenHaptics\\Developer\\3.5.0\\Quickhaptics\\examples\\Debug\\pickApplesGLUT.exe")
    #exec(open("file_to_arduino.py").read())
    os.system("//ad/eng/users/g/h/gheyrich/Desktop/file_to_arduino.py && C:\\OpenHaptics\\Developer\\3.5.0\\Quickhaptics\\examples\\Debug\\pickApplesGLUT.exe") #this is def making them both run 
    #os.system("C:\\OpenHaptics\\Developer\\3.5.0\\Quickhaptics\\examples\\Debug\\pickApplesGLUT.exe &")

def run_mult_proc():
        p1 = multiprocessing.Process(target=exec1, args=())
        p2 = multiprocessing.Process(target=exec2, args=())    

        p1.start()
        #p2.start()
        
        
def exec1():
    os.system("//ad/eng/users/g/h/gheyrich/Desktop/file_to_arduino.py")
    
def exec2():
    os.system("C:\\OpenHaptics\\Developer\\3.5.0\\Quickhaptics\\examples\\Debug\\pickApplesGLUT.exe")
    
def run_thread():
    t1 = threading.Thread(target=exec1, args=()) 
    t2 = threading.Thread(target=exec2, args=()) 
    t1.start()
    #t2.start() 

def exec3():
    file2arduino.main()

def run_module():
    t1 = threading.Thread(target=exec2, args= ())
    t2 = threading.Thread(target=exec3, args=())
    t1.start()
    t2.start()

    #p2 = multiprocessing.Process(target=exec2, args=()) 
    #p2.start()  

    #os.system("C:\\OpenHaptics\\Developer\\3.5.0\\Quickhaptics\\examples\\Debug\\pickApplesGLUT.exe")


    #file2arduino.main()
    #exec2()
    

if __name__ == '__main__':
    #run_thread()
    #run_mult_proc()
    #run_module()
    run()
