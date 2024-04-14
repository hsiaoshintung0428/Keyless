/* 
 * File:   main.c
 * Author: Norton.Hsioa
 *
 * Created on October 8, 2023, 10:28 PM
 * 20240414
 *完成模組 ADC 可動作, RB3可用中斷處理
 *  代辦事項 
 *  檢查解上鎖功能
 * 
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
#include "uart.h"
#include "hef.h"
#include "spi.h"
#include "ata5781.h"


void Init_ExtOsc(void);
//void Init_SPI(void);


/*
 * 
 */
uint8_t count=0;
int main(int argc, char** argv) 
{
    uint16_t aa;
    Init_ExtOsc();
    Init_GPIO();
    Init_ADC();
    Init_TMR();
  
    Remap_GPIO();
    Init_SPI();
    Init_PWM();
    FlashUnlock();
    Init_interrupt();
    Init_ATA5781();
    Init_uart();
    FlashUnlock();
    //FlashWriteByte(HEFSPACE,0xAA);
    //FlashWriteByte(HEFSPACE+1,0xAB);
   
    if(PowerState == PS_G3)//when system resume from G3
    {
        
    }

    
    while(1)
    {

        if(INTCONbits.INTF)
        {
           INTCONbits.INTF = 0;
        }
        
        //aa = rf_ata5781_read_version();
        //DumpintDec(aa);
        
        if((mFLAG._bits._RFINT) || (mFLAG._bits._GPIO) )//中斷喚醒
        {
            if(mFLAG._bits._GPIO)
            {
              // aa= Internal_ADC_Conversion(ADC_PWR ,ENABLE); //抓ADC值
              // DumpintDec(aa);
                Unlock_Handle();
               mFLAG._bits._GPIO = 0;
            }
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
                    if(_GPIOTMR0CLR)//啟用TMR0計數
                    {
                        Putdata("main loop_1\n");
                      _GPIOTMR0CLR = DISABLE ;//清除TMR0 啟用旗標
                       RestoreTMR0(FillTMR0,ENABLE);//5mS,啟用TMR0中斷
                    }
                    
                    if(mFLAG._bits._GPIO 
                       && (!_GPIOBlock)
                       && (ISPWRON() == HiVoltage))//GPIO中斷啟用 && GPIO block 未被啟用 && 釋放按鍵 
                    {
                        Putdata("main loop_2\n");
                        if((_GPIOTimeCount <= (PWR_PressTime_Limit/TMR0PollingTime)))//小於300 ms
                        {
                                mGPIOState._bits.Wait = ENABLE; //啟用720ms等待
                                _GPIOTimeCount = 0;
                                RestoreTMR0(FillTMR0,ENABLE);//5mS,啟用TMR0中斷
                                //計算錯誤次數
                        }
                        else if(_GPIOTimeCount >= (PWR_PressTime_Limit/TMR0PollingTime))//大於300 ms
                        {   
                             RestoreTMR0(FillTMR0,DISABLE);//5mS,停用TMR0中斷//停用TMR0 中斷
                             //檢查keyless 
                             mGPIOState._bits.Wait = DISABLE;
                             mGPIOState._bits.UnLock = ENABLE;//啟動解鎖
                             mFLAG._bits._GPIO  = DISABLE ;//清除GPIO判斷旗標
                            _GPIOTimeCount =0;
                        }                            
                    }
                    if(mGPIOState._bits.UnLock) //啟用解鎖
                    {
                        Putdata("main loop_3\n");
                        Unlock_Handle();
                        mGPIOState._bits.UnLock = DISABLE; 
                    }
                    
                    else 
                    {
                        if( (mGPIOState._bits.Wait) 
                        &&(_GPIOTimeCount >= (PWR_Failure_WaitTime/TMR0PollingTime)))//啟動720mS未等待    

                      {
                          Putdata("main loop_4\n");
                          mGPIOState._bits.Wait = 0;
                          PowerState = 3;//關機程序
                      }
                        
                    }
                    
                    break;//end case 0
                //    
                case 1://上鎖
                    break;//end case 1
                    
                case 2://學習
                    break;//end case 2
                    
                case 3://關機
                    break;//end case 3
            }//end switch(PowerState)
            
        }//end中斷喚醒
        
        
        _delay1mS(250);
    }//end while(1)

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
  
    while(PLLR == 0)
    {
    }    
  
}








