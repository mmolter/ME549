#define PIN_LED     PB0
#define PIN_SENSOR  PB1

#include <avr/io.h>
#include <util/delay.h>

int main(void){
    uint16_t last_rising_edge  = 0; 
    uint16_t pulses_per_second = 0;
    
    /* Setup data direction registers */
    DDRB = (1 << PIN_LED) | (0 << PIN_SENSOR);

    /* Set INPUT to INPUT_PULLUP */
    PORTB = (0 << PIN_LED) | (0 << PIN_SENSOR);

    /* Main program loop. */
    while(1){
        /* IF PIN_SENSOR is LOW */
        if (PINB & (1 << PIN_SENSOR)){
            /* Turn on LED */
            PORTB |= (1 << PIN_LED);
        }
        else {
            /* Turn LED off */
            PORTB &= ~(1 << PIN_LED);
        }
    }

    return(0);
}
