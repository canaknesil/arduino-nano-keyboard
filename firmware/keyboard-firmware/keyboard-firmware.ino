#include "platform_dependent.h"
#include "keyboard.h"

#define DEBUG_MSG_SIZE_MAX 256

/*
 * Platform dependent
 */

int row_pins[ROWS] = {A0, A1, A2, A3, A4, A5};
int col_pins[COLS] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

void d_print(char *str, ...)
{
	static char msg[DEBUG_MSG_SIZE_MAX];
	va_list args;

	if (strlen(str) > DEBUG_MSG_SIZE_MAX - 1)
		str[DEBUG_MSG_SIZE_MAX - 1] = '\0'; // Chop str.
	
	va_start(args, str);
	vsprintf(msg, str, args);
	va_end(args);
	
	Serial.write('p');
	Serial.print(msg);
	Serial.write('\0');
}

void d_delay(unsigned long ms)
{
	delay(ms);
}

char d_read_pin(int pin)
{
	if (pin >= A0 && pin <= A5) {
		int val = analogRead(pin);
		if (val > 950)
			return 1;
		else
			return 0;
	} else {
		int val = digitalRead(pin);
		if (val == HIGH)
			return 1;
		else
			return 0;
	}
}

void d_write_pin(int pin, char val)
{
	if (val)
		digitalWrite(pin, HIGH);
	else
		digitalWrite(pin, LOW);
}

void d_send_keycode(KeyCode key, char pressed)
{
	Serial.write('k');
	Serial.write(pressed);
	Serial.write(&key, sizeof(KeyCode));
}

/* 
 * Arduino main
 */

void print_pin_info()
{
	d_print("Pin info:");
	for (int i=0; i<ROWS; i++)
		d_print("Row %d -> %d", i, row_pins[i]);
	for (int i=0; i<COLS; i++)
		d_print("Col %d -> %d", i, col_pins[i]);
}

void prepare_pins()
{
	for (int i=0; i<ROWS; i++)
		pinMode(row_pins[i], INPUT);
	for (int i=0; i<COLS; i++) {
		pinMode(col_pins[i], OUTPUT);
		digitalWrite(col_pins[i], LOW);
	}
}

void setup() {
	Serial.begin(9600);
	prepare_pins();

	d_print("Initialized.");
	//print_pin_info();

	// Debug
	//d_write_pin(col_pins[1], HIGH);
}

void loop() {
	keyboard_loop();
}
