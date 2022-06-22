import subprocess
import multiprocessing 
from multiprocessing import Pool
import os 



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
        p1 = multiprocessing.Process(target="//ad/eng/users/g/h/gheyrich/Desktop/file_to_arduino.py")
        p2 = multiprocessing.Process(target="C:\\OpenHaptics\\Developer\\3.5.0\\Quickhaptics\\examples\\Debug\\pickApplesGLUT.exe")    

        p1.start()
        p2.start()


if __name__ == '__main__':
    run_mult_proc()
