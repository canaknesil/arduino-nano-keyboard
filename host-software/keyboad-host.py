import serial
from serial.tools.list_ports import comports
import sys
import time
import pynput.keyboard as kb
import os
from keycode import hid_to_key

#
# KEYBOARD KEY INVOCATION
#

def get_key_name(keycode):
    return "keyname" # TODO

#
# DEVICE CONNECTION
#

def get_port(product_id, vendor_id):
    devices = list(filter(lambda d: d.pid == product_id and d.vid == vendor_id,
                          comports()))
    if len(devices) != 1:
        return None
    return devices[0].device

def blocking_connect_to_port(product_id, vendor_id):
    print("Waiting for device with product ID %d and vendor ID %d to connect..." % (product_id, vendor_id))
    while True:
        port = get_port(product_id, vendor_id)
        if port != None:
            try:
                ser = serial.Serial(port)
                print("Connected to port " + port)
                return ser
            except serial.SerialException:
                pass
            print("Unsuccessfull connection to port " + port)
        time.sleep(1)

#
# COMMAND_LOOP
#
        
def read_char(ser):
    return str(ser.read().decode("utf-8"))

def read_int(ser):
    return int.from_bytes(ser.read(), byteorder="little")
            
def command_loop(ser):
    print("Listening device ...")
    while True:
        command = read_char(ser)
        if command == 'p': # Print for debugging
            print("Device print: ", end="")
            c = read_char(ser)
            while c != '\0':
                print(c, end="")
                c = read_char(ser)
            print()
        elif command == 'k':
            pressed = True if read_int(ser) != 0 else False
            keycode = read_int(ser)
            key = hid_to_key(keycode)
            if pressed:
                print("Pressed  %s (keycode = %d)" % (str(key), keycode))
            else:
                print("Released %s (keycode = %d)" % (str(key), keycode))
        else:
            print("Unknown command", command)

#
# MAIN
#

def main():
    config_file = os.path.dirname(os.path.realpath(__file__)) + "/identified-device"
    if not os.path.exists(config_file):
        print("Device is not identified.")
        print("Run identify-device.py to identify the device.")
        sys.exit()

    with open(config_file) as f:
        lines = f.readlines()
    product_id = int(lines[0])
    vendor_id = int(lines[1])

    while True:
        ser = blocking_connect_to_port(product_id, vendor_id)
        
        try:
            command_loop(ser)
        except serial.SerialException:
            continue
    
main()


