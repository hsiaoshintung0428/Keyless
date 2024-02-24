/* 
 * File:   main.c
 * Author: Norton.Hsioa
 *
 * Created on October 8, 2023, 10:28 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "config.h"
#include "global.h"
#include "options.h"
#include "delay.h"
#include "interrupt.h"
#include "ioports.h"
#include "TMR.h"
#include "pwm.h"
#include "adc.h"
#include "process.h"
#include "hef.h"

uint8_t _GPIOTimeCount=0;
uint8_t _GPIOState=0;
uint8_t _GPIOBlock = 0;

void Init_ExtOsc(void);
void Init_SPI(void);

/*
 * 
 */
int main(int argc, char** argv) 
{
    Init_ExtOsc();
    Init_ADC();
    Init_TMR();
    Init_GPIO();
    Remap_GPIO();
    Init_SPI();
    Init_PWM();
    FlashUnlock();
    Init_interrupt();
   
    if(PowerState == PS_G3)//when system resume from G3
    {
        
    }

    
    while(1)
    {
        if((mFLAG._bits._RFINT) || (mFLAG._bits._GPIO) )//中斷喚醒
        {
            switch(PowerState)
            {
                case 0: //解鎖
                    //按壓 POWER BUTTON 時間大於 0.3 秒時，控制器會執行身份辨識動作
                    //若小於 0.3 則等 0.72 秒後回休眠
                    //搜尋遙控器，在搜尋範圍內，進行遠程身份辨識
                    //若搜尋不到配對遙控器，控制器不做任何動作
                    //若連續 8 次按壓 POWER BUTTON 都搜尋不到遙控器，系統將進入 10 秒不動作，已進行省電10 秒後重新累計 8 次
                    //每次回到待機休眠模式，8 次計數將歸零
                    //10 秒內統計按 8 次，每次搜尋 16 次。省電 10 秒後重新累計。
                    if(mFLAG._bits._GPIO && (!_GPIOBlock) )//GPIO可用
                    {
                        if(_GPIOTimeCount >= (PWR_PressTime_Limit/PollingTime))//判斷時間是否大於300mS
                        {
                            if( ISPWRON() == DISABLE )//判斷GPIO狀態
                            {
                             _GPIOState = TRUE;
                            }
                            else//
                            {
                             _GPIOState = FALSE;   
                             _GPIOBlock = TRUE;
                            }
                        }                                                       
                    }
                    break;
                    
                case 1://上鎖
                    break;
                    
                case 2://學習
                    break;
                    
                case 3://關機
                    break;
            }
            
        }
    }

    return (EXIT_SUCCESS);
}

/*
 * Function: Initialization Extern Oscillator
 * Input:None
 * Output:None
 * Modify History:
 */

void Init_ExtOsc(void)
{
     // SCS FOSC; SPLLEN disabled; IRCF 8MHz_HF; 
    OSCCONbits.SPLLEN = ENABLE; 
    OSCCONbits.IRCF =   IntOSC_8MHz;
    // SOSCR enabled; 
    OSCSTAT = 0x80;
    // TUN 0; 
    OSCTUNE = 0x00;
    // SBOREN disabled; BORFS disabled; 
    BORCON = 0x00;
    // Wait for PLL to stabilize
#if (!DBG_Token)    
    while(PLLR == 0)
    {
    }    
#endif    
}

/*
 * Function: 
 * Input:None
 * Output:None
 * Modify History:
 */
void Init_SPI(void)
{
//    UnlockIO(); //Unlock PPS mode
//    SSPCLKPPS = ppsOutmap(_ppsPORTC_,_ppsPIN3_) ;     //Set SPI SSPCLKPSS to RC3[RF_CLK]
//    SSPDATPPS = ppsOutmap(_ppsPORTC_,_ppsPIN4_) ;     //Set SPI SSPDATPPS to RC4[RF_MISO]
//    RC5PPS = _pps_Out_SD0_ ;                          //Set RC5PPS to SPI_SDO   [RF_MOSI]
//    SSPSSPPS =  ppsOutmap(_ppsPORTD_,_ppsPIN3_) ;     //Set SPI SSPSSPPS  to RD3[RF_CS1]
//    LockIO();//Lock  PPS mode
    
    // this setting selects master mode with frequency fosc/4
    SSPCON1bits.SSPM0 = 0;
    SSPCON1bits.SSPM1 = 0;
    SSPCON1bits.SSPM2 = 0;
    SSPCON1bits.SSPM3 = 0;
    // Enable SPI Port
    SSPCON1bits.SSPEN = 1;
    // Configure The Clock Polarity & Phase
    SSPCON1bits.CKP = 0;
    SSPSTATbits.CKE = 0;
    //  Slew rate control enabled for High Speed mode
    SSPSTATbits.SMP = 0;
    // Set SPI pins as digital I/O
    TRISC5 = 0; // SDO -> Output
    TRISC4 = 1; // SDI -> Input
    TRISC3 = 0; // SCK -> Output
    //Uncommnent this line, if you want to send send over interrupt
    // SSPIE = 1; PEIE = 1; GIE = 1;
}






