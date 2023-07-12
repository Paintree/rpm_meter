#include "gpio.h"

void gpioInit(volatile uint8_t *ddr, volatile uint8_t *port, uint8_t pin, PinDirection direction) {
    if (direction == INPUT) {
        *ddr &= ~(1 << pin);
    } else {
        *ddr |= (1 << pin);
    }
}

void gpioWrite(volatile uint8_t *port, uint8_t pin, PinState state) {
    if (state == LOW) {
        *port &= ~(1 << pin);
    } else {
        *port |= (1 << pin);
    }
}

void gpioToggle(volatile uint8_t *port, uint8_t pin) {
    if (gpioRead(port, pin) == HIGH) {
        *port &= ~(1 << pin);
    } else {
        *port |= (1 << pin);
    }
}

PinState gpioRead(volatile uint8_t *port, uint8_t pin) {
    return ((*port >> pin) & 0x01) ? HIGH : LOW;
}

uint16_t gpioAnalogRead(uint8_t channel) {
    uint16_t value = 0; 

    ADMUX = (1 << REFS0);   

    ADMUX |= channel;
    ADCSRA |= (1 << ADEN);  

    ADCSRA |= (1 << ADSC);  

    while (ADCSRA & (1 << ADSC));   

    value = ADCL;
    value |= (ADCH << 8);   

    ADCSRA &= ~(1 << ADEN);
    return value;
}