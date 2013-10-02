/*

 */

#include "commands.h"

SerialCommand SerialShell;

const char *onoff[] = {"OFF", "ON"};


static int freeRAM() {
	extern int __heap_start, *__brkval;
	int v;
return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
} // end of freeRAM()

static void ok() { Serial.println(F("OK")); }

static void error(const char *errmsg) { 
	Serial.print(F("ERROR: "));
	Serial.println(errmsg);
} // end of error()


void ToggleLED() {
	char *arg;

	arg = SerialShell.next();

	if (arg == NULL) {
		int8_t state;
		state = LEDPIN_STATE
		Serial.print(F("LED "));
		Serial.println(onoff[state]);
	} else {
	if (strcmp(arg, "ON") == 0) {
		ok();
		LEDPIN_ON
	} else {
	if (strcmp(arg, "OFF") == 0) {
		ok();
		LEDPIN_OFF
	} else { error("unknown param"); }
	}}
} // end of ToggleLED


void Show() {
	/* show different values */
	char *arg;

	arg = SerialShell.next();

	if (strcmp(arg, "RAM") == 0) {
		Serial.print(F("RAM: "));
		Serial.println(freeRAM());
	} // end of if
	if (strcmp(arg, "CFG") == 0) {
		SerialShell.clearBuffer();
		Serial.print(F("// AutoKAP configuration"));
		Version();
		Pause();
		Shoot();
		Shootpause();
		Pan();
		Panspeed();
		Neutral();
		Tilt();
	} // end of if
} // end of Show()


void Echo() {
	char *arg;

	arg = SerialShell.next();
	while (arg != NULL) {
		Serial.print(arg);
		Serial.print(" ");
		arg = SerialShell.next();
	}
	Serial.println();
} // end of Echo()


void Version() {
	Serial.print(F("Version "));
	Serial.println(config.version);
} // end of Version()


void Pause() { _setValue("PAUSE", config.pause); }


void Shoot() { _setValue("SHT", config.shoot); }


void Shootpause() { _setValue("SHTP", config.shotpause); }


void Pan() { _setValue("PAN", config.pan); }


void Panspeed() { _setValue("SPD", config.panspeed); }


void Neutral() { _setValue("ZERO", config.panspeed); }


void Tilt() {
	int16_t values[4];
	int8_t set = 0;

	for (int8_t i=0; i<5; i++) {
		char* arg = SerialShell.next();

		if (arg == NULL) {
			values[i] = 0;
		} else {
			values[i] = atoi(arg);
			set = i;
		} // end of if
	} // end of for

	if (set == 0) {
		Serial.print("TLT");
		for (int8_t i=0; i<5; i++) {
			Serial.print(" ");
			Serial.print(config.tilt[i]);
		} // end of for
		Serial.println();
	} else {
		for (int8_t i=0; i<5; i++) { config.tilt[i] = values[i]; }
		ok();
	} // end of if
} // end of Tilt()


void Write() {
	eepromWriteConfiguration();
	ok();
} // end of Write()


void NoOp() {;}


void UnknownCommand(const char *command) { error(command); }


void _setValue(char *cmd, int16_t &config) {
	char *arg;

	arg = SerialShell.next();
	if (arg != NULL) {
		Serial.print(cmd);
		Serial.print(F(" "));
		Serial.println(config);
	} else {
		if (atoi(arg) > 0) {
			config = atoi(arg);
			ok();
		} else { error("unknown parameter"); }
	} // end of if
} // end of _setValue()
