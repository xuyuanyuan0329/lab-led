#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "usart.h"


 int main(void)
 {
	u8 t;
	u8 len;	
	u16 times=0;  	
 	SystemInit();//系统时钟等初始化
	delay_init(72);	     //延时初始化
	NVIC_Configuration();//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);//串口初始化为9600
 	LED_Init();	 //LED端口初始化
	printf("蓝牙控制LED\r\n"); 
	 LED0=0;
	 LED1=0;
	while(1)
	{
		//printf("蓝牙控制LED\r\n");
	  switch(Bluetooth_data)
		{
            case  0x01: LED0=!LED0;
                        break; 
						case  0x02: LED1=!LED1;
												break;
					  case  0x03: LED0=!LED0;LED1=!LED1;
					 			        break;
    }
	}	 

 }
 
 					 
// 		switch(BUF_RX_PID)
//  		
// 		{

//  				case 0x02:k=2;	break; //前进标志
// 				
//  			    case 0x01: k=1; break;//后退标志
//  			
//  				case 0x00: k=0;	break;//停止标志
//  						
//  				case 0x03: k=3;	break;//左转标志
// 				
// 				case 0x04: k=4;	break;//右转标志
//  			    
//  				case 0x05: k=5;	break;//原地高速左转标志
// 				
// 				case 0x06: k=6;	break;//原地高速右转标志
//           
//              	case 0x07: k=7;	break;//原地低速右转标志

// 				case 0x08: k=8;	break;//原地低速标志
//  		}

