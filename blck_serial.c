/*
Developer: Eric Blanco (24−maig−2024)
Revised: Izan Hernandez (23-juny-2024)
*/

#include "blck_serial.h"
#include <ctype.h>

// Envia la cadena s a través del port serial.
uint8_t print(const char s[]) {
    
    uint8_t count = 0;
    while (s[count] != '\0') {
        if (serial_can_put()) {
            serial_put(s[count]);
            count++;
        } else {
            break;
        }
    }
    return count;
}

// Llegeix fins a m-1 caràcters del port serial i els guarda en s.
uint8_t reads(char s[], uint8_t m) {
    
    uint8_t count = 0;
    bool started = false;

    while (count < m - 1) {
        while (!serial_can_get());

        char c = serial_get();

        if (isprint(c)) {
            if (!started) {
                started = true;
            }
            s[count++] = c;
        } else if (started) {
            break;
        }
    }

    s[count] = '\0';
    return count;
}

