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

void ToggleLED();
void Show();
void Echo();
void Write();
void Version();
void Pause();
void Shoot();
void Shootpause();
void Pan();
void Panspeed();
void Neutral();
void Tilt();
void Step();
void Reset();

void NoOp();
void UnknownCommand(const char *command);


void _setValue(char *cmd, int16_t &config);


#endif	/* COMMANDS_H */

