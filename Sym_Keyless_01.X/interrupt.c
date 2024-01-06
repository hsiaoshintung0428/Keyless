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


void Init_Interttup(void)
{
    
}


void _INTERRUPT ISR(void)
{
    if(Read_TMR0IF())
    {

    }
    
}
