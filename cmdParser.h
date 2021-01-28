/*
 * cmdParser.h
 *
 *  Created on: 17 мар. 2020 г.
 *      Author: Konstantin Prusakov
 */

#ifndef CMDPARSER_H_
#define CMDPARSER_H_

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define CMD_BEGIN '/'
#define CMD_DELIMITER ';'
#define CMD_END 0x0D
#define CMD_TITTLE_LENGTH 2
#define CMD_DATA_LENGTH 30

typedef struct cmd {
	char *title;
	char *data;
	uint8_t data_cnt;
} cmd;

extern cmd CMD;
extern uint8_t cmd_ready;

cmd configureCMD();

void parseCmd(char c);
void parseCmd(char *buffer, uint16_t buffer_size);

bool cmdTittleCmp(cmd *command, char *s);
bool cmdTittleCmp(char *s);

char* getParam(cmd* command, uint8_t param_number);
char* getParam(uint8_t param_number);

char* getUID(cmd* command);
char* getUID();

#endif /* CMDPARSER_H_ */
