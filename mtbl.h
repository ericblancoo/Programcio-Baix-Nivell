#ifndef MTBL_H
#define MTBL_H

#define MAX 40

#include "mchar.h"

typedef struct{
  mchar_t morse;
  char ascii;
} conversion_table[MAX];

void init_mtbl(void);
void empty_table(void);
void convert(char c, mchar_t m);
char mtbl_m2a(mchar_t c);
mchar_t mtbl_a2m(char c); 
#endif