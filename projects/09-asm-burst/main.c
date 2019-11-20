/***********************************************************************
 * 
 * Implementation of LFSR-based (Linear Feedback Shift Register) 
 * pseudo-random generator in AVR assembly.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2017-2019 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Includes ----------------------------------------------------------*/
#include <stdlib.h>         // itoa() function
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "uart.h"
#include "gpio.h"


/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/

#define burst_5         PB5

/* Define ------------------------------------------------------------*/
//#define UART_BAUD_RATE 9600

/* Variables ---------------------------------------------------------*/
//state_t current_state = IDLE_STATE;

/* Function prototypes -----------------------------------------------*/
//void fsm_random(void);
extern void burst_asm(uint8_t current);
//extern uint8_t rand8_asm(uint8_t current);

/* Functions ---------------------------------------------------------*/

int main(void)
{
    GPIO_config_output(&DDRB, burst_5);
    GPIO_write(&PORTB, burst_5, 1);
 


    /* Infinite loop */
      for (;;)
      {
       burst_asm(0);
      }
    return (0);
}