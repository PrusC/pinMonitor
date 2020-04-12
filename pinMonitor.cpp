#include <Arduino.h>

#include "pinMonitor.h"

void setup() {
	Serial.begin(9600);
}


void loop() {
	if(cmd_ready) {
		executeCMD(&CMD);
	}
}


void serialEvent() {
	char c = Serial.read();
	parseCmd(c);
}
