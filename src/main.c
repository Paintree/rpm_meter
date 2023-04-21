#include <avr/io.h>
#include <util/delay.h>

void main () {

    // Blink Led
    DDRB = DDRB | (1<<DDB5);
    
    while(1) {
        PORTB = PORTB | (1 << PORTB5);
        _delay_ms(1000);
        PORTB = PORTB & ~(1 << PORTB5);
        _delay_ms(1000);
    }
    
}