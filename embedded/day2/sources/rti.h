#ifndef RTI_H        /*prevent duplicated includes*/
#define RTI_H

/*Includes*/
#include "projectglobals.h"

void init_rti(int s, void (*fpointer)(void));
void rti_handler(void);

#endif /*RTI_H*/
