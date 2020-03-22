#include <Arduino.h>
#include "cmdParser.h"

void setup() {
	Serial.begin(9600);
}

void loop() {

}

//extern cmd CMD;

void serialEvent() {
	char c = Serial.read();
	parseCmd(c);

	if(cmd_ready) {
		Serial.println(CMD.title);
		Serial.println(getParam(0));
		Serial.println(getParam(1));
		Serial.println(getParam(2));
		Serial.println(getParam(4));
		cmd_ready = 0;
	}

}
