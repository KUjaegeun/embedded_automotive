/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

		                                 2���� �ǽð� ���ͷ�Ʈ �ǽ�    


1. GENERAL DESCRIPTION : 2���� �ǽð� ���ͷ�Ʈ �ǽ�  
2. GENERAL ENVIRONMENT : Window XP / Metrowerks CodeWarrior 3.1 ( Target Board )
3. DEVELOPMENT NOTE
   1) Development Environment : Window XP / MC9S12DP256 Board
   2) Development Tool : Metrowerks CodeWarrior 3.1 ( Target Board )
   3) Edito : Metrowerks CodeWarrior 3.1 ( Target Board )
   4) Target MCU : MC9S12DP256 (16bit)
   
4. Project Description: �ǽð� ���ͷ�Ʈ ����Ͽ� led ���������� ����Ʈ �Ǵ� �ӵ� ������ 

5. HISTORY 
   /*****************************************************************************/
   /*YYYY-MM-DD   Version        Name                   Description             */
   /*2008-10-18     1.0      Automation Lab             2���� �ǽð� ���ͷ�Ʈ �ǽ�   */
   /*****************************************************************************

6. REFERENCES : Copyright(c) 1994-2008 Automation Lab. All Rights Reserved.

*====*====*=====*====*====*====*====*====*====*====*====*====*====*====*====*/

#include "main.h"
#include <stdlib.h>

#define MAX_STRING 15


// buffer for SCI
char sci_rx_buffer[MAX_STRING+1];
char sci_tx_buffer[MAX_STRING*2];

/* ���� ��ƾ�� �ʹ� ��� �ǽð� ���е��� ��������!! */
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