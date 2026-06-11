/*
Developer: Izan Hernandez (4−juny−2024)
Revised: Izan Hernandez (23-juny-2024)
*/

#include "mtbl.h"

static conversion_table t;


// Inicialitza la taula de conversió amb els codis Morse corresponents.
void init_mtbl(void){
  empty_table();
  convert('A', mchar(01));
  convert('B', mchar(1000));
  convert('C', mchar(1010));
  convert('D', mchar(100));
  convert('E', mchar(0));
  convert('F', mchar(0010));
  convert('G', mchar(110));
  convert('H', mchar(0000));
  convert('I', mchar(00));
  convert('J', mchar(0111));
  convert('K', mchar(101));
  convert('L', mchar(0100));
  convert('M', mchar(11));
  convert('N', mchar(10));
  convert('O', mchar(111));
  convert('P', mchar(0110));
  convert('Q', mchar(1101));
  convert('R', mchar(010));
  convert('S', mchar(000));
  convert('T', mchar(1));
  convert('U', mchar(001));
  convert('V', mchar(0001));
  convert('W', mchar(011));
  convert('X', mchar(1001));
  convert('Y', mchar(1011));
  convert('Z', mchar(1100));
  convert('0', mchar(11111));
  convert('1', mchar(01111));
  convert('2', mchar(00111));
  convert('3', mchar(00011));
  convert('4', mchar(00001));
  convert('5', mchar(00000));
  convert('6', mchar(10000));
  convert('7', mchar(11000));
  convert('8', mchar(11100));
  convert('9', mchar(11110));
  convert(' ', mchar(01010));
}

// Buida la taula de conversió.
void empty_table(void){
  for (int i = 0; i < MAX; i++){
    t[i].morse = mchar_empty;
    t[i].ascii = '-';
  }
}

// Afegeix una conversió de caràcter ASCII a codi Morse a la taula.
void convert(char c, mchar_t m){
  int i;
  for (i = 0; t[i].morse != mchar_empty; i++);
  t[i].morse = m;
  t[i].ascii = c;
}

// Converteix un codi Morse a un caràcter ASCII.
char mtbl_m2a(mchar_t c){
  int i;
  for (i = 0; i < MAX; i++){
    if (c == t[i].morse)
      return t[i].ascii;
  }
  return 0;
}

// Converteix un caràcter ASCII a un codi Morse.
mchar_t mtbl_a2m(char c){
  int i;
  for (i = 0; i < MAX; i++){
    if (c == t[i].ascii)
      return t[i].morse;
  }
  return mchar_empty;
}
