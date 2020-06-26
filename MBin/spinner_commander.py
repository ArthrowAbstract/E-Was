import serial
import time
import sys

arduino=serial.Serial('com5',9600)   ### write the correct com port before running

time.sleep(2)

while 1:
    with open("class.txt") as file:
    	var=file.read()
    if var=="exit":
        break
    elif var == "glass":
    	angle = 45
    elif var == "plastic":
    	angle = 90
    elif var == "metal":
    	angle = 135
    arduino.write(angle.encode())

sys.exit(0)
