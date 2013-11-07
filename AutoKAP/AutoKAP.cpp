// Do not remove the include below
#include "AutoKAP.h"


//The setup function is called once at startup of the sketch
void setup()
{
	LEDPIN_PINMODE
	LEDPIN_OFF

	CHDKPIN_PINMODE
	CHDKPIN_OFF

	Serial.begin(9600);
	Serial.print(F("// AutoKAP V"));
	Serial.println(VERSION);

	SerialShell.addCommand("LED", ToggleLED);
	SerialShell.addCommand("SHW", Show);
	SerialShell.addCommand("PRT", Echo);
	SerialShell.addCommand("WRT", Write);
	SerialShell.addCommand("VER", Version);
	SerialShell.addCommand("PAUSE", Pause);
	SerialShell.addCommand("SHT", Shoot);
	SerialShell.addCommand("SHTP", Shootpause);
	SerialShell.addCommand("PAN", Pan);
	SerialShell.addCommand("SPD", Panspeed);
	SerialShell.addCommand("ZERO", Neutral);
	SerialShell.addCommand("TLT", Tilt);
	SerialShell.addCommand("STEP", Step);
	SerialShell.addCommand("RST", Reset);
	SerialShell.addCommand("//", NoOp);
	SerialShell.setDefaultHandler(UnknownCommand);
	Serial.println(F("// - Serial communication started"));

	eepromReadConfiguration();
	Serial.println(F("// - Configuration done"));


	TiltServo.attach(TILT_SERVO);
	TiltServo.writeMicroseconds(config.tilt[0]);
	currentTilt = config.tilt[0];

	PanServo.attach(PAN_SERVO);
	PanServo.writeMicroseconds(config.neutral);

	Serial.println(F("// - Starting KAP"));
	signalLed("---");
	LEDPIN_OFF
}


void moveServos() {
	static unsigned long next = 0;

	if (millis() >= next) {
		if (config.tilt[TiltPosition] != currentTilt) {
			int16_t diff;
			diff = config.tilt[TiltPosition] - currentTilt;
			if (diff > 0) { currentTilt = currentTilt + config.step; }
			if (diff < 0) { currentTilt = currentTilt - config.step; }
			if (abs(diff) < config.step) { currentTilt = config.tilt[TiltPosition]; }
			TiltServo.writeMicroseconds(currentTilt);
		} // end of if

		next = millis() + 10;
	} // end of if
} // end of moveServos

// The loop function is called in an endless loop
void loop()
{
	unsigned long now;

	SerialShell.readSerial();
	moveServos();

	now = millis();

	if (now >= next) {
		switch (NextAction) {
		case ACTION_TILT:
			// wait until position is reached!
			if (config.tilt[TiltPosition] == currentTilt) {
				NextAction = ACTION_SHOOT;
				next = now + config.pause;
			} else {
				next = now + 10;
			} // end of if
			break;
		case ACTION_SHOOT:
			// shoot per chdk
			LEDPIN_ON
			CHDKPIN_ON
			NextAction = ACTION_ENDSH;
			next = now + config.shoot;
			break;
		case ACTION_ENDSH:
			LEDPIN_OFF
			CHDKPIN_OFF
			next = now + config.shotpause;
			NextAction = ACTION_SHOOTPAUSE;
			break;
		case ACTION_SHOOTPAUSE:
			TiltPosition = TiltPosition++;
			if (TiltPosition > TILTPOSCOUNT || config.tilt[TiltPosition] == 0) {
				NextAction = ACTION_PAN;
				TiltPosition = 0;
			} else {
				NextAction = ACTION_TILT;
			}
			break;
		case ACTION_PAN:
			// pan start
			PanServo.writeMicroseconds(config.panspeed);
			next = now + config.pan;
			NextAction = ACTION_PANEND;
			break;
		case ACTION_PANEND:
			PanServo.writeMicroseconds(config.neutral);
			next = now + config.pause;
			NextAction = ACTION_TILT;
			break;
		} // end of switch
	} // end of if
} // end of loop()
