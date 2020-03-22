/*
 * cmd.cpp
 *
 *  Created on: 22 мар. 2020 г.
 *      Author: Konstantin
 */

#include "cmd.h"
#include <Arduino.h>

void executeCMD(cmd* command) {
	char *tittle = command->title;
	if(strcmp(tittle, SET_MODE) == 0) {
		setPinMode(command);
	}
	else if(strcmp(tittle, SET_DIGITAL) == 0) {
		setDigital(command);
	}
	else if(strcmp(tittle, GET_DIGITAL) == 0) {
		getDigital(command);
	}
	else if(strcmp(tittle, SET_ANALOG) == 0) {
		setAnalog(command);
	}
	else if(strcmp(tittle, GET_ANALOG) == 0) {
		getAnalog(command);
	}
	else {
		sendResult(command, "Unknown command");
	}
	cmd_ready = 0;
}

void sendResult(cmd* command, char* res) {
	if(Serial) {
		Serial.print("answer: ");
		Serial.print(res);
		Serial.print('\n');
	}
}
void sendResult(cmd* command, int res) {
	if(Serial) {
		Serial.print("answer: ");
		Serial.print(res);
		Serial.print('\n');
	}
}

void setPinMode(cmd* command) {
	int pin;
	int value;
	char *uid = getUID(command);
	char *param = getParam(command, 1);
	if(uid == NULL || param == NULL) {
		sendResult(command, "Unknown uid or parameter value");
		return;
	} else {
		pin = atoi(uid);
		value = atoi(param);
		if (pin > 13 || pin < 2) {
			sendResult(command, "Wrong pin number");
			return;
		}
		if(value > 1 || value < 0) {
			sendResult(command, "Wrong pin mode");
			return;
		}

		if (value == 1)
			pinMode(pin, OUTPUT);
		else if(value == 0)
			pinMode(pin, INPUT);

		sendResult(command, "OK");
	}
}

void setDigital(cmd* command) {
	int pin;
	int value;
	char *uid = getUID(command);
	char *param = getParam(command, 1);
	if(uid == NULL || param == NULL) {
		sendResult(command, "Unknown uid or parameter value");
		return;
	} else {
		pin = atoi(uid);
		value = atoi(param);
		if (pin > 13 || pin < 2) {
			sendResult(command, "Wrong pin number");
			return;
		}
		if(value > 1 || value < 0) {
			sendResult(command, "Wrong digital value");
			return;
		}

		if (value == 1)
			digitalWrite(pin, HIGH);
		else if(value == 0)
			digitalWrite(pin, LOW);

		sendResult(command, "OK");
	}
}
void getDigital(cmd* command) {
	int pin;
	char *uid = getUID(command);
	if(uid == NULL) {
		sendResult(command, "Unknown uid value");
		return;
	} else {
		pin = atoi(uid);
		if (pin > 13 || pin < 2) {
			sendResult(command, "Wrong pin number");
			return;
		}
		int val = digitalRead(pin);
		sendResult(command, val);
	}
}

void setAnalog(cmd* command) {
	int pin;
	int value;
	char *uid = getUID(command);
	char *param = getParam(command, 1);
	if(uid == NULL || param == NULL) {
		sendResult(command, "Unknown uid or parameter value");
		return;
	} else {
		pin = atoi(uid);
		value = atoi(param);
		if (pin > 5 || pin < 0) {
			sendResult(command, "Wrong pin number");
			return;
		}
		if(value > 4095 || value < 0) {
			sendResult(command, "Wrong analog value");
			return;
		}
		analogWrite(pin, value);
		sendResult(command, "OK");
	}
}

void getAnalog(cmd* command) {
	int pin;
	char *uid = getUID(command);
	if(uid == NULL) {
		sendResult(command, "Unknown uid value");
		return;
	} else {
		pin = atoi(uid);
		if (pin > 5 || pin < 0) {
			sendResult(command, "Wrong pin number");
			return;
		}
		int val = analogRead(pin);
		sendResult(command, val);
	}
}



