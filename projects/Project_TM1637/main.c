/*
 * ---------------------------------------------------------------------
 * Author:     	Vojtěch Bárta, Roman Vomela
 *             
 * Created:     2019-11-28
 * Last update: 2019-12-17
 * Platform:    ATmega328P, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description: 3-sides-poker-timer, counting up/down 
 */

/* Includes ------------------------------------------------------------ */
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include "tm1637.h"
#include <avr/interrupt.h>
#include "gpio.h"

/* Define --------------------------------------------------------------- */
#define MAX_NUMBER_OF_DIGITS 10
#define LIMIT_OF_MINUTES 10
#define MS_IN_ONE_SECOND 1000
#define TENS_OF_SECONDS_IN_ONE_MINUTE 6
#define BTN_S1					PC0 // PCINT 8
#define BTN_S2					PC1 // PCINT 9

/* Global variables ------------------------------------------------------------- */ 
volatile int c_up = 0;
volatile int c_down = 0;

/* Functions -------------------------------------------------------------------- */ 
int main(void)
{
	/* Local variables ------------------------------------------------------- */
	int seconds = 0;
	int tens_of_seconds = 0;
	int minutes = 0;

	int seconds_d = 9;  
	int tens_of_seconds_d = 5;
	int minutes_d = 9;

	int a = 0;	/* display selection after counting */ 
	
	TM1637_init(1/*enable*/, 7/*brightness*/);
	TM1637_clear(); 	/* clear display */

	TM1637_display_digit(3, 0); 
	TM1637_display_digit(2, 0);
	TM1637_display_digit(1, 0);
	TM1637_display_colon(1);
	_delay_ms(500);
	
	DDRB &= ~((1 << DDB0) | (1 << DDB1));
	PORTB |= ((1 << PORTB0) | (1 << PORTB1));

	/* Pin Change Interrupts */
	PCICR |= (_BV(PCIE0) | _BV(PCIE1));
	PCMSK0 |= (_BV(PCINT0) | _BV(PCINT1));

	/* Enable interrupts by setting the global interrupt mask */
	sei ();

	/* Infinite loop */
	while (1)
	{
		if(c_up == 1)
		{
			c_up = 0;
			TM1637_clear();	/* clear display */
			if (seconds == MAX_NUMBER_OF_DIGITS) 
			{
				seconds = 0;
				tens_of_seconds++; 	/* increments tens of seconds */
				if (tens_of_seconds == TENS_OF_SECONDS_IN_ONE_MINUTE) 
				{
					minutes++;	/* increments of minutes */
					tens_of_seconds = 0;
					if (minutes == LIMIT_OF_MINUTES) 
					{
						minutes = 0;
						a = 1;
					}
				}
			}
			TM1637_display_digit(3, seconds);
			TM1637_display_digit(2, tens_of_seconds);
			TM1637_display_digit(1, minutes);
			TM1637_display_colon(1);
			_delay_ms(MS_IN_ONE_SECOND);
			seconds++;	/* increments of seconds */
			
		}
		else if (c_down == 1)
		{
			c_down = 0;
			TM1637_clear();	/* clear display */
			TM1637_display_digit(3, seconds_d);
			TM1637_display_digit(2, tens_of_seconds_d);
			TM1637_display_digit(1, minutes_d);
			TM1637_display_colon(1);
			_delay_ms(MS_IN_ONE_SECOND);
			if (seconds_d == 0)
			{
				seconds_d = 10;
				if(seconds_d == 10)
				{
					tens_of_seconds_d--;	/* decrements of tens of second */
					if(tens_of_seconds_d == -1)
					{
						tens_of_seconds_d = 5;
						if(tens_of_seconds_d == 5)
						{
							minutes_d--; 	/* decrements of minutes */
							if(minutes_d == -1)
							{
								minutes_d = 10;
								a = 2;
							}
						}
					}

				}
			}
			seconds_d--;	/* decrements of seconds*/
			
		}
		if (a == 1)
		{
			TM1637_display_digit(3, 9);
			TM1637_display_digit(2, 5);
			TM1637_display_digit(1, 9);
			TM1637_display_colon(1);
			_delay_ms(1000);
		
		}
		else if (a == 2)
		{
			TM1637_display_digit(3, 0);
			TM1637_display_digit(2, 0);
			TM1637_display_digit(1, 0);
			TM1637_display_colon(1);
			_delay_ms(1000);
		
		}
	}
}	

/* Interrupt routine */
ISR(PCINT0_vect)
{
	static int c_down_c = 0;
	static int c_up_c = 0;
	if (bit_is_clear(PINC, BTN_S2))
	{
		if (c_up_c == c_up)
		{
			c_down = 0;
			c_up = 1;		
		}
	}
	else if (bit_is_clear(PINC, BTN_S1))
	{
		if (c_down_c == c_down)
		{
			c_down = 1;
			c_up = 0;		
		}
	}	
}
