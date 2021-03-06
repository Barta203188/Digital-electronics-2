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

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>
#include <util/delay.h>
#define LED_RED     PD2
#define BTN         PD3
#define BLINK_DELAY 500

int main(void)
{
    /* Set output pin */
    //DDRD |= _BV(LED_GREEN);           /* DDRB = DDRB or (0010 0000) */
    DDRD |= _BV(LED_RED);
    DDRD &= ~_BV(BTN);
    PORTD |= _BV(BTN);                /* nastaveni pull up rezistoru*/
    /* Turn LED off */
    //PORTB &= ~_BV(LED_GREEN);         /* PORTB = PORTB and (0010 0000) */
    PORTD &= ~_BV(LED_RED);
    /* Infinite loop */
    for (;;)
    {
        if(bit_is_clear(PIND, BTN))
        {
        /* Invert LED and delay */
        //PORTB ^= _BV(LED_GREEN);      /* PORTB = PORTB xor (0010 0000) */
        PORTD ^= _BV(LED_RED);
        _delay_ms(BLINK_DELAY);     /* Wait for several milisecs */
        }
    }
    return (0);
}
