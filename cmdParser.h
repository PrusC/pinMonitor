/*
 * cmdParser.h
 *
 *  Created on: 15 мар. 2020 г.
 *      Author: Konstantin
 */

#ifndef CMDPARSER_H_
#define CMDPARSER_H_

#include <stdint.h>
#include <string.h>

#define D0 0 //Serial Rx
#define D1 1 //Serial Tx

#define D2 2
#define D3 3
#define D4 4
#define D5 5
#define D6 6
#define D7 7
#define D8 8
#define D9 9
#define D10 10
#define D11 11
#define D12 12
#define D13 13

#define A0 0
#define A1 1
#define A2 2
#define A3 3
#define A4 4
#define A5 5

typedef struct cmd_config {
	char CMD_BEGIN = '$';
	char CMD_DELIMITER = ';';
	char CMD_END = 0x0D;
	uint8_t PARAMETERS_COUNT = 1;
	uint8_t CMD_LENGTH = 2;
	uint8_t IS_UID = 1;
} cmd_config;

typedef struct cmd {
	char *type;
	char *uid;
	char **data;
} cmd;


extern char *cmd_tx;

void parseCmd(char c);

void parseCmd(char *buffer, uint16_t buffer_size);

cmd configureCMD(cmd_config config);


#endif /* CMDPARSER_H_ */
