#************************************************************#
#*    NAME: Blake Cole                                      *#
#*    ORGN: hydrocycle                                      *#
#*    FILE: serial_arduino.py                               *#
#*    DATE: 06 MARCH 2021                                   *#
#************************************************************#

# SERIAL_ARDUINO appends serial data to a text file

#adapted from:
# Eli The Computer Guy
# "Arduino – Read Serial Communication with Raspberry Pi"
# <https://www.elithecomputerguy.com/>

import serial
import time

if __name__ == '__main__':
    # specify filename and path for logfile
    fname = r"/home/pi/arduino/flowSensor/flow.log"

    # initiate serial reading, flush buffer
    s = serial.Serial('/dev/ttyACM0', baudrate=9600, timeout=1)
    s.flush()

    while True:
        if s.in_waiting > 0:
            payload = s.readline().decode('utf-8').rstrip()
            current_time = time.strftime("%Y-%m-%d %H:%M:%S")
            line = "TIME=" + current_time + "," + payload
            print(line)
            logfile = open(fname, "a")
            logfile.write(line + "\n")
            logfile.close()
