#include "rpm.h"
#include "config.h"

#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint32_t timerPulse = 0;
volatile uint16_t pulses = 0;

void initRPM() {

    TCCR1A = 0x00;
    TCCR1B = (1 << CS10);
    OCR1A = 1562;
    TIMSK1 |= (1 << OCIE1A);

    EICRA = (1 << ISC01);
    EIMSK |= (1 << INT0);

    sei();
}

uint16_t getRPM() {
    if (pulses == 0 || timerPulse == 0)
        return 0;
    uint16_t rpm = pulses * 600 / timerPulse;
    pulses = 0;
    timerPulse = 0;

    return rpm;
}

ISR(TIMER1_COMPA_vect) {
    timerPulse++;
}

ISR(INT0_vect) {
    pulses++;
}