#ifndef MODULATOR_H
#define MODULATOR_H
#include <avr/io.h>
#include <stdbool.h>


//Inicialitza el m`odul. Despr´es de la inicialitzaci´o el senyal de sortida ´es baix.
void modulator_init(void);
//Canvia l’estat del senyal de sortida. Si l ´es true activa la generaci´o de portadora, si ´es false desactiva la generaci´o de portadora.
void modulator_set(bool l);
#endif