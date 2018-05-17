import serial
import time


anus = ["L(1000,0,0);", "L(1000,1000,0);", "L(1000,1000,100);", "L(1000,1000,0);", "L(0,0,0);"]

commands = []


with open("code.txt", 'r') as infile:
    lines = infile.readlines()
    for line in lines:
        commands.append(line.split(';'))

ser = serial.Serial(
    port='COM4',\
    baudrate=115200,\
    parity=serial.PARITY_NONE,\
    stopbits=serial.STOPBITS_ONE,\
    bytesize=serial.EIGHTBITS,\
    timeout=0)
i = 0
ser.close()
ser.open()
print(ser.name)         # check which port was really used

while True:
    reading = ser.readline()
    if reading:
        print(reading)
    if reading == b'R\n':
        if commands[0][i]:
            ser.write((commands[0][i] + ';').encode('utf-8'))
            ser.flush()
        i += 1

ser.close()             # close port
