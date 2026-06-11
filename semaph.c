
/*
Developer: Eric Blanco (22−maig−2024)
Revised: Izan Hernandez (23-juny-2024)
*/

#include "semaph.h"

// Associa un semàfor a una llum.
semaph_t semaph_bind(lamp_t *const lamp) {
    semaph_t sem;

    sem.l = lamp;
    sem.s = SemOff;
    return sem;
}

// Estableix l'estat del semàfor.
void semaph_set(semaph_t *const sem, semaph_state_t s) {
    sem->s = s;
    switch (s) {
        case SemOff:
            lamp_off(sem->l, Green);
            lamp_off(sem->l, Yellow);
            lamp_off(sem->l, Red);
            break;
        case SemClear:
            lamp_on(sem->l, Green);
            lamp_off(sem->l, Yellow);
            lamp_off(sem->l, Red);
            break;
        case SemApproach:
            lamp_off(sem->l, Green);
            lamp_on(sem->l, Yellow);
            lamp_off(sem->l, Red);
            break;
        case SemStop:
            lamp_off(sem->l, Green);
            lamp_off(sem->l, Yellow);
            lamp_on(sem->l, Red);
            break;
    }
}


// Obté l'estat actual del semàfor.
semaph_state_t semaph_get(const semaph_t sem) {
    return sem.s;
}

// Desassocia el semàfor de la llum.
void semaph_unbind(semaph_t *const sem) {
  sem->l = NULL;
  sem->s = SemOff;
}
