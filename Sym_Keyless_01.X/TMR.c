/* 
 * File:   ioport_core.c
 * Author: Norton.Hsioa
 *
 * Created on October 8, 2023, 10:28 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "mcu.h"
#include "global.h"
#include "TMR.h"




void Init_TMR1(void);
void Set_TMR1(uint16_t value);

//
void Init_TMR(void)
{
    Init_TMR1();
}

void Init_TMR0(void)
{
//    OPTION_REGbits.PS   = Timer0PS;
//    OPTION_REGbits.PSA = ENABLE;
//    OPTION_REGbits.T0CS = 0;

}
//
void RestoreTMR0(uint8_t value)
{
    TMR0 = value;
 
}

void Init_TMR1(void)
{
    Set_TMR1Source(TMR1_Source_CoreOSC);
    Set_TMR1Externalcircuit(DISABLE);
    Set_TMR1ScaleOSC(TMR1Rate8);
    Set_TMR1SYNCFOSC(ENABLE);
    T1GCON =0;
}

void Set_TMR1(uint16_t value)
{
    union{
     struct {
                uint8_t LSB :8;//bit0-bit3
                uint8_t MSB :8;//bit4-bit7
        }byte;
        uint16_t All;
    }_TMR1Count;
    
    _TMR1Count.All = value;
    Set_TMR1ON(DISABLE);
    TMR1H = _TMR1Count.byte.MSB;
    TMR1L = _TMR1Count.byte.LSB;
}

void Run_TMR1(uint8_t value ,uint16_t count)
{
    Set_TMR1(count);
    Set_TMR1ON(value);
}




void Init_TMR2(void)
{
    T2CLKCONbits.CS = 0x01; //FSYS
    T2CONbits.ON =0;
    T2CONbits.CKPS = 0x07;//1:128
    T2CONbits.OUTPS =0x11;//1:10 
}

void SetTMR2(uint8_t value)
{
    
}

void Run_TMR2(uint8_t value ,uint8_t count)
{
    
}