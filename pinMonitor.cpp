#include <Arduino.h>
#include "cmdParser.h"

void setup() {
	Serial.begin(9600);
}

void loop() {

}

void serialEvent() {
	char c = Serial.read();
	Serial.print(c);
	parseCmd(c);
	if(cmd_ready) {
		Serial.write(CMD.title);
		Serial.print(CMD.data);
		cmd_ready = 0;
	}

}
