/* 
 * File:   configuration.h
 * Author: tiggr
 *
 * Created on 21.09.2013 23:12
 */

#ifndef CONFIGURATION_H
#define	CONFIGURATION_H

#define EEPROM_SIGNATURE         0x414B4150
#define EEPROM_CONF_VERSION      2

#include "def.h"

struct config_t {
	int32_t signature;
	int16_t version;
	int16_t pause;
	int16_t shoot;
	int16_t shotpause;
	int16_t pan;
	int16_t panspeed;
	int16_t neutral;
	int16_t tilt[TILTPOSCOUNT];
};

extern config_t config;

void eepromReadConfiguration();
void eepromWriteConfiguration();

#endif	/* CONFIGURATION_H */

