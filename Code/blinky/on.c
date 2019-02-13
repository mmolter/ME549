// ------ Preamble -------- //

#define F_CPU 1000000 

#include <avr/io.h>     /* Defines pins, ports, etc. */

int main(void) { 
    DDRB  = 0b00000001;
    PORTB = 0b00000001;

    while(1){
    }
    return(0);
}
