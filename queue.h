#ifndef QUEUE_H
#define QUEUE_H

#include <stdint.h>
#include <stdbool.h>
#define QUEUE_SIZE 60


typedef struct {
    uint8_t buffer[QUEUE_SIZE];
    uint8_t primer;
    uint8_t ultim;
    bool empty;
    bool full;
} queue_t;

void queue_empty(queue_t *const q);
bool queue_is_empty(const queue_t *const q);
bool queue_is_full(const queue_t *const q);
void queue_enqueue(queue_t *const q, uint8_t v);
void queue_dequeue(queue_t *const q);
uint8_t queue_front(const queue_t *const q);

#endif