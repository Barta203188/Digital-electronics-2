/*
 * ---------------------------------------------------------------------
 * Author:      Tomas Fryza
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2018-10-23
 * Last update: 2019-11-01
 * Platform:    ATmega328P, 16 MHz, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description:
 *    Analog-to-digital conversion with displaying result on LCD and 
 *    transmitting via UART.
 * 
 * Note:
 *    Peter Fleury's UART library.
 */

/* Includes ----------------------------------------------------------*/
#include <stdlib.h>             // itoa() function
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "lcd.h"
#include "uart.h"

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
#define UART_BAUD_RATE 9600

/* Variables ---------------------------------------------------------*/
/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/
/**
 *  Brief:  Main program. Read ADC result and transmit via UART.
 *  Input:  None
 *  Return: None
 */
int main(void)
{
    // LCD display
    lcd_init(LCD_DISP_ON);
    lcd_puts("LCD testing");

    /* ADC
     * TODO: Configure ADC reference, clock source, enable ADC module, 
     *       and enable conversion complete interrupt */
    ADMUX &= ~(_BV(REFS1) | _BV(MUX0) | _BV(MUX1)| _BV(MUX2)| _BV(MUX3));
    ADMUX |= _BV(REFS0);
    ADCSRA |= (_BV(ADEN) | _BV(ADIE) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0));

    /* Timer1
     * TODO: Configure Timer1 clock source and enable overflow 
     *       interrupt */
    TIM_config_prescaler(TIM1 ,TIM_PRESC_64);
    TIM_config_interrupt(TIM1 ,TIM_OVERFLOW_ENABLE);

    // UART: asynchronous, 8-bit data, no parity, 1-bit stop
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));

    // Enables interrupts by setting the global interrupt mask
    sei();

    // Put string to ringbuffer for transmitting via UART.
    uart_puts("UART testing\r\n");

    // Infinite loop
    for (;;) {
    }

    // Will never reach this
    return (0);
}

/**
 *  Brief: Timer1 overflow interrupt routine. Start ADC conversion.
 */
ISR(TIMER1_OVF_vect)
{
    // TODO: Start ADC conversion
    ADCSRA |= _BV(ADSC);
}

/**
 *  Brief: ADC complete interrupt routine. Update LCD and UART 
 *         transmiter.
 */
ISR(ADC_vect)
{
    uint16_t value = 0;
  
    char uart_string[4];

	// Read 10-bit ACD value
    value = ADC;

    lcd_clrscr();
    lcd_puts("Voltage value :)");
    lcd_gotoxy(0, 1);
    itoa(value, uart_string, 10);
    //lcd_puts(uart_string);

   if(value < 90)
    {
      
        uart_puts("\r\n\033[4;32mRIGHT\033[0m");
        
        lcd_puts(uart_string);
        lcd_gotoxy(6, 1);
        lcd_puts("RIGHT   :(");
    }
        
    else if(value >= 90 && value <= 110)
    {
          
        uart_puts("\r\nUP");
        lcd_puts(uart_string);
        lcd_gotoxy(6, 1);
        lcd_puts("UP");
    }
    else if(value >= 235 && value <= 280)
    {

        uart_puts("\r\nDOWN");
        lcd_puts(uart_string);
        lcd_gotoxy(6, 1);
        lcd_puts("DOWN");
    }   
    else if(value >= 390 && value <= 430)
    {
    
        uart_puts("\r\nLEFT");
        lcd_puts(uart_string);
        lcd_gotoxy(6, 1);
        lcd_puts("LEFT");
    }  
    else if(value >= 620 && value <= 680)
    {
           
        uart_puts("\r\nSELECT");
        lcd_puts(uart_string);
        lcd_gotoxy(6, 1);
        lcd_puts("SELECT");
    }   
    else
        uart_puts("\r\nNo selection");  
   /* uart_puts(uart_string);
    uart_puts("\n\r");
*/
    // TODO: Update LCD and UART transmiter
}