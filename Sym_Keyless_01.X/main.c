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
#include "interrupt.h"
#include "ioports.h"
#include "TMR.h"
#include "pwm.h"
#include "adc.h"
#include "process.h"
#include "hef.h"






void Init_ExtOsc(void);
void Init_SPI(void);

/*
 * 
 */
int main(int argc, char** argv) {
    
    uint8_t Duty_temp = 0;
    
    Init_ExtOsc();
    Init_ADC();
    Init_TMR();
    Init_GPIO();
    Remap_GPIO();
    Init_SPI();
    Init_PWM();
    
    FlashUnlock();
    
    LATC |= 0x81;//L_Lamp & R_Lamp
    TRISC |=0x7E; 

    Init_interrupt();
    mFLAG.all = 0;
    mFLAG._bits._TMR1 = 0;
    
    
    LATAbits.LATA3 =1 ;
    TRISAbits.TRISA3 = 0;
   // Set_PWM(4,50);
    

    if(PowerState == PS_G3)//when system resume from G3
    {
        
    }

    
    while(1)
    {
        Set_PWM_Duty(PWM_Channel_4,Duty_temp);
        Duty_temp++;
        if( mFLAG._bits._GPIO )
        {
            
        }
//        if(Duty_temp > 100)
//            Duty_temp = 0;
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
    while(PLLR == 0)
    {
    }    
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






