#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include <avr/io.h>

typedef enum {
  INPUT,
  OUTPUT
} PinDirection;

typedef enum {
  LOW,
  HIGH
} PinState;

void gpioInit(volatile uint8_t *ddr, volatile uint8_t *port, uint8_t pin, PinDirection direction);
void gpioWrite(volatile uint8_t *port, uint8_t pin, PinState state);
void gpioToggle(volatile uint8_t *port, uint8_t pin);
PinState gpioRead(volatile uint8_t *port, uint8_t pin);
uint16_t gpioAnalogRead(uint8_t channel);

#endif // GPIO_H
