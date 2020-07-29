#include "platform_dependent.h"
#include "keyboard.h"

#define DEBUG_MSG_SIZE_MAX 256

/*
 * Platform dependent functions
 */

void dprint(char *str, ...)
{
	static char msg[DEBUG_MSG_SIZE_MAX];
	va_list args;
	
	str[DEBUG_MSG_SIZE_MAX - 1] = '\0'; // Chop str.
	
	va_start(args, str);
	vsprintf(msg, str, args);
	va_end(args);
	
	Serial.write('p');
	Serial.print(msg);
	Serial.write('\0');
}


/* 
 * Arduino main
 */

void setup() {
	Serial.begin(9600);
	dprint("Initialized.");
}

void loop() {
	do_smt();
	delay(5000);
}
