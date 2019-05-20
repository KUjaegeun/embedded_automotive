#include "atd.h"

void init_atd0(void) {
    // initialize ADC0
  Atd0.atdctl2.byte = 0x80;
  Atd0.atdctl3.byte = 0x20;
  Atd0.atdctl4.byte = 0x85;
  Atd0.atdctl5.byte = 0xe0;
  Atd0.atddien0.byte = 0xff;
}


int get_atd0(int channel) 
{
  
  if (channel >= 0 && channel <= 7)
    return (int)(Atd0.atddr[channel].d10);
  else
    return -1;
  
}



