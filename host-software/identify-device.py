from serial.tools.list_ports import comports
import sys
import os

devices = comports()
n = len(devices)

if n == 0:
    print("No device found.")
    sys.exit()

print("Detected devices:\n")    
for i, dev in enumerate(devices):
    print("% d) %s" % (i+1, dev.device))
idx = int(input("\nEnter device number 1-%d (0 to cancel): " % n))
if idx == 0:
    sys.exit()
selected = devices[idx - 1]

if not isinstance(selected.pid, int):
    print("Invalid Product ID: " + str(selected.pid))
    sys.exit()
if not isinstance(selected.vid, int):
    print("Invalid Vendor ID: " + str(selected.vid))
    sys.exit()

config_file = os.path.dirname(os.path.realpath(__file__)) + "/identified-device"
print("Writing configuration file " + config_file)
with open(config_file, "w") as f:
    print("Product ID:", selected.pid)
    print("Vendor ID :", selected.vid)
    f.write(str(selected.pid) + "\n") # Product ID
    f.write(str(selected.vid) + "\n") # Vendor ID




