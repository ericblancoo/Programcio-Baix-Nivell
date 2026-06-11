#ifndef CONTROL_H
#define CONTROL_H

#include "semaph.h"
#include "timer.h"
#include "lamp.h"
#include "gpio_device.h"


typedef enum {StreetA, StreetB} street_t;

void control_init(void);

void control_force(street_t t);

void control_off(void);

void control_on(void);

semaph_state_t control_get_state(street_t s);

#endif