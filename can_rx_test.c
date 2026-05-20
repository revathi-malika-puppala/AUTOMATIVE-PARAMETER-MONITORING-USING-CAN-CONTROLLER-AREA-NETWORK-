//can_rx_test.c
#include<LPC21xx.h>
#include "can.h"
#include "types.h"
#include "delay.h"
CANF rxF;
main()
{
	Init_CAN1();
	IODIR0|=((1<<5)|(1<<6));
	while(1)
	{
  	CAN1_Rx(&rxF);
	if(rxF.Data1==1)
		IOPIN0^=1<<5;
	else
		IOPIN0^=1<<6;
	}	
}
