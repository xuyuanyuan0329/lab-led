#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "usart.h"

//ALIENTEK Mini STM32�����巶������3
//����ʵ��
//������̳:www.openedv.com	

 int main(void)
 {
	u8 t;
	u8 len;	
	u16 times=0;  	
 	SystemInit();//ϵͳʱ�ӵȳ�ʼ��
	delay_init(72);	     //��ʱ��ʼ��
	NVIC_Configuration();//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);//���ڳ�ʼ��Ϊ9600
 	LED_Init();	 //LED�˿ڳ�ʼ��
	printf("��������LED\r\n"); 
	 LED0=0;
	 LED1=0;
	while(1)
	{
		//printf("��������LED\r\n");
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

//  				case 0x02:k=2;	break; //ǰ����־
// 				
//  			    case 0x01: k=1; break;//���˱�־
//  			
//  				case 0x00: k=0;	break;//ֹͣ��־
//  						
//  				case 0x03: k=3;	break;//��ת��־
// 				
// 				case 0x04: k=4;	break;//��ת��־
//  			    
//  				case 0x05: k=5;	break;//ԭ�ظ�����ת��־
// 				
// 				case 0x06: k=6;	break;//ԭ�ظ�����ת��־
//           
//              	case 0x07: k=7;	break;//ԭ�ص�����ת��־

// 				case 0x08: k=8;	break;//ԭ�ص��ٱ�־
//  		}

