FQBN := arduino:avr:nano:cpu=atmega328old
SKETCH_NAME := keyboard-firmware
PORT := /dev/ttyUSB0

.PHONY: compile upload
all: compile

compile:	
	arduino-cli compile --fqbn $(FQBN) $(SKETCH_NAME)

upload:
	arduino-cli upload -p $(PORT) --fqbn $(FQBN) $(SKETCH_NAME)
