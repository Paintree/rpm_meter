#include "config.h"
#include "gpio.h"
#include "i2c.h"

#include <util/delay.h>

#define LED_DATA_DIRECTION  DDRB
#define LED_PORT            PORTB
#define LED_PIN             PB5

void main () {
    gpioInit(&LED_DATA_DIRECTION, &LED_PORT, LED_PIN, OUTPUT);
    i2cInit();
    
    while(1) {
        gpioToggle(&LED_PORT, LED_PIN);
        _delay_ms(1000);
    }
}