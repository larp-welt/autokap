/*
 *
 */

#include <Arduino.h>
#include <avr/eeprom.h>

#include "configuration.h"

config_t config;


void eepromReadConfiguration() {
    // http://playground.arduino.cc/Code/EEPROMWriteAnything
    eeprom_read_block((void*)&config, (void*)0, sizeof(config));
    if (config.signature != EEPROM_SIGNATURE || config.version != EEPROM_CONF_VERSION) {
        // no config found, lets asume some reasonable defaults
        config.signature = EEPROM_SIGNATURE;
        config.version = EEPROM_CONF_VERSION;
        config.pause = 2000;
        config.shotpause = 1000;
        config.pan = 1500;
        config.panspeed = 1700;
        config.neutral = 1500;
        config.tilt[0] = 900;
        config.tilt[1] = 1200;
        config.tilt[2] = 1500;
        config.tilt[3] = 1800;
        config.tilt[4] = 0;
    } 
}


void eepromWriteConfiguration() {
    // http://playground.arduino.cc/Code/EEPROMWriteAnything
    eeprom_write_block((const void*)&config, (void*)0, sizeof(config));
}
