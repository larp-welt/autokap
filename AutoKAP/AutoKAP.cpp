// Do not remove the include below
#include "AutoKAP.h"

#define ACTION_TILT		0
#define ACTION_SHOOT	1
#define ACTION_PAN		2
#define ACTION_PANEND	3


Servo TiltServo, PanServo;
unsigned long next = 0;
char TiltPosition = 0;
char NextAction = ACTION_TILT;


//The setup function is called once at startup of the sketch
void setup()
{
	LEDPIN_PINMODE
	LEDPIN_OFF

	Serial.begin(9600);
	Serial.print(F("// AutoKAP V"));
	Serial.println(VERSION);

    SerialShell.addCommand("LED", ToggleLED);
	SerialShell.addCommand("SHW", Show);
	SerialShell.addCommand("PRT", Echo);
	SerialShell.addCommand("WRT", Write);
	SerialShell.addCommand("//", NoOp);
	SerialShell.setDefaultHandler(UnknownCommand);
    Serial.println(F("// - Serial communication started"));

    eepromReadConfiguration();
    Serial.println(F("// - Configuration done"));


	TiltServo.attach(TILT_SERVO);
	PanServo.attach(PAN_SERVO);

	Serial.println(F("// - Starting KAP"));
	signalLed("---");
	LEDPIN_OFF
}


// The loop function is called in an endless loop
void loop()
{
	unsigned long now;

	SerialShell.readSerial();

	now = millis();

	if (now >= next) {
		switch (NextAction) {
		case ACTION_TILT:
			// tilt
			TiltServo.writeMicroseconds(config.tilt[TiltPosition]);
			NextAction = ACTION_SHOOT;
			next = now + config.pause;
			break;
		case ACTION_SHOOT:
			// shoot per chdk
			// ToDo
			TiltPosition = TiltPosition++;
			if (TiltPosition > TILTPOSCOUNT || config.tilt[TiltPosition] == 0) {
				NextAction = ACTION_PAN;
				TiltPosition = 0;
			} else {
				NextAction = ACTION_TILT;
			}
			next = now + config.shotpause;
			break;
		case ACTION_PAN:
			// pan start
			TiltServo.writeMicroseconds(config.tilt[TiltPosition]);
			PanServo.writeMicroseconds(config.panspeed);
			next = now + config.pan;
			NextAction = ACTION_PANEND;
			break;
		case ACTION_PANEND:
			PanServo.writeMicroseconds(config.neutral);
			next = now + config.pause;
			NextAction = ACTION_SHOOT;
			break;
		} // end of switch
	} // end of if
} // end of loop()
