#include <avr/io.h>
#include <TM1637Display.h>

#define CLK 2
#define DIO 3

const uint8_t AHOJ[] = { 
SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G, // A 
SEG_B | SEG_C | SEG_E | SEG_F | SEG_G, // H 
SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F, // O 
SEG_B | SEG_C | SEG_D | SEG_E // J 
}; 
uint8_t desetinna_tecka[] = { 0x00, 0x00, 0x00, 0x00, 0x00 }; 
//instance displej z knihovny TM1637 
TM1637Display displej(CLK, DIO);
void setup() { 
Serial.begin(9600); 
displej.setBrightness(15); 
displej.setSegments(AHOJ); 
delay(3000); 
displej.showNumberDec(12, false);
delay(1000); 
displej.showNumberDec(34, true); 
delay(1000); 
for (int i = 0; i < 256; i++) { 
Serial.print("Aktualni cislo: "); Serial.println(i); 
displej.setSegments(desetinna_tecka); 
desetinna_tecka[0]++; 
desetinna_tecka[1]++; 
desetinna_tecka[2]++; 
desetinna_tecka[3]++; 
desetinna_tecka[4]++; 
delay(500); 
} 
displej.showNumberDec(5, 1, 2); 
delay(1000);
} 
void loop() 
{ 
uint8_t vypis[] = { 0, 0, 0, 0 }; 
long cas = millis() / 1000; 
vypis[0] = displej.encodeDigit((cas / 60) / 10); 
vypis[1] = displej.encodeDigit((cas / 60) % 10); 
vypis[2] = displej.encodeDigit((cas % 60) / 10); 
vypis[3] = displej.encodeDigit((cas % 60) % 10); 
displej.setSegments(vypis); 
delay(500); 
vypis[1] = vypis[1] + 128; 
displej.setSegments(vypis);
delay(500); 
}
