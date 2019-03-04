#define PIN_LED     PB0
#define PIN_SENSOR  PD2

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <USART.h>

volatile uint16_t ticks = 0;

float ticksToLPM(uint16_t ticks){
    ticks = (float) ticks;
    float freq = 1000000 / ticks;

    return freq / 7.500;
}

ISR(INT0_vect){
    /* Read the timer. */
    ticks = (TCNT1H << 8) | (TCNT1L & 0x00FFF);

    /* Reset the timer. */
    TCNT1H = 0x00;
    TCNT1L = 0x00;

    if (ticksToLPM(ticks) > 1){
        /* Turn on LED */
        PORTB |= (1 << PIN_LED);
    }
    else {
        /* Turn LED off */
        PORTB &= ~(1 << PIN_LED);
    }
}

void initInterrupt(void){
    EIMSK |= (1 << INT0);                   // Enable INT0
    EICRA  = (0 << ISC01) | (1 << ISC00);   // Trigger on falling edge.
    sei();                                  // Turn on (globally) interrupts.
}

void initCounter(void){
    TCCR1A |= 0x00;
    TCCR1B |= 0x00; // No clock scaler (i.e. 1 tick = 1 [us])
}

int main(void){
    /* Setup data direction registers */
    DDRB = (1 << PIN_LED);
    DDRD = (0 << PIN_SENSOR);

    /* Set INPUT to INPUT_PULLUP */
    PORTB = (0 << PIN_LED);
    PORTD = (0 << PIN_SENSOR);

    /* Turn on interrupts. */
    initInterrupt();

    /* Turn on timer/counter 01 */
    initCounter();

    /* Turn on serial communications. */
    initUSART();
    printString("\r\nDoes this work?...");

    /* Main program loop. */
    while(1){
      printString("\r\nTest!");
    }

    return(0);
}
