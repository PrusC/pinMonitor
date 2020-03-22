/*
 * cmd.h
 *
 *  Created on: 22 мар. 2020 г.
 *      Author: Konstantin
 */

#ifndef CMD_H_
#define CMD_H_

//#define D0 0 //RX
//#define D1 1 //TX
//#define D2 2
//#define D3 3
//#define D4 4
//#define D6 6
//#define D7 7
//#define D8 8
//#define D9 9
//#define D10 10
//#define D11 11
//#define D12 12
//#define D13 13

//#define A0 0
//#define A1 1
//#define A2 2
//#define A3 3
//#define A4 4

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
