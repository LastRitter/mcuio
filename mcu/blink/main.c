#include <avr/io.h>
#include <util/delay.h>

// LED is in PC7 (Arduino D13)
#define BLINK_PORT      PORTC
#define BLINK_DDR       DDRC
#define BLINK_PIN       7
#define BLINK_MSEC      100


int main(void)
{
    BLINK_DDR |= (1 << BLINK_PIN); // Set Blink Pin Output
    
    while(1)
    {
        BLINK_PORT |= (1 << BLINK_PIN);
        _delay_ms(BLINK_MSEC);

        BLINK_PORT &= ~(1 << BLINK_PIN);
        _delay_ms(BLINK_MSEC);
    }

    return 0;
}


