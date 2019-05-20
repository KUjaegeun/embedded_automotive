/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

		                                 2일차 실시간 인터럽트 실습    


1. GENERAL DESCRIPTION : 2일차 실시간 인터럽트 실습  
2. GENERAL ENVIRONMENT : Window XP / Metrowerks CodeWarrior 3.1 ( Target Board )
3. DEVELOPMENT NOTE
   1) Development Environment : Window XP / MC9S12DP256 Board
   2) Development Tool : Metrowerks CodeWarrior 3.1 ( Target Board )
   3) Edito : Metrowerks CodeWarrior 3.1 ( Target Board )
   4) Target MCU : MC9S12DP256 (16bit)
   
4. Project Description: 실시간 인터럽트 사용하여 led 오른쪽으로 쉬프트 되는 속도 빨라짐 

5. HISTORY 
   /*****************************************************************************/
   /*YYYY-MM-DD   Version        Name                   Description             */
   /*2008-10-18     1.0      Automation Lab             2일차 실시간 인터럽트 실습   */
   /*****************************************************************************

6. REFERENCES : Copyright(c) 1994-2008 Automation Lab. All Rights Reserved.

*====*====*=====*====*====*====*====*====*====*====*====*====*====*====*====*/

#include "main.h"
#include <stdlib.h>

#define MAX_STRING 15


// buffer for SCI
char sci_rx_buffer[MAX_STRING+1];
char sci_tx_buffer[MAX_STRING*2];

/* 서비스 루틴이 너무 길면 실시간 정밀도가 떨어진다!! */
void rti_service(void) 
{
   static unsigned char led_var = 1;
   
   set_portb(1,led_var);
   
   led_var = led_var * 2;
   
   if(led_var == 0){
   
    led_var = 1;
   
   }
   
}


void main ()
{
  init_portb(1);
  set_portb(1, 0x00);

  int_enable();
  init_rti(2000);


	for (;;) {

    continue;
	}
	
	return;
	
}