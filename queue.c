/*
Developer: Eric Blanco (23−maig−2024)
Revised: Izan Hernandez (23-juny-2024)
*/

#include <util/atomic.h>
#include "queue.h"
#define QUEUE_SIZE 60


void queue_empty(queue_t *const q) {
    q->primer = 0;
    q->ultim = 0;
    q->empty = true;
    q->full = false;
    return;
}

bool queue_is_empty(const queue_t *const q) {
    return q->empty;
}

bool queue_is_full(const queue_t *const q) {
    return q->full;
}
// encolem variable a la cua (primer)
void queue_enqueue(queue_t *const q, uint8_t v) {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        if (!q->full) {
            q->buffer[q->primer] = v;
            q->primer = (q->primer + 1) % QUEUE_SIZE;
            if (q->primer == q->ultim) {
                q->full = true;
            }
            q->empty = false;
        }
    }
    return;
}
// desencolem variable (ultim)
void queue_dequeue(queue_t *const q) {
   ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        if (!q->empty) {
            q->ultim = (q->ultim + 1) % QUEUE_SIZE;
            if (q->primer == q->ultim) {
                q->empty = true;
            }
            q->full = false;
        }
    }
    return;
}

uint8_t queue_front(const queue_t *const q) {
    return q->buffer[q->ultim];
}