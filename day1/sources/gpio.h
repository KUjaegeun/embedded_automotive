#ifndef GPIO_H
#define GPIO_H

#include "projectglobals.h"

void init_portb(int direction);
void set_portb(int reverse, unsigned char data);
unsigned char get_portb(void);

#endif