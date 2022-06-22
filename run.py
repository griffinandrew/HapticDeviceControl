import subprocess
import multiprocessing 
from multiprocessing import Pool
import os 
import threading 


haptic = ("C:\\OpenHaptics\\Developer\\3.5.0\\Quickhaptics\\examples\\Debug\\pickApplesGLUT.exe")

f2p= ("//ad/eng/users/g/h/gheyrich/Desktop/file_to_arduino.py")


def run():
    #p1 = subprocess.Popen(["C:\\OpenHaptics\\Developer\\3.5.0\\Quickhaptics\\examples\\Debug\\pickApplesGLUT.exe"])
    p2 = subprocess.Popen("//ad/eng/users/g/h/gheyrich/Desktop/file_to_arduino.py & C:\\OpenHaptics\\Developer\\3.5.0\\Quickhaptics\\examples\\Debug\\pickApplesGLUT.exe")

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
        p2.start()
        
        
 def exec1():
    os.system("//ad/eng/users/g/h/gheyrich/Desktop/file_to_arduino.py")
    
 def exec2():
    os.system("C:\\OpenHaptics\\Developer\\3.5.0\\Quickhaptics\\examples\\Debug\\pickApplesGLUT.exe")
    
def run_thread():
    t1 = threading.Thread(target=exe1, args=()) 
    t2 = threading.Thread(target=exe2, args=()) 
    t1.start()
    t2.start() 
    

if __name__ == '__main__':
    run_thread()
    #run_mult_proc()

    
    
