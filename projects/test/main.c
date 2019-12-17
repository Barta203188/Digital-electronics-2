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
#include "timer.h"

#define MAX_NUMBER_OF_DIGITS 10
#define LIMIT_OF_MINUTES 10
#define MS_IN_ONE_SECOND 1000
#define TENS_OF_SECONDS_IN_ONE_MINUTE 6

#define BTN_S1									PC0 // PCINT 9
#define BTN_S2									PC1 // PCINT 10


volatile int c_up = 0;
volatile int c_down = 0;
//volatile int c_up_c;
//olatile int c_down_c;

int main(void)
{
	TM1637_init(1/*enable*/, 7/*brightness*/);
	TM1637_clear();

	TM1637_display_digit(3, 1);
	TM1637_display_digit(2, 2);
	TM1637_display_digit(1, 3);
	TM1637_display_colon(1);
	_delay_ms(1000);
	
	DDRB &= ~((1 << DDB0) | (1 << DDB1));
	PORTB |= ((1 << PORTB0) | (1 << PORTB1));

	PCICR |= (_BV(PCIE0) | _BV(PCIE1));
	PCMSK0 |= (_BV(PCINT0) | _BV(PCINT1));
	
/*
	PCICR |= _BV(PCIE1);
	PCMSK1 |= _BV(PCINT9) | _BV(PCINT10);

	TIM_config_prescaler(TIM0, TIM_PRESC_1024);
    TIM_config_interrupt(TIM0, TIM_OVERFLOW_ENABLE);

	TIM_config_prescaler(TIM1, TIM_PRESC_256);
    TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);
*/

	sei ();

	while (1)
	{
		
		if (c_up == 1)
		{
			c_up = 0;
			TM1637_display_digit(3, 7);
			TM1637_display_digit(2, 7);
			TM1637_display_digit(1, 7);
			TM1637_display_colon(1);
			_delay_ms(2000);
		}
		
		else if (c_down == 1)
		{
			c_down = 0;
			TM1637_display_digit(3, 4);
			TM1637_display_digit(2, 4);
			TM1637_display_digit(1, 4);
			TM1637_display_colon(1);
			_delay_ms(2000);
		}
		else
		{
			TM1637_display_digit(3, 9);
			TM1637_display_digit(2, 9);
			TM1637_display_digit(1, 9);
			TM1637_display_colon(1);
			_delay_ms(2000);
		}
	}
}

ISR(PCINT0_vect)
{
	static int c_down_c = 0;
	static int c_up_c = 0;
	if (bit_is_clear(PINC, BTN_S2))
	{
		if (c_up_c == c_up)
		{
			//c_down = 0;
			c_up = 1;		
		}
	}
	else if (bit_is_clear(PINC, BTN_S1))
	{
		if (c_down_c == c_down)
		{
			c_down = 1;
			//c_up = 0;		
		}
	}	
}
