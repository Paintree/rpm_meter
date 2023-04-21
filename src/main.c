#define F_CPU 16000000UL
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include <util/delay.h>

#include "gpio.h"

void main () {

    gpioInit(&DDRB, &PORTB, PB5, OUTPUT);
    
    while(1) {
        gpioToggle(&PORTB, PB5);
        _delay_ms(1000);
    }
}