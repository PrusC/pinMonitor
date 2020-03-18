/*
 * cmdParser.h
 *
 *  Created on: 17 мар. 2020 г.
 *      Author: kPrusakov
 */

#ifndef CMDPARSER_H_
#define CMDPARSER_H_

#include <stdint.h>
#include <string.h>

typedef struct cmd_config {
	char CMD_BEGIN = '$';
	char CMD_DELIMITER = ';';
	char CMD_END = 0x0D;
	uint8_t CMD_LENGTH = 2;
	uint8_t DATA_LENGTH = 30;
} cmd_config;

typedef struct cmd {
	char *title;
	char *data;
} cmd;

extern cmd CMD;
extern uint8_t cmd_ready;

void parseCmd(char c);
void parseCmd(char *buffer, uint16_t buffer_size);
cmd configureCMD(cmd_config* config);

#endif /* CMDPARSER_H_ */
