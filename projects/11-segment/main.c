// TM1637 test
// main.c


#include "tm1637.h"


int main(void)
    {
    TM1637_SERIAL_INIT;

    led_print(0, "tE5t");

    for(;;);
    }