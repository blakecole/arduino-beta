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
    # open logfile, write header row
    fname = r"/home/pi/arduino/flowSensor/flow.log"
    header = "timestamp,flow_rate,total_volume \n"
    logfile = open(fname, "w")
    logfile.write(header)
    logfile.close()
    
    # initiate serial reading, flush buffer
    s = serial.Serial('/dev/ttyACM0', baudrate=9600, timeout=1)
    s.flush()

    logging = True

    while logging:
        try:
            if (s.in_waiting > 0):
                current_time = time.strftime("%Y-%m-%d %H:%M:%S")

                # parse payload
                payload = s.readline().decode('utf-8').strip()
                msg = dict(item.split("=") for item in payload.split(","))
                line = current_time + "," + ','.join(map(str, msg.values()))
                print(line)

                # save csv line to file
                logfile = open(fname, "a")
                logfile.write(line + "\n")
                logfile.close()

        except KeyboardInterrupt:
            print("\n")
            print("[data logging stopped by user]\n");
            logging = False
            logfile.close()


