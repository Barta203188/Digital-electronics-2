/*
 * ---------------------------------------------------------------------
 * Author:      Tomas Fryza
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2018-10-11
 * Last update: 2019-10-16
 * Platform:    ATmega328P, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description: Decimal counter with data display on 7-segment display.
 * TODO: Create and test functions to operate a 7-segment display using
 *       shift registers.
 * NOTE: Store segment.c and segment.h files in library/src and 
 *       library/inc folders.
 */

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>
#include "gpio.h"
#include "timer.h"
#include <avr/interrupt.h>

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
#define CLK             PD2
#define DATA            PD4 

/* Variables ---------------------------------------------------------*/
/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/
/**
 *  Brief:  Main program. Shows decimal values ​​on 7-segment display.
 *  Input:  None
 *  Return: None
 */
    int i = 0;
int main(void)
{
    /* D1 led */
    // TODO: Configure D1 led at Multi-Function Shield
    //GPIO_config_output(&DDRB , LED_D1);
    /* Pin Change Interrupts 11:9 */
    // TODO: Configure Pin Change Interrupts 11, 10, and 9
    PCICR |= _BV(PCIE1);
    PCMSK1 |= _BV(PCINT9) | _BV(PCINT10) | _BV(PCINT11);

    TIM_config_prescaler(TIM1, TIM_PRESC_256);
    TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);
    /* 7-segment display interface */
    // TODO: Configure 7-segment display pins
    
    /* Enable interrupts by setting the global interrupt mask */
    sei();

    /* Infinite loop */
    for (;;) {
        // TODO: Use function to display digit 1 at position 0
        SEG_putc(i, 0);
    }

    return (0);
}

/**
 *  Brief: Pin Change Interrupt 11:9 routine. Toggle a LED.
 */
ISR(TIMER1_OVF_vect)
{
    // TODO: Toggle a led
     i++;
     SEG_putc(i, 0);
    if(i == 10) 
        {
            i = 0;
            
        }
}
/*ISR(TIMER0_OVF_vect)
{
    
    c++;
    if(c == 4)
    {
        c = 0;
    }
    
}*/



