#include "config.h"
#include "gpio.h"
#include "i2c.h"
#include "rpm.h"
#include "liquid_crystal_i2c.h"

#include <util/delay.h>
#include <stdio.h>
#include <string.h>

#define LED_DATA_DIRECTION DDRB
#define LED_PORT PORTB
#define LED_PIN PB5

#define LCD_ADRESS 0x27
#define LCD_COLUMNS 20
#define LCD_ROWS 4

#define RPM_SPACE 13

void main()
{
    initRPM();
    char string[RPM_SPACE] = {0};

    gpioInit(&LED_DATA_DIRECTION, &LED_PORT, LED_PIN, OUTPUT);
    i2cInit(SCL_100);

    LiquidCrystalDevice_t device = lq_init(LCD_ADRESS, LCD_COLUMNS, LCD_ROWS, LCD_5x8DOTS);
    lq_turnOnBacklight(&device);

    lq_print(&device, "RPM Meter");
    lq_setCursor(&device, 1, 13);
    lq_print(&device, "RPM");
    lq_setCursor(&device, 1, 0);


    while (1)
    {
        lq_setCursor(&device, 1, 0);
        sprintf(string, "");
        sprintf(string, "%d",getRPM());
        uint8_t rem = strlen(string);
        lq_print(&device, string);
        for (int i = 0; i < RPM_SPACE - rem; i++) {
            lq_setCursor(&device, 1, i + rem);
            lq_print(&device, " ");
        }

        gpioToggle(&LED_PORT, LED_PIN);
        _delay_ms(200);
    }
}
