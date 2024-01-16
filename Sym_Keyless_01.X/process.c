/* 
 * File:   process.c
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
#include "process.h"

uint8_t PowerState = 0xFF;

//龍頭解鎖
void Unlock_Handle(void)
{
    
}

//龍頭上鎖
void Lock_Handle(void)
{
    
}

//閃爍方向燈
void Blinking_TurnSignal(uint8_t control )
{
    
}