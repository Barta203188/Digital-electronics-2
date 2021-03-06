/*
 * ---------------------------------------------------------------------
 * Author:      Tomas Fryza
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2018-09-27
 * Last update: 2019-07-16
 * Platform:    ATmega328P, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description: Blink a LED with delay function.
 * TODO: Verify functionality of LED blinker.
 * NOTE: Macro _BV converts a bit number into a byte value (see AVR Libc
 * Reference Manual).
 */


#include <avr/io.h>
#include <util/delay.h>
#include "gpio.h"
#define LED_RED     PD2
#define LED_GREEN   PB5
#define BTN         PD0
#define BLINK_DELAY 500

int main(void)
{
    /* Set output pin */
    GPIO_config_output(&DDRB, LED_GREEN);           /* DDRB = DDRB or (0010 0000) */
    GPIO_config_output(&DDRD, LED_RED);
    GPIO_input_pullup(PORTD, BUTTON);
    /* Turn LED off */
    GPIO_write(&PORTD, LED_RED, 1);
    GPIO_write(&PORTB, LED_GREEN, 1);
    
    for (;;)
    {
        if(bit_is_clear(PIND, BTN))
        {
        /* Invert LED and delay */
        GPIO_toggle(&PORTD, LED_RED);
        GPIO_toggle(&PORTB, LED_GREEN);
        _delay_ms(BLINK_DELAY);     /* Wait for several milisecs */
        }
    }
    return (0);
}
