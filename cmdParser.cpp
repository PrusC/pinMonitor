/*
 * cmdParser.c
 *
 *  Created on: 17 мар. 2020 г.
 *      Author: kPrusakov
 */


#include "cmdParser.h"

#define CMD_BEGIN '$'
#define CMD_DELIMITER ';'
#define CMD_END 0x0D
#define CMD_TITTLE_LENGTH 2
#define CMD_DATA_LENGTH 30

uint16_t flag_cmd = 0;
uint16_t rXcnt = 0;
uint8_t cmd_ready = 0;
uint8_t cmd_params_cnt = 0;

cmd CMD = configureCMD();

cmd configureCMD() {
	cmd ans;
	ans.title = (char*)malloc(CMD_TITTLE_LENGTH*sizeof(char));
	ans.data = (char*)malloc(CMD_DATA_LENGTH*sizeof(char));
	memset(ans.title, 0, sizeof(char)*CMD_TITTLE_LENGTH);
	memset(ans.data, 0, sizeof(char)*CMD_DATA_LENGTH);
	ans.data_cnt = 0;
	return ans;
}


void initializeCMD() {
	memset(CMD.title, 0, sizeof(char)*CMD_TITTLE_LENGTH);
	memset(CMD.data, 0, sizeof(char)*CMD_DATA_LENGTH);
	CMD.data_cnt = 0;
}


void parseCmd(char c) {
	if(!cmd_ready) {
		switch(flag_cmd) {
			case 0:
				if(c == CMD_BEGIN) {
					flag_cmd = 1;
					rXcnt = 0;
					initializeCMD();
				}
				break;

			case 1:
				if(rXcnt >= CMD_TITTLE_LENGTH || c == CMD_DELIMITER) {
					flag_cmd = 2;
					if(rXcnt < CMD_DATA_LENGTH-1) {
						CMD.title[rXcnt] = 0;
					}
					rXcnt = 0;
				} else {
					CMD.title[rXcnt] = c;
					rXcnt ++;
				}
				break;

			case 2:
				if(c == CMD_END) {
					if(rXcnt > 0 && CMD.data_cnt == 0) {
						CMD.data_cnt ++;
					}
					CMD.data[rXcnt] = 0;
					cmd_ready = 1;
					flag_cmd = 0;
					rXcnt = 0;
				} else {
					if(c == CMD_DELIMITER && rXcnt == 0) {
						break;
					}
					if(c == CMD_DELIMITER) {
						CMD.data_cnt ++;
						CMD.data[rXcnt] = 0;
					} else {
						CMD.data[rXcnt] = c;
					}
					rXcnt ++;
				}
				break;
		}
	}
}


void parseCmd(char *buffer, uint16_t buffer_size) {
	uint8_t res = 0;
	for(uint16_t i = 0; i < buffer_size; i ++) {
		parseCmd(buffer[i]);
	}
}


bool cmdTittleCmp(cmd *command, char *s) {
	if(strcmp(command->title, s) == 0) {
		return true;
	}
	return false;
}


bool cmdTittleCmp(char *s) {
	if(cmd_ready) {
		return cmdTittleCmp(&CMD, s);
	}
	return false;
}


char* getParam(cmd* command, uint8_t param_number) {
	uint8_t cnt = 0;
	bool found = false;
	if(command->data_cnt < param_number) {
		return NULL;
	}
	char *ps = command->data;

	for(uint8_t i = 0; i < CMD_DATA_LENGTH; i ++) {
		if (i > 0 && ps[i] == 0 && ps[i - 1] != 0) {
			cnt++;
		}
		if (cnt == param_number && ps[i] != 0x00) {
			return (char *)(&ps[i]);
		}
	}
	return NULL;
}


char* getParam(uint8_t param_number) {
	if(cmd_ready) {
		return getParam(&CMD, param_number);
	}
	return NULL;
}


char* getUID(cmd* command) {
	return getParam(command, 0);
}


char* getUID() {
	return getParam(0);
}

