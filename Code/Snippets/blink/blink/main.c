/*
 * blink.c
 *
 * Created: 3/10/2019 1:01:54 PM
 * Author : mmolt
 */ 

#define F_CPU 8000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

ISR(TIMER0_COMPA_vect){
	PORTB ^= (1 << PB7);
};

int main(void)
{
	/* Set PIN13 to OUTPUT */
	DDRB |= (1 << PB7);
	
	
	/* Setup Timer/Counter 0 */
	
	TCCR0A  = (0 << COM0A1) & (0 << COM0A0);					// Normal Mode.
	TCCR0A |= (0 << WGM02)  & (1 << WGM01)  & (0 << WGM00);		// Clear on timer on OCRA match.
	
	TCCR0B  = (1 << CS02) & (0 << CS01) & (1 << CS00);			// CLK / 1024 = 1 [us].
	
	TIMSK0 = (1 << OCIE0A); // Overflow interrupt enable.
	
	sei();
	
	PORTB = 0xFF;
		
    while (1) {}
	
	return(0);
}
