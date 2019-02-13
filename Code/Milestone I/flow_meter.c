#define PIN_LED     PB0
#define PIN_SENSOR  PD2

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint16_t pulses = 0;

ISR(INT0_vect){
    /* Count the pulses */
    pulses = pulses + 1;
}

void initInterrupt(void){
    EIMSK |= (1 << INT0);                   // Enable INT0 
    EICRA  = (1 << ISC01) | (0 << ISC00);   // Trigger on falling edge. 
    sei();                                  // Turn on (globally) interrupts.    
}

int main(void){
    /* Setup data direction registers */
    DDRB = (1 << PIN_LED);
    DDRD = (0 << PIN_SENSOR);

    /* Set INPUT to INPUT_PULLUP */
    PORTB = (0 << PIN_LED);
    PORTD = (0 << PIN_SENSOR);

    /* Main program loop. */
    while(1){
        /* IF PIN_SENSOR is LOW */
        if (PIND & (1 << PIN_SENSOR)){
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
