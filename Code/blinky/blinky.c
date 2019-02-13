// ------ Preamble -------- //

#define F_CPU 1000000 
#define MCU atmega328p


#include <avr/io.h>     /* Defines pins, ports, etc. */
#include <util/delay.h> /* Functions to allow delay. */

int main(void) { 
    DDRB = 0b00000001;

    while(1){
        PORTB = 0b00000001;
        _delay_ms(1000);

        PORTB = 0b00000000;
        _delay_ms(1000);
    }
    return(0);
}
