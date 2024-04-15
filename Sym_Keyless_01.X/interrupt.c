/* 
 * File:   interrupt.c
 * Author: 
 *
 * Created on 
 */
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "mcu.h"
#include "global.h"
#include "interrupt.h"
#include "ioports.h"
#include "TMR.h"
#include "uart.h"


extern void RestoreTMR0(uint8_t value , uint8_t EN);

uint8_t Right =0;
uint8_t Left =1;

/*
 * Function: 
 * Input:None
 * Output:None
 * Modify History:
 */
void Init_interrupt(void)
{
    INTCON = 0;
    PIR1 = PIR2 =PIR3 =PIR4 =PIR5 =PIR6 =0;
    Set_Globa_Interrupt(ENABLE);
    Set_Extern_Interrupt(ENABLE);
    
    Set_INTIE(ENABLE);
//    Set_TMR1IE(ENABLE);
    Set_IOCIE(ENABLE);
    IOCBPbits.IOCBP3 = 1;
    //IOCBNbits.IOCBN3 = 1;
    
    
    
    CLS_INTIF();
    CLS_TMR1IF();
    CLS_IOCIF();
    
    Run_TMR1(FillTMR1,ENABLE);
}

/*
 * Function: 
 * Input:None
 * Output:None
 * Modify History:
 */

 uint8_t Trigger = 0;
void _INTERRUPT ISR(void)
{
    //Putdata("\nisr =  ");
    if(Read_TMR0IF()) 
    {
      CLS_TMR0IF();  
      RestoreTMR0(FillTMR0, ENABLE);
      _GPIOTimeCount++;
      
    }
    
    if(Read_TMR1IF())
    { 
        mFLAG._bits._TMR1 = ENABLE;
        CLS_TMR1IF();      
    }
    //Iinterrupt from SPI int(RB3)
    if(Read_IOCIF() && IOCBFbits.IOCBF3)
    { 
        if(PORTBbits.RB3)
            Putdata("IOCIF_H \n ");
        else
            Putdata("IOCIF_L \n ");
        IOCBFbits.IOCBF3  = 0;
        mFLAG._bits._GPIO = ENABLE;
        //Set_IOCIE(DISABLE);
        if(mGPIOState._bits.Wait)
        {
            
        }
        _GPIOTMR0CLR  = ENABLE; 
        CLS_IOCIF();
        
    }
    //Iinterrupt from SPI int(RD5)
    if( INTCONbits.INTF )
    {
        //Putdata("INTF\n ");
        mFLAG._bits._RFINT = ENABLE;
         INTCONbits.INTF = 0;
        CLS_INTIF();
    }
    
}
