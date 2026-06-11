
#include <util/atomic.h>

#include "ether.h"

static queue_t queue_tx;
static mchar_iter_t i;

static enum {run, stop} action = stop;
static enum {estat1, estat2} estat;

static void punt(void);
static void ratlla(void);
static void low(void);
static void convert_morse(void);

static void punt(void) {
    modulator_set(true);
    timer_after(TIMER_MS(DOT), low);
}

static void ratlla(void) {
    modulator_set(true);
    timer_after(TIMER_MS(DASH), low);
}

static void low(void) { 
    modulator_set(false);
    if (mchar_valid(i)) {
        if(mchar_next(&i) == MDot) {
            timer_after(TIMER_MS(GAP), punt);
        } else {
            timer_after(TIMER_MS(GAP), ratlla);
        }
    } else {
        if (!queue_is_empty(&queue_tx)) {
            timer_after(TIMER_MS(LETTERGAP), convert_morse);
        } else {
            action = stop;
        }
    }
}

static void convert_morse(void) { // converteix a morse i cridem punt o ratlla
    if (!queue_is_empty(&queue_tx)) {
        i = mchar_iter(mtbl_a2m(queue_front(&queue_tx))); // convertim de ascii a morse el front de queue_tx
        queue_dequeue(&queue_tx);
        if (mchar_valid(i)) {
            if (mchar_next(&i) == MDot) {
                punt();
            } else {
                ratlla();
            }
        }
    }
}

void ether_open(void) { // Inicialitza el mòdul i deixa el sistema a punt per enviar caràcters morse.
    queue_empty(&queue_tx);
    init_mtbl();
    modulator_init();
    timer_init();
    sei();  // Habilitar interrupciones globales
    estat = estat1;
}

void ether_close(void) { // Deshabilita la comunicació morse.
    while (action == stop);
}

void ether_put(uint8_t c) { // Envia el caràcter c usant el canal Morse.
    while (queue_is_full(&queue_tx)); // mirem si la cua està plena
    
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        queue_enqueue(&queue_tx, c); // afegim c a la cua
    }
    
    if (action == stop) {
        convert_morse();
        action = run;
    }
}

bool ether_can_put(void) { // Retorna true sii és possible enviar un caràcter pel port sèrie
    return !(queue_is_full(&queue_tx));
}