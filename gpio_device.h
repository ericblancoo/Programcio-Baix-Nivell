#ifndef GPIO_DEVICE_H
#define GPIO_DEVICE_H

#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>

typedef enum {Input, InputNP, Output} pin_direction_t;
// definim stuct
typedef struct {
   // volatile 
    volatile uint8_t *port;
    uint8_t pin_mask;
} pin_t;
pin_t pin_bind(volatile uint8_t *port, uint8_t pin, pin_direction_t d);
void pin_write(pin_t p, uint8_t v);
uint8_t pin_read(pin_t p);
void pin_toggle(pin_t p);
void pin_unbind(pin_t *const p);
#endif