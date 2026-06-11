#ifndef LAMP_H
#define LAMP_H

#include "gpio_device.h"
#include <stdbool.h>

typedef enum {Green, Yellow, Red} color_t;

typedef struct {
    pin_t green;
    pin_t yellow;
    pin_t red;
} lamp_t;

void lamp_bind(lamp_t *const l, pin_t p_green, pin_t p_yellow, pin_t p_red);
void lamp_on(lamp_t *const l, color_t c);
void lamp_off(lamp_t *const l, color_t c);
void lamp_toggle(lamp_t *const l, color_t c);
bool lamp_is_on(const lamp_t *const l, color_t c);
void lamp_unbind(lamp_t *const l);

#endif