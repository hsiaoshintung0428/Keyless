/* 
 * File:   interrupt.c
 * Author: Varcolac_MV_SKU36
 *
 * Created on 2023年12月6日, 下午 10:25
 */
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "mcu.h"
#include "global.h"
#include "interrupt.h"
#include "TMR.h"
#include "ioports.h"

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
    Set_Globa_Interrupt(ENABLE);
    Set_Extern_Interrupt(ENABLE);
    
    Set_INTIE(ENABLE);
    Set_TMR1IE(ENABLE);
    Set_IOCIE(ENABLE);
    
    CLS_INTIF();
    CLS_TMR1IF();
    CLS_IOCIF();
    
    Run_TMR1(ENABLE , FillTMR1);
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
    if(Read_TMR1IF())
    { 
        mFLAG._bits._TMR1 = ENABLE;
        CLS_TMR1IF();      
    }
    //Iinterrupt from SPI int(RB3)
    if(Read_IOCIF())
    {
        //check power state... 
        //first check power state
        //if sleep state wake up MCU do something...
        //if in on state do not thing??
        mFLAG._bits._GPIO = ENABLE;//Set interrupt GPIO flag
        CLS_IOCIF();
        
    }
    //Iinterrupt from SPI int(RD5)
    if(Read_INTIF())
    {
        mFLAG._bits._RFINT = ENABLE;
        CLS_INTIF();
    }
    
}
