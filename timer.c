// (funciona)

#include "timer.h"



static struct {
    entry t[N]; // 20
    uint8_t n;
} tt;


// Inicialització timer, cridar amb interupcions desactivades.
void timer_init(void) {
    // CTC mode.
    TCCR0A = 0b00000010;

    // Presc (1024)
    TCCR0B = 0b00000101;
    OCR0A = 156;

    //Int.OCIE0A desactivada
    TIMSK0 = 0b00000000;

    //Inicialitzacio task table
    int i;
    tt.n = 0;

    for (i = 0; i < N; i++)
        tt.t[i].every = 0;
}


timer_handler_t timer_after(uint16_t ticks, timer_callback_t f) {
    // Planifiquem la funció f per executarla al cap de 'tick' ticks JUST ONCE.
    timer_handler_t th;

    // Afegir la tasca en el primer lloc buit
    if (tt.n < N) {
        for (th = 0; th < N; th++) {
            if (tt.t[th].every == 0) // En el cas de que no hi haguin entris, fem un break.
                break;
        }

        // Actuaitzem els valors pper la tasca th del for anterior.
        tt.t[th].remaining = ticks;
        tt.t[th].every = ticks;
        tt.t[th].ntimes = 1;
        tt.t[th].callback = f; // PSab
        ++(tt.n);

        if (tt.n == 1) {
            // Int.OCIE0A activada.
            TIMSK0 |= 0b00000010; 
        }

        return th;
    }
    return TIMER_ERR;
}


timer_handler_t timer_every(uint16_t ticks, timer_callback_t f) {
    // Planifiquem la funció f per executarla al cap de 'tick' ticks de manera indefinida.
    timer_handler_t th;
    th = timer_after(ticks, f);

    if (th != TIMER_ERR) {
        // Quan ho posem 0, vol dir infinites vegades al cap de 'tick' ticks.
        tt.t[th].ntimes = 0;
        return th;
    }

    return th;
}


timer_handler_t timer_ntimes(uint8_t n, uint16_t ticks, timer_callback_t f) {
    // Planifiquem la funció f per executarla al cap de 'tick' ticks n vegades.
    timer_handler_t th;
    th = timer_after(ticks, f);

    if (th != TIMER_ERR) {
        // Li diem el nombre de vegades que volem que repeteixi la funció.
        tt.t[th].ntimes = n;
        return th;
    }

    return th;  
}


void timer_cancel(timer_handler_t h) {
    // Parem la acció identificada com a h.
    tt.t[h].every = 0;
    --(tt.n);
}


void timer_cancel_all(void) {
    // Cancela totes les accions planificades.
    int h;

    for (h = 0; h < N; h++) {
        
        if (tt.t[h].every != 0)
        timer_cancel(h);
    }
}


ISR(TIMER0_COMPA_vect) {
    
    int i;

    for (i = 0; i < N; i++) {

        if (tt.t[i].every != 0) {
            --(tt.t[i].remaining);

            if (tt.t[i].remaining == 0) {
                tt.t[i].callback();

                // Exec. infinita
                if (tt.t[i].ntimes == 0)
                    tt.t[i].remaining = tt.t[i].every;
                
                // Exec. unica
                else if (tt.t[i].ntimes == 1) {
                    tt.t[i].every = 0;
                    --(tt.n);

                    if (tt.n == 0)
                        //Int.OCIE0A desactivada perque no queden tasques per fer (n).
                        TIMSK0 &= 0b11111101; 
                } 

                // ntimes exec.
                else if (tt.t[i].ntimes > 1) {
                    --(tt.t[i].ntimes);
                    tt.t[i].remaining = tt.t[i].every;	
                }
            }
        }
    }
}