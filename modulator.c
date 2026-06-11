/*Developer: Eric Blanco (4-juny-2024)
Revised: Izan Hernandez (23-juny-2024)
*/

#include "modulator.h"

void modulator_init(void){
  // Reset 
  TCNT2 = 0; 
  
  // CTC, comparador A amb Toggle en OC2A desactivat
  TCCR2A =  _BV(1); 
  
  // Senyal baix, Prescaler = 32KHZ
  TCCR2B = _BV(1) | _BV(0); 
  OCR2A = 79;

  // senyal modulat PORTB3, no modulat PORTB5
  DDRB = _BV(5)| _BV(3); 
}

void modulator_set(bool l){
  
  if (l){
    // Reset 
    TCNT2 = 0; 

    // Toggle en OC2A
    TCCR2A |= _BV(6); 

    // senyal modulat PORTB3, no modulat PORTB5
    PORTB = _BV(3) | _BV(5); 
  }

  else{
    // desactiva toggle on compare match amb OCR2A
    TCCR2A &=  ~_BV(6); 

    // senyal modulat PORTB3, no modulat PORTB5
    PORTB = 0; 
  }
}
