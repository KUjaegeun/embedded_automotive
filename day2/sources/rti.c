#include "rti.h"


int scaler;
void (*rti_routine)(void);

// s : scaler by 0.5ms
// eg) s=2000 -> 0.5*2000 = 1s
// fpointer : When rti handler is invoked, this function is invoked
void init_rti(int s, void (*fpointer)(void))
{
	scaler = s;
	Crg.rtictl.byte = 0x17;
	rti_routine = fpointer;
	Crg.crgint.byte |= RTIE;
	
}


void rti_handler(void)
{
	static int count = 0;
	
	count++;

	if (count >= scaler) {
		// process task
		(*rti_routine)();
		count = 0;
	}
	// clear flag
	Crg.crgflg.byte |= RTIF;

}
