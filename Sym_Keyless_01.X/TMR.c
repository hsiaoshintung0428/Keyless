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

//
void Init_TMR0(void)
{
    OPTION_REGbits.PS   = Timer0PS;
    OPTION_REGbits.PSA = ENABLE;
    OPTION_REGbits.T0CS = 0;
}
//
void RestoreTMR0(uint8_t value)
{
    TMR0 = value;
 
}

void Init_TMR2(void)
{
    
}

void SetTMR2(uint8_t value)
{
    
}