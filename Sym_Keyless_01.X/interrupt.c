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

void Init_Interttup(void)
{
    Set_Globa_Interrupt(ENABLE);
    Set_Extern_Interrupt(ENABLE);
    Set_TMR1IE(ENABLE);
    CLS_TMR1IF();
}


void _INTERRUPT ISR(void)
{
    if(Read_TMR1IF())
    {
        CLS_TMR1IF();
        Run_TMR1(ENABLE , FillTMR1);
    }
    
    if(Read_IOCIF())
    {
        //check power state... 
        //first check power state
        //if sleep state wake up MCU do something...
        //if in on state do not thing??
        
    }
    
}
