/*
Developer: Izan Hernandez (4−juny−2024)
Revised: Izan Hernandez (23-juny-2024)
*/

#include "mchar.h"

// Afegeix un senyal (punt o guió) a un caràcter Morse.
mchar_t mchar_add(mchar_t m, msign_t s) {

  if (mchar_len(m) < 5) {

    if (s == MDot) 
      m &= ~(1<<(7-(mchar_len(m))));
    else
      m |= (1 << (7 - mchar_len(m)));

    m++;
  }

  return m;
}

// Inicialitza un iterador per a un caràcter Morse.
mchar_iter_t mchar_iter(mchar_t m) {
  mchar_iter_t i;
  i.m = m;
  i.mask = 0x80; // bit 7 = 1
  i.sentinel = (1 << (7 - mchar_len(m)));
  return i;
}

// Retorna el següent senyal (punt o guió) de l'iterador.
msign_t mchar_next(mchar_iter_t *const i) {
  msign_t s;

  if (i->m & i->mask)
    s = MDash;
  else
    s = MDot;

  i->mask >>= 1;
  return s;
}

// Comprova si l'iterador és vàlid (si hi ha més senyals).
bool mchar_valid(mchar_iter_t i) {
  return !(i.mask == i.sentinel);
}
