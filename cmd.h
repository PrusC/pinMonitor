/*
 * cmd.h
 *
 *  Created on: 22 мар. 2020 г.
 *      Author: Konstantin
 */

#ifndef CMD_H_
#define CMD_H_

#include "cmdParser.h"

#define SET_MODE "SM"
#define SET_DIGITAL "SD"
#define GET_DIGITAL "GD"
#define SET_ANALOG "SA"
#define GET_ANALOG "GA"

void executeCMD(cmd* command);
void sendResult(cmd* command, char* res);
void sendResult(cmd* command, int ans);
void setPinMode(cmd* command);
void setDigital(cmd* command);
void getDigital(cmd* command);
void setAnalog(cmd* command);
void getAnalog(cmd* command);


#endif /* CMD_H_ */
