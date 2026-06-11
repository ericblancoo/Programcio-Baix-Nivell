/*
Developer: Eric Blanco (5−abril−2024)
Revised: Izan Hernandez (23-juny-2024)
*/
#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include "gpio_device.h"


// Vincular pins
pin_t pin_bind(volatile uint8_t *port, uint8_t pin, pin_direction_t d) {
    
    uint8_t pin_mask = (1 << pin); // aquesta linea fa una mascara dels pins

    // configura ports
    if (d == Output) {
        *(port - 1) |= pin_mask;  // Sortida
    } else {
        *(port - 1) &= ~pin_mask; // Entrada, això(~) inverteix els bits 
        if (d == Input) {
            *port |= pin_mask; // activa pull up
        }
    }

    return (pin_t){.port = port, .pin_mask = pin_mask};
}

void pin_write(pin_t p, uint8_t v) {
    if (v) {
        *(p.port) |= p.pin_mask;   // pin = 1
    } else {
        *(p.port) &= ~(p.pin_mask); // pin = 0
    }
}

uint8_t pin_read(pin_t p) {
    return (*(p.port) & p.pin_mask) ? 1 : 0; // llegir pin, retorna 1 o 0 si esta en high o low respectivament
}

void pin_toggle(pin_t p) {
    *(p.port) ^= p.pin_mask; // XOR, si son iguals posa en low el pin, y el estat del pin al struct canvia
}

void pin_unbind(pin_t *const p) {
    // restableix configuració del pin
    *(p->port - 1) &= ~(p->pin_mask);
    p->port = NULL;
    p->pin_mask = 0;
}
