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

#define Fosc  8000000//石英整盪器頻率
#define Speed 9600    //電腦通訊速度
#define Brate ((Fosc/Speed)-1)

void Init_uart(void)
{
  word temp ;
  TX1STA=0b00100100;//啟動發送模組;
                  //8位元高速傳輸;
  RC1STA=0b10010000;//啟動接收模組
                  //8位元接收
  BAUD1CON=0x08; //16位元
 
temp.w = Brate ;
//  temp.w = 83;
  
  TX_init = 1;
  RX_init = 1;
  SP1BRGH = temp.b.msb ;
  SP1BRG  = temp.b.lsb;
//  SP1BRGH = Brate>>8;
//  SP1BRG  = Brate; 
}

void PutChar(unsigned char data)
{
 while (PIR1bits.TXIF== 0){}
 TXREG =data;  //傳輸暫存器(TXREG)
}

void Putdata (const  unsigned char *data)
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


void DumpintDec (unsigned int val) //十進制轉換 only 69999
{
 unsigned int v0=0,v1=0,v2=0,v3=0,v4=0; //v4=萬 v3=千 v2=百位 v1 =十位 v0=個位
 v4= val/10000;//65536/10000=6.5536
 val=(unsigned int) val-(10000*v4);
 v3= val/1000;//5536/1000=5.536
 val=(unsigned int)val-(1000*v3);
 v2=val/100;//536/100=5.36
 val=(unsigned int)val-(100*v2);
 v1= val/10;//36/10
 v0= val%10;

 if(v4>0){goto s4;}
 if(v3>0){goto s3;}
 if(v2>0){goto s2;}
 if(v1>0){goto s1;}
goto s0;
s4:PutChar(v4+'0');
s3:PutChar(v3+'0');
s2:PutChar(v2+'0');
s1:PutChar(v1+'0');
s0:PutChar(v0+'0');
}


//void UART1_HEX(U8 data)
//{
//     
//}


