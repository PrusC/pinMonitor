/*
 * cmdParser.c
 *
 *  Created on: 17 мар. 2020 г.
 *      Author: kPrusakov
 */


#include "cmdParser.h"

uint16_t flag_cmd = 0;
uint16_t rXcnt = 0;
uint8_t cmd_ready = 0;

cmd_config CONFIG;
cmd CMD = configureCMD(&CONFIG);

void parseCmd(char c) {
	if(!cmd_ready) {
		switch(flag_cmd) {
			case 0:
				if(c == CONFIG.CMD_BEGIN) {
					flag_cmd = 1;
					rXcnt = 0;
				}
				break;

			case 1:
				if(rXcnt >= CONFIG.CMD_LENGTH || c == CONFIG.CMD_DELIMITER) {
					flag_cmd = 2;
					if(rXcnt < CONFIG.CMD_LENGTH-1) {
						CMD.title[rXcnt] = 0;
					}
					rXcnt = 0;
				} else {
					CMD.title[rXcnt] = c;
					rXcnt ++;
				}
				break;

			case 2:
				if(c == CONFIG.CMD_END) {
					CMD.data[rXcnt] = c;
					cmd_ready = 1;
					flag_cmd = 0;
					rXcnt = 0;
				} else {
					CMD.data[rXcnt] = c;
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

cmd configureCMD(cmd_config* config) {
	cmd ans;
	ans.title = (char*)malloc((config->CMD_LENGTH)*sizeof(char));
	ans.data = (char*)malloc((config->DATA_LENGTH)*sizeof(char));
	memset(ans.title, 0, sizeof(char)*config->CMD_LENGTH);
	memset(ans.data, 0, sizeof(char)*config->DATA_LENGTH);
	return ans;
}
