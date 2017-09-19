#include <built_in.h>

unsigned int adc_rd;
unsigned int rd;

void main() {
  /* This program reads the data from the microcontroller ADC
   * and converts the light bulbs on the board.
   */
  DDRB = 0xFF; // all diodes in the ON mode
  DDRC = 0xFF; // all diodes in the ON mode
  
  while (1) {
    adc_rd = ADC_Read(2); // read from the second ADC controller
    // adc_rd = 496; // let got 0111110000
    rd =  65535; // the state of our ports is now: 
                 // all lamps are ON (11111111 11111111)
    adc_rd = (adc_rd >> 6); // shift by 6 to the right 
                            // (div by 2^6: 0000000111)
                            // only three light bulbs should shine
    rd = (rd << adc_rd); // left shift to adc_rd
                         // 1111111110000000
    PORTB = rd; // low byte is output to port B
                // 10000000
    PORTC = Hi(rd); // high byte is output to port C
                    // 11111111
  }
}

