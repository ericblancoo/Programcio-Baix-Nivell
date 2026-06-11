#ifndef BLCK_SERIAL_H
#define BLCK_SERIAL_H

#include "serial_device.h"
#include <stdint.h>

uint8_t print(const char s[]);

uint8_t reads(char s[], uint8_t m);

#endif
