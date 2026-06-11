#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#define TIMER_MS(ms) (ms/10)
#define TIMER_ERR (timer_handler_t)-1

#define N 20 // Max. accions planificades


typedef void (*timer_callback_t)(void);

typedef int8_t timer_handler_t;

typedef struct {
    uint16_t remaining, every, ntimes;
    timer_callback_t callback;
} entry;

void timer_init(void);

timer_handler_t timer_after(uint16_t ticks, timer_callback_t f);

timer_handler_t timer_every(uint16_t ticks, timer_callback_t f);

timer_handler_t timer_ntimes(uint8_t n, uint16_t ticks, timer_callback_t f);

void timer_cancel(timer_handler_t h);

void timer_cancel_all(void);
#endif