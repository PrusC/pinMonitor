#include <Arduino.h>
#include "cmdParser.h"

void setup() {
	Serial.begin(9600);
}

void loop() {

}

extern cmd CMD;

void serialEvent() {
	char c = Serial.read();
	parseCmd(c);

	if(cmd_ready) {
		Serial.println(CMD.title);
		Serial.println(CMD.data);
		cmd_ready = 0;
	}

}
