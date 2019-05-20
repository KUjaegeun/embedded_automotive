#include "sci.h"


char *txbuffer_sci0;
int txoffset_sci0;

unsigned char *rxbuffer_sci0;

unsigned char led_flag=0;

int rxoffset_sci0;
int __atoi(char *p);

 
void init_sci0(int baud_rate, char *rxbuf, int rx_max) 
{

  unsigned long oscclk, busclk;
  unsigned short bd;

	oscclk = 16000000;						// Set Oscillator Freq. = 16 MHz
  busclk = oscclk/2;					// Set Bus Freq. = (1/2) * Oscillator Freq.

  bd = (unsigned short)((busclk / 16) / baud_rate);   
  Sci0.scibd.word = bd;  
  
  Sci0.scicr1.byte = 0x0;
  Sci0.scicr2.byte = TE + RE + RIE;          /* enable both the transmitter & receiver */ 

	txoffset_sci0 = 0;
	rxbuffer_sci0 = rxbuf;
	rxoffset_sci0 = rx_max;

  return;
}


void write_sci0(char *text, int length)
{
	txbuffer_sci0 = text;
	txoffset_sci0 = length;
	Sci0.scicr2.byte += TIE;
	
}


void sci0_handler(void)  //시리얼 통신의 인터럽트 서비스 루틴
{
  static unsigned char i=0; /* index into command */
	static int j = 0; // index of transmition buffer
	static int k = 0; // index of led ASCII value
	static unsigned char ledbuffer_sci0[3];
	unsigned char status;
  unsigned char rc;
  int m;

  
	status = Sci0.scisr1.byte;
	
	if ( (status & RDRF) != 0) {  //데이터 수신시 처리 부분  
	 	rc = Sci0.scidrl.byte; /* data read */

		rxbuffer_sci0[i] = rc;
		                                         	  
		
		if (rc == 'L') {
		
	    led_flag = 1;
		  
		}
		
	  i++;
	  
	  if (rc == '$'){
	    
	    if (led_flag == 1) {
		
		  //write your code//
		  
		  //버퍼값을 옮겨준다.

		    for(m=0;m<(i-2);m++){
		    
	      ledbuffer_sci0[m] =	rxbuffer_sci0[m+1];   // A를 알맞은 수식으로 바꾸시오
	      		    
		    }

		  }
   
	    //버퍼에 있는 ASCII값을 __atoi함수로 integer값으로 바꿔 set_portb함수로 출력한다.
	    
	    set_portb(led_flag,__atoi(ledbuffer_sci0));			//B를 알맞은 변수로 바꾸시오
	    	    
	    //write your code//
	    
	    led_flag = 0;
	    k=0;
	    i=0;
	    for(m=0;m<5;m++){
		    
	      ledbuffer_sci0[m] = 0;	
	      rxbuffer_sci0[m] = 0;  		    
		  }
		  
		  
	  }
		
	
		
	} /* end of "if ( (status & RDRF) != 0) {" */
	
	// ready to transmit a data
	if ( (status & TDRE) != 0) 
	{  //데이터 송신시 처리 부분  
		if (j >= txoffset_sci0) 
		{
			Sci0.scicr2.byte = Sci0.scicr2.byte & ~TIE; // mask interrupt
			txoffset_sci0 = 0;
			j = 0; // clear index
		} 
		else 
		{
			Sci0.scidrl.byte = txbuffer_sci0[j]; // send a data
			j++; // increase index
		} /* end of "if (j >= txoffset_sci0) {" */
	} /* end of "if ( (status & TDRE) != 0) {" */
	
	return;
  
}

int __atoi(char *p)
{
	int n;
	int f;

	n = 0;
	f = 0;
	for(;;p++) {
		switch(*p) {
		case ' ':
		case '\t':
			continue;
		case '-':
			f++;
		case '+':
			p++;
		}
		break;
	}
	while(*p >= '0' && *p <= '9')
		n = n*10 + *p++ - '0';
	return(f? -n: n);
}
  