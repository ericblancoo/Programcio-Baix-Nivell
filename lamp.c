/*
Developer: Eric Blanco (20−maig−2024)
Revised: Izan Hernandez (23-juny-2024)
*/

#include "lamp.h"

// Associa els pins als colors de la llum.
void lamp_bind(lamp_t *const l, pin_t p_green, pin_t p_yellow, pin_t p_red) {
    l->green = p_green;
    l->yellow = p_yellow;
    l->red = p_red;
}

// Encén la llum del color especificat.
void lamp_on(lamp_t *const l, color_t c) {
    switch (c) {
        case Green:
            pin_write(l->green, 1);
            break;
        case Yellow:
            pin_write(l->yellow, 1);
            break;
        case Red:
            pin_write(l->red, 1);
            break;
    }
}

// Apaga la llum del color especificat.
void lamp_off(lamp_t *const l, color_t c) {
    switch (c) {
        case Green:
            pin_write(l->green, 0);
            break;
        case Yellow:
            pin_write(l->yellow, 0);
            break;
        case Red:
            pin_write(l->red, 0);
            break;
    }
}

// Canvia l'estat de la llum del color especificat.
void lamp_toggle(lamp_t *const l, color_t c) {
    switch (c) {
        case Green:
            pin_toggle(l->green);
            break;
        case Yellow:
            pin_toggle(l->yellow);
            break;
        case Red:
            pin_toggle(l->red);
            break;
    }
}

// Comprova si la llum del color especificat està encesa.
bool lamp_is_on(const lamp_t *const l, color_t c) {
    switch (c) {
        case Green:
            return pin_read(l->green);
        case Yellow:
            return pin_read(l->yellow);
        case Red:
            return pin_read(l->red);
        default:
            return false;
    }
}

// Desassocia els pins dels colors de la llum.
void lamp_unbind(lamp_t *const l) {
    pin_unbind(&(l->green));
    pin_unbind(&(l->yellow));
    pin_unbind(&(l->red));
}
