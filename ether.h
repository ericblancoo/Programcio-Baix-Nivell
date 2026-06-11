
/*
Developer: Roger Escudero (22-05-2022)
Revised: 
*/
#ifndef ETHER_H
#define ETHER_H


#include "queue.h"
#include "modulator.h"
#include "mtbl.h"
#include "timer.h"
#include "mchar.h"

#define DOT 50
#define GAP DOT
#define LETTERGAP 3*DOT
#define DASH 3*DOT

void ether_open(void);
void ether_close(void);
void ether_put(uint8_t c);
bool ether_can_put(void);

#endif