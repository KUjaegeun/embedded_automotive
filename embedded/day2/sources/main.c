   
/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

		                                 2일차 시리얼 통신 실습


1. GENERAL DESCRIPTION : 2일차 시리얼 통신 실습  
2. GENERAL ENVIRONMENT : Window XP / Metrowerks CodeWarrior 3.1 ( Target Board )
3. DEVELOPMENT NOTE
   1) Development Environment : Window XP / MC9S12DP256 Board
   2) Development Tool : Metrowerks CodeWarrior 3.1 ( Target Board )
   3) Edito : Metrowerks CodeWarrior 3.1 ( Target Board )
   4) Target MCU : MC9S12DP256 (16bit)
   
4. Project Description: L정수 값을 송신 받으면 정수 값이 LED출력 

5. HISTORY 
   /*****************************************************************************/
   /*YYYY-MM-DD   Version        Name                   Description             */
   /*2008-10-18     1.0      Automation Lab             2일차 시리얼 통신 예제  */
   /*****************************************************************************

6. REFERENCES : Copyright(c) 1994-2008 Automation Lab. All Rights Reserved.

*====*====*=====*====*====*====*====*====*====*====*====*====*====*====*====*/

#include "main.h"
#include <stdlib.h>

#define MAX_STRING 15

// buffer for SCI
char sci_rx_buffer[MAX_STRING+1];
char sci_tx_buffer[MAX_STRING*2];


void main ()
{

  init_sci0(19200, sci_rx_buffer, MAX_STRING);
  init_portb(1);
  int_enable();
  write_sci0("SCI OK$", 7);
  
	for (;;) {
  
    continue;
 
 	}
	
	return;
	
}