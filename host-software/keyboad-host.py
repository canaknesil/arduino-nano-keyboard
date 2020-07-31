import serial
import sys
import time
import pynput.keyboard as kb

def get_key_name(keycode):
    return "keyname" # TODO

def blocking_connect_to_port(port):
    while True:
        try:
            ser = serial.Serial(port)
            return ser
        except serial.SerialException:
            print("Unsuccessfull connection to port " + port)
            time.sleep(1)

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
            keyname = get_key_name(keycode)
            if pressed:
                print("Pressed %s (%d)" % (keyname, keycode))
            else:
                print("Released %s (%d)" % (keyname, keycode))
        else:
            print("Unknown command", command)


def main():
    port = sys.argv[1]
    print("port: " + port)

    while True:
        ser = blocking_connect_to_port(port)
        print("Connected to port " + ser.name)
        
        try:
            command_loop(ser)
        except serial.SerialException:
            continue
    
main()


