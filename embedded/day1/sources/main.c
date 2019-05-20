#include "main.h"
#define REVERSE 1

void main ()
{
  unsigned int loop;
  unsigned char ledvalue = 1;
  unsigned int change = 0;
  init_portb(1);
	//Insert Application Software Here.
	for (;;){
	  
	  set_portb(REVERSE, ledvalue);
	  for(loop =1; loop !=0;loop++)
	   continue;
	  if(change == 0)
	    ledvalue = ledvalue * 2;
	  else
	    ledvalue = ledvalue /2;
	  if(ledvalue == 128){
	    set_portb(REVERSE, ledvalue);
	    change = 1;
	  } else if(ledvalue == 1)
	      change = 0;
	  for(loop =1; loop !=0;loop++)
	    continue;
	  
	}
}