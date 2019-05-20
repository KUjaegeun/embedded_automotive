#include "rti.h"

int scaler;
int speed_reg = 0x1F;

// s : scaler by 0.5ms
// eg) s=2000 -> 0.5*2000 = 1s
void init_rti(int s)
{
	scaler = s;
	Crg.rtictl.byte = speed_reg;
	Crg.crgint.byte |= RTIE;
}


void rti_handler(void)
{
	static int count = 0;
	
	count++;

	if (count >= scaler) {
		// process task
		rti_service();
		count = 0;

	
		Crg.rtictl.byte = speed_reg;
		
		
	
		if(speed_reg > 0x10)      		
		{
	  	
		  speed_reg--;
		}
		
	}
	// clear flag
	Crg.crgflg.byte |= RTIF;

}
