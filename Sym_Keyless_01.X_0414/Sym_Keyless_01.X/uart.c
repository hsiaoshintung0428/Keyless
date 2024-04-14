#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "global.h"
#include "mcu.h"
#include "ioports.h"

#include "TMR.h"
#include "uart.h"

#define TX_init TRISBbits.TRISB5  //RB5 
#define RX_init TRISBbits.TRISB4  //RB4

#define Fosc  mFOSC//石英整盪器頻率
#define Speed 115200    //電腦通訊速度
#define Brate (uint32_t)((Fosc/Speed/4)-1)

const  uint8_t disNumber[]={'0','1','2','3','4','5',
	               	   '6','7','8','9','A','B',
	               	   'C','D','E','F','X',
                      };

void Init_uart(void)
{
  word temp ;
  //異同
  TX1STA=0b00100100;//啟動發送模組;
                  //8位元高速傳輸;
  RC1STA=0b10010000;//啟動接收模組
                  //8位元接收
  BAUD1CON=0x08; //16位元
 
//temp.w = Brate ;
temp.w = 68;
  TX_init = 0;
  RX_init = 1;
  //SP1BRGH = temp.b.msb ;
  //SP1BRG  = temp.b.lsb;
  SP1BRGH = Brate>>8;
  SP1BRG  = Brate&0xFF;
}

void PutChar(unsigned char data)
{
 while (PIR1bits.TXIF== 0){}
 TX1REG =data;  //傳輸暫存器(TXREG)
}

void Putdata (uint8_t *data)
{
 while (*data !=0)
 {
  PutChar (*data++);
 } 
}




unsigned char GetChat (void)
{  
 unsigned char TMP ;
 TMP = RCSTA & 0x06;//?
 if (TMP != 0 )
 {
  RCSTA =0;
  TMP = RCSTA ;
  RCSTA = 0x90;
 }
 while (PIR1bits.RCIF ==0){ }
 return RCREG ; //返回接收暫存器(RCREG)
}

void CLS (void) //函式功能不回傳數值
{
 Putdata("\x1B[2J");  //清除pc螢幕
}

void PutNext (void) 
{
 Putdata("\r\n");  //換行
}


void DumpintDec (uint32_t data) 
{
     //MAX=4294967295
    uint8_t num[10]={4,2,9,4,9,6,7,2,9,5};
    //0004.808192
    num[0]=disNumber[data/1000000000L];
    //-USART1_SENDbyte(num[0]);
    num[1]=disNumber[(data%1000000000)/100000000L];
    //-USART1_SENDbyte(num[1]);
    num[2]=disNumber[(data%100000000)/10000000L];
    //-USART1_SENDbyte(num[2]);
    if(num[0]=='0')
    {
        PutChar(' ');
        if(num[1]=='0')
        {
            PutChar(' ');
            if(num[2]=='0')
            {
                PutChar(' ');
            }
            else
            {
                PutChar(num[2]);
            }
            
        }
        else
        {
            PutChar(num[1]);
            PutChar(num[2]);
        }
    }
    else
    {
       PutChar(num[0]);
       PutChar(num[1]);
       PutChar(num[2]);
    }
    
    num[3]=disNumber[(data%10000000)/1000000L];
    PutChar(num[3]);
    PutChar('.');
    num[4]=disNumber[(data%1000000)/100000L];
    PutChar(num[4]);
    num[5]=disNumber[(data%100000)/10000];
    PutChar(num[5]);
    num[6]=disNumber[(data%10000)/1000];
    PutChar(num[6]);
    num[7]=disNumber[(data%1000)/100];
    PutChar(num[7]);
    num[8]=disNumber[(data%100)/10];
    PutChar(num[8]);
    num[9]=disNumber[(data%10)];
    PutChar(num[9]);  
}

void USART1_HEX(uint8_t data)
{
    PutChar(disNumber[data>>4]);
    PutChar(disNumber[data&0x0F]);
}



