/*
Developer: Eric Blanco (2−juny−2024)
Revised: Izan Hernandez (23-juny-2024)
*/
#include "ether.h"
#include "control.h"
#include "blck_serial.h"
#include "serial_device.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <util/atomic.h>

// funcio per mirar en quin estat està
void what_state(street_t q){
	switch (control_get_state(q)){
		case SemClear:
			print("CLEAR\r\n");
			break;

		case SemApproach:
			print("APROACH\r\n");
			break;

		case SemStop:
			print("STOPP\r\n");
			break;

		case SemOff:
			print("OFF\r\n");
			break;
	}
}

void main(void){
  char s[5];
  serial_open();
  control_init();
  ether_open();
  sei();
  control_on();
  while (1) {
    reads(s, 3);

    if (strcmp(s, "FA") == 0) { 

      if ((control_get_state(StreetA)) != SemOff && (control_get_state(StreetB) != SemOff)){
	      ether_put('F');
	      ether_put('A');
      }

      control_force(StreetA);
      print("Ok\r\n");
    }

    else if (strcmp(s, "FB") == 0) { 
      if ((control_get_state(StreetA)) != SemOff && (control_get_state(StreetB) != SemOff)){
        ether_put('F');
        ether_put('B');
      }

      control_force(StreetB);
      print("Ok\r\n");
    }

    else if (strcmp(s, "?A") == 0) { 
      what_state(StreetA);
    }
    
    else if (strcmp(s, "?B") == 0){ 
      what_state(StreetB);
    }
    
    else if (strcmp(s, "R") == 0){ 
      if ((control_get_state(StreetA)) == SemOff && (control_get_state(StreetB) == SemOff))
	      ether_put('R');
      control_on();
      print("Ok\r\n");
    }
    
    else if (strcmp(s, "H") == 0){ 
      if ((control_get_state(StreetA)) != SemOff && (control_get_state(StreetB) != SemOff))
        ether_put('H');
      control_off();
      print("Ok\r\n");
    }
  }
}

