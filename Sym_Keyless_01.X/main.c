/* 
 * File:   main.c
 * Author: Norton.Hsioa
 *
 * Created on October 8, 2023, 10:28 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "global.h"
#include "ioports.h"
#include "TMR.h"




void Init_ExtOsc(void);
void Init_SPI(void);

/*
 * 
 */
int main(int argc, char** argv) {
    
    Init_ExtOsc();
    Init_TMR0();
    Init_GPIO();
    Init_SPI();
    TRISA   = 0x00;

    while(1)
    {
        
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
    OSCCONbits.SPLLEN = ENABLE; 
    OSCCONbits.IRCF =   ExtOSC_8MHz;
    OSCCONbits.SCS   = 0;        
}

void Init_SPI(void)
{
    UnlockIO(); //Unlock PPS mode
    SSPCLKPPS = ppsOutmap(_ppsPORTC_,_ppsPIN3_) ;     //Set SPI SSPCLKPSS to RC3[RF_CLK]
    SSPDATPPS = ppsOutmap(_ppsPORTC_,_ppsPIN4_) ;     //Set SPI SSPDATPPS to RC4[RF_MISO]
    RC5PPS = _pps_Out_SD0_ ;                          //Set RC5PPS to SPI_SDO   [RF_MOSI]
    SSPSSPPS =  ppsOutmap(_ppsPORTD_,_ppsPIN3_) ;     //Set SPI SSPSSPPS  to RD3[RF_CS1]
    LockIO();//Lock  PPS mode
    
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
