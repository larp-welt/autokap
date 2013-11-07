// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef AutoKAP_H_
#define AutoKAP_H_
#include "Arduino.h"
#include <Servo.h>

#include "def.h"
#include "config.h"
#include "extern/SerialCommand.h"
#include "configuration.h"
#include "commands.h"
#include "utils.h"

#define ACTION_TILT			0
#define ACTION_SHOOT		1
#define ACTION_ENDSH		2
#define ACTION_SHOOTPAUSE	3
#define ACTION_PAN			4
#define ACTION_PANEND		5

Servo TiltServo, PanServo;
unsigned long next = 0;
char TiltPosition = 0;
int16_t currentTilt;
char NextAction = ACTION_TILT;

#ifdef __cplusplus
extern "C" {
#endif
void loop();
void setup();
#ifdef __cplusplus
} // extern "C"
#endif

//add your function definitions for the project AutoKAP here

void moveServos();


//Do not add code below this line
#endif /* AutoKAP_H_ */
