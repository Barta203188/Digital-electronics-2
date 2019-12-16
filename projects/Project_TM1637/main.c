/**
 * Copyright (c) 2017-2018, Łukasz Marcin Podkalicki <lpodkalicki@gmail.com>
 *
 * This is ATtiny13 "Running Digits" example using attiny-tm1637-library,
 * https://github.com/lpodkalicki/attiny-tm1637-library .
 *
 */

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include "tm1637.h"
#include <avr/interrupt.h>
#include "gpio.h"

#define MAX_NUMBER_OF_DIGITS 10
#define LIMIT_OF_MINUTES 10
#define MS_IN_ONE_SECOND 1000
#define TENS_OF_SECONDS_IN_ONE_MINUTE 6

#define BTN_S1									PC0 // PCINT 8
#define BTN_S2									PC1 // PCINT 9


volatile int c_up = 0;
volatile int c_down = 0;

int main(void)
{
	int seconds = 0;
	int tens_of_seconds = 0;
	int minutes = 0;
/*
	int seconds_d = 9;
	int tens_of_seconds_d = 5;
	int minutes_d = 9;
*/
	int a = 0;
	
	/* setup */
	TM1637_init(1/*enable*/, 7/*brightness*/);
	TM1637_clear();

	TM1637_display_digit(3, 0);
	TM1637_display_digit(2, 0);
	TM1637_display_digit(1, 0);
	TM1637_display_colon(1);
	_delay_ms(800);
	

	DDRB &= ~((1 << DDB0) | (1 << DDB1));

	PORTB |= ((1 << PORTB0) | (1 << PORTB1));
/*	GPIO_config_input(&DDRB , BTN_S1);

*/
	PCICR |= _BV(PCIE0);
	PCMSK0 |= _BV(PCINT0);

	

/*	TIM_config_prescaler(TIM1, TIM_PRESC_256);
    TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);
*/
	sei ();

	/* loop */

	//c_up = 0;

	while (1)
	{
		if(c_up == 1)
		{
			TM1637_clear();
			if (seconds == MAX_NUMBER_OF_DIGITS) {
				seconds = 0;
				tens_of_seconds++;
				if (tens_of_seconds == TENS_OF_SECONDS_IN_ONE_MINUTE) {
					minutes++;
					tens_of_seconds = 0;
					if (minutes == LIMIT_OF_MINUTES) {
						minutes = 0;
						a = 1;
						break;
					}
				}
			}
			TM1637_display_digit(3, seconds);
			TM1637_display_digit(2, tens_of_seconds);
			TM1637_display_digit(1, minutes);
			TM1637_display_colon(1);
			_delay_ms(30);
			seconds++;
		}

		if(c_down == 1)
		{
			TM1637_display_digit(3, 5);
			TM1637_display_digit(2, 5);
			TM1637_display_digit(1, 5);
			TM1637_display_colon(1);
		}
	}	
			
			
			/*
			TM1637_clear();
			TM1637_display_digit(3, seconds_d);
			TM1637_display_digit(2, tens_of_seconds_d);
			TM1637_display_digit(1, minutes_d);
			TM1637_display_colon(1);
			_delay_ms(30);
			if (seconds_d == 0)
			{
				seconds_d = 10;
				if(seconds_d == 10)
				{
					tens_of_seconds_d--;
					if(tens_of_seconds_d == -1)
					{
						tens_of_seconds_d = 5;
						if(tens_of_seconds_d == 5)
						{
							minutes_d--;
							if(minutes_d == -1)
							{
								break;
							}
						}
					}

				}
			}
			seconds_d--;
			*/
			
		
			
		
	

if (a == 1)
{
	TM1637_display_digit(3, 9);
	TM1637_display_digit(2, 5);
	TM1637_display_digit(1, 9);
	TM1637_display_colon(1);

}
else
{
	TM1637_display_digit(3, 0);
	TM1637_display_digit(2, 0);
	TM1637_display_digit(1, 0);
	TM1637_display_colon(1);
}

	

	
}

ISR(PCINT0_vect)
{
	
	c_up = 1;
	c_down = 1;
}
