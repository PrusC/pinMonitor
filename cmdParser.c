/*
 * cmdParser.c
 *
 *  Created on: 15 мар. 2020 г.
 *      Author: Konstantin
 */

#include "cmdParser.h"

#define CMD_UID_LENGTH 4
#define CMD_PARAMETERS_LENGTH 4

uint16_t flag_cmd = 0;
uint16_t rXcnt = 0;
uint8_t cmd_ready = 0;

cmd_config CONFIG;
cmd CMD = configureCMD(CONFIG);


void parseCmd(char c) {
	switch(flag_cmd) {
	case 0:
		if(c == CONFIG.CMD_BEGIN) {
			flag_cmd = 1;
			rXcnt = 0;
		}
		break;

	case 1:
		if(rXcnt >= CONFIG.CMD_LENGTH || c == CONFIG.CMD_DELIMITER) {
			flag_cmd ++;
//			CMD.title[rXcnt] = 0;
			rXcnt = 0;
		} else {
			CMD.title[rXcnt] = c;
			rXcnt ++;
		}
		break;

	case 2:
		if(CONFIG.IS_UID) {
			if(rXcnt > CMD_UID_LENGTH || c == CONFIG.CMD_DELIMITER) {
				flag_cmd ++;
				rXcnt = 0;
			} else {
				if(c == CONFIG.CMD_END) {
					cmd_ready = 1;
					flag_cmd = 0;
					rXcnt = 0;
				}
				CMD.uid[rXcnt] = c;
				rXcnt ++;
			}
		} else {
			flag_cmd ++;
		}
		break;

	case 3:
		if(c == CONFIG.CMD_END) {
			cmd_ready = 1;
			flag_cmd = 0;
			rXcnt = 0;
		}

		break;
	}
}


void parseCmd(char *buffer, uint16_t buffer_size) {
	for(uint16_t i = 0; i < buffer_size; i ++) {
		parseCmd(buffer[i]);
	}
}

cmd configureCMD(cmd_config config) {
	cmd ans;
	memset(ans.title, 0, sizeof(char)*config.CMD_LENGTH);
	if(config.IS_UID) {
		memset(ans.uid, 0, sizeof(char)*CMD_UID_LENGTH);
	} else {
		ans.uid = NULL;
	}
	ans.data = (char**)malloc(config.PARAMETERS_COUNT);
	for(int i = 0; i < config.PARAMETERS_COUNT; i ++) {
		memset(ans.data[i], 0, sizeof(char)*CMD_PARAMETERS_LENGTH);
	}
	return ans;
}
