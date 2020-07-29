import serial
import sys
import time

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
            
def command_loop(ser):
    while True:
        print("Listening device ...")
        command = read_char(ser)
        print("Command " + str(command))
        if command == 'p': # Print for debugging
            print("Device print: ", end="")
            c = read_char(ser)
            while c != '\0':
                print(c, end="")
                c = read_char(ser)
            print()
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


