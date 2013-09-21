/* 
 * File:   commands.h
 * Author: tiggr
 *
 * Created on 3. April 2013, 14:33
 */

#include <stdint.h>
#include "extern/SerialCommand.h"
#include "configuration.h"
#include "def.h"

#ifndef COMMANDS_H
#define	COMMANDS_H

extern SerialCommand SerialShell;
extern int8_t submode;

void ToggleLED();
void Show();
void Echo();
void Write();

void NoOp();
void UnknownCommand(const char *command);


#endif	/* COMMANDS_H */

