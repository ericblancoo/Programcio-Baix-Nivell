/*
Developer: Eric Blanco (25−maig−2024)
Revised: Izan Hernandez (23-juny-2024)
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "control.h"
#include <util/atomic.h>
#include <util/delay.h>

#define TICK_CLEAR 80
#define TICK_APPROACH 20

static int ticks = 0;


// SEMAFOR A
static pin_t greenA;
static pin_t yellowA;
static pin_t redA;
static lamp_t lampA;
static semaph_t SemaforA;

// SEMAFOR B
static pin_t greenB;
static pin_t yellowB;
static pin_t redB;
static lamp_t lampB;
static semaph_t SemaforB;
static timer_handler_t h;

static enum { Aclear, Bclear, AtoB, BtoA, ABoff } state;//


static void interrupt_routine(void) {
    --ticks;
    if (ticks == 0) {
        
        if (state == Aclear) {
            
            semaph_set(&SemaforA, SemApproach);
            ticks = TICK_APPROACH;
            state = AtoB;

        } else if (state == AtoB) {
            
            semaph_set(&SemaforA, SemStop);
            semaph_set(&SemaforB, SemClear);
            ticks = TICK_APPROACH + TICK_CLEAR;
            state = Bclear;

        } else if (state == Bclear) {
            
            semaph_set(&SemaforB, SemApproach);
            ticks = TICK_APPROACH;
            state = BtoA;

        } else if (state == BtoA) {
           
            semaph_set(&SemaforA, SemClear);
            semaph_set(&SemaforB, SemStop);
            ticks = TICK_CLEAR;
            state = Aclear;
        }
    }
}

void control_init(void){
    state = ABoff; // Semafors apagats inicialment

    // Timer
    timer_init();

    // Semafor A
    greenA =    pin_bind(&PORTD, 5, Output);
    yellowA =   pin_bind(&PORTD, 6, Output);
    redA =      pin_bind(&PORTD, 7, Output);
    lamp_bind(&lampA, greenA, yellowA, redA);
    SemaforA = semaph_bind(&lampA); 

    // Semafor B
    greenB =    pin_bind(&PORTD, 4, Output);
    yellowB =   pin_bind(&PORTC, 3, Output);
    redB =      pin_bind(&PORTC, 2, Output);
    lamp_bind(&lampB, greenB, yellowB, redB);
    SemaforB = semaph_bind(&lampB); 
}

void control_force(street_t t) {
    if (state != ABoff){
        if (t == StreetA){
            if (state == Bclear) {
	            semaph_set(&SemaforB, SemApproach);
	            ticks = TICK_APPROACH;
	            state = BtoA;

            } else if(state == Aclear) {
	            ticks = TICK_CLEAR;

            } else if(state = AtoB) {
                semaph_set(&SemaforA, SemClear);
                ticks = TICK_CLEAR;
                state = Aclear;
            }
        } else {
            if (state == Aclear) {
                semaph_set(&SemaforA, SemApproach);
                ticks = TICK_APPROACH;
	            state = AtoB;

            } else if(state == Bclear) {
	            ticks = TICK_APPROACH + TICK_CLEAR;

            } else if(state = BtoA){
                semaph_set(&SemaforB, SemClear);
                ticks = TICK_APPROACH + TICK_CLEAR;
                state = Bclear;
            }  
        }
    }
}

void control_off(void){
    if (state != ABoff){
        semaph_set(&SemaforA, SemOff);
        semaph_set(&SemaforB, SemOff);
        state = ABoff;
    }
}

void control_on(void){
    if (state == ABoff){
        semaph_set(&SemaforA,SemClear);
        semaph_set(&SemaforB,SemStop);
        ticks = TICK_CLEAR;
        h = timer_every(TIMER_MS(100), interrupt_routine);
        state = Aclear;
    }
}

semaph_state_t control_get_state(street_t s){
    if (s == StreetA)
        return semaph_get(SemaforA);

    else
        return semaph_get(SemaforB);
}


