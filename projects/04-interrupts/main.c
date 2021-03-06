/*
 * ---------------------------------------------------------------------
 * Author:      Tomas Fryza
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2018-11-28
 * Last update: 2019-10-11
 * Platform:    ATmega328P, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description: Control LEDs using functions from GPIO and Timer 
 *              libraries. Do not use delay library any more.
 * TODO: Create and test functions to control 8-bit Timer/Counter0 and 
 *       16-bit Timer/Counter1 modules.
 * NOTE: Store timer.c and timer.h files in library/src and library/inc
 *       folders.
 */


#include <avr/io.h>
#include "gpio.h"
#include "timer.h"
#include <avr/interrupt.h>
#define LED_GREEN   PB5
#define LED_RED     PB0

int i = 0;
int main(void)
{
    GPIO_config_output(&DDRB, LED_GREEN);
    GPIO_write(&PORTB, LED_GREEN, PIN_LOW);
    GPIO_config_output(&DDRB, LED_RED);
    GPIO_write(&PORTB, LED_RED, PIN_LOW);
    TIM_config_prescaler(TIM0, TIM_PRESC_1024);
    TIM_config_interrupt(TIM0, TIM_OVERFLOW_ENABLE);
    TIM_config_prescaler(TIM1, TIM_PRESC_256);
    TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);
    sei();

    for (;;) {
    }

    return (0);
}

ISR(TIMER0_OVF_vect)
{
    i++;
    if (i==10)
    {
    // TODO: Toggle green LED
        i=0;
        GPIO_toggle(&PORTB, LED_GREEN);
    }
}

ISR(TIMER1_OVF_vect)
{
    // TODO: Toggle red LED
    GPIO_toggle(&PORTB, LED_RED);
}
