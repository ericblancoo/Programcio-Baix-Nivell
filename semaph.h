#ifndef SEMAPH_H
#define SEMAPH_H

#include "lamp.h"

typedef enum {
    SemOff,
    SemClear,
    SemApproach,
    SemStop,
} semaph_state_t;

typedef struct {
    lamp_t *l;
    semaph_state_t s;
} semaph_t;

semaph_t semaph_bind(lamp_t *const lamp);
void semaph_set(semaph_t *const sem, semaph_state_t s);
semaph_state_t semaph_get(const semaph_t sem);
void semaph_unbind(semaph_t *const sem);
#endif
