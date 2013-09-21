/*
 * def.h
 *
 *  Created on: 21.09.2013
 *      Author: tiggr
 */

#ifndef DEF_H_
#define DEF_H_

#define VERSION "0.1"

#define TILTPOSCOUNT 4

#define LEDPIN_PINMODE             pinMode (13, OUTPUT);
#define LEDPIN_TOGGLE              PINB |= 1<<5;     //switch LEDPIN state (digital PIN 13)
#define LEDPIN_OFF                 PORTB &= ~(1<<5);
#define LEDPIN_ON                  PORTB |= (1<<5);
#define LEDPIN_STATE               bitRead(PORTB, 5);


#endif /* DEF_H_ */
