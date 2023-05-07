#include "config.h"
#include "gpio.h"
#include "i2c.h"
#include "liquid_crystal_i2c.h"

#include <util/delay.h>

#define LED_DATA_DIRECTION DDRB
#define LED_PORT PORTB
#define LED_PIN PB5

#define LCD_ADRESS  0x27
#define LCD_COLUMNS 20
#define LCD_ROWS    4

void main() {

    gpioInit(&LED_DATA_DIRECTION, &LED_PORT, LED_PIN, OUTPUT);
    i2cInit(SCL_100);

    LiquidCrystalDevice_t device = lq_init(LCD_ADRESS, LCD_COLUMNS, LCD_ROWS, LCD_5x8DOTS);
    lq_turnOnBacklight(&device);

    lq_print(&device, "RPM Meter");
    lq_setCursor(&device, 1, 0);
    lq_print(&device, "Initialization");

    while (1)
    {
        gpioToggle(&LED_PORT, LED_PIN);
        _delay_ms(1000);
    }

}