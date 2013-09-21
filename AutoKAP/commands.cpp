/*

 */

#include "commands.h"

SerialCommand SerialShell;
        
const char *onoff[] = {"OFF", "ON"};


static int freeRAM () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

static void ok() { Serial.println(F("OK")); }

static void error(const char *errmsg) { 
    Serial.print(F("ERROR: "));
    Serial.println(errmsg);
}


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
}


void Show() {
    /* show different values */
    char *arg;
    
    arg = SerialShell.next();
    
    if (strcmp(arg, "RAM") == 0) {
        Serial.print(F("RAM: "));
        Serial.println(freeRAM());
    }
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


void Write() {
    eepromWriteConfiguration();
    ok();
}


void NoOp() {;}


void UnknownCommand(const char *command) { error(command); }
