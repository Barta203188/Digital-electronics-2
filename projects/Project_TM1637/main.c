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

#define MAX_NUMBER_OF_DIGITS 10
#define LIMIT_OF_MINUTES 10
#define MS_IN_ONE_SECOND 1000
#define TENS_OF_SECONDS_IN_ONE_MINUTE 6

int main(void)
{
	int seconds = 0;
	int tens_of_seconds = 0;
	int minutes = 0;

	/* setup */
	TM1637_init(1/*enable*/, 7/*brightness*/);
	TM1637_clear();

	/* loop */
	while (1) {
			if (seconds == MAX_NUMBER_OF_DIGITS) {
				seconds = 0;
				tens_of_seconds++;
				if (tens_of_seconds == TENS_OF_SECONDS_IN_ONE_MINUTE) {
					minutes++;
					tens_of_seconds = 0;
					if (minutes == LIMIT_OF_MINUTES) {
						minutes = 0;
					}
				}
			}
			TM1637_display_digit(3, seconds);
			TM1637_display_digit(2, tens_of_seconds);
			TM1637_display_digit(1, minutes);
			TM1637_display_colon(1);
			_delay_ms(MS_IN_ONE_SECOND);
			seconds++;
		}
}
