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
#include "delay.h"
#include "process.h"

uint8_t PowerState = 0xFF;
uint16_t  Timestamp =0;



//DRV8872
void DRV8872_WakeUp(void);
void DRV8872_Sleep(void);
void DRV8872_Reverse(void);
void DRV8872_Forward(void);
void DRV8872_Coast(void);
void DRV8872_Brake(void);


//龍頭解鎖
void Unlock_Handle(void)
{   
    stuTHCML *th;
    th->date.dt.day =1;
    
    DRV8872_WakeUp();
    _delay1uS(50);
    DRV8872_Forward();
    _delay1mS(40);
}

//龍頭上鎖
void Lock_Handle(void)
{
    DRV8872_WakeUp();
    _delay1uS(50);
    DRV8872_Reverse();
     _delay1mS(40);
    DRV8872_Sleep();
}


void Set_TurnSignal(uint8_t Dir, uint8_t control )
{
    switch (Dir)
    {
        case DirectionRight:
            SetLAMP_Right(control);
            break;
            
        case DirectionLeft:
            SetLAMP_Left(control);
            break;
            
        case DirectionAll:
            SetLAMP_Right(control);
            SetLAMP_Left(control);
            break;
    }
}

void DRV8872_WakeUp(void)
{
    //wark up DRV8872 first 
    //Set PWM_IN1& 2 to still high level more than 5 us
    //device is operational 50 µs (tON) later 
    //[7.3.2 Sleep mode]  
    SetMOTOPWM1(ENABLE);
    SetMOTOPWM1(ENABLE);
    _delay1uS(5);
    
    
}

void DRV8872_Sleep(void)
{
    //wark up DRV8872 first 
    //Set PWM_IN1& 2 to still low level more than 1 ms
    //[7.3.2 Sleep mode]  
    SetMOTOPWM1(DISABLE);
    SetMOTOPWM1(DISABLE);
    _delay1mS(1);
}

void DRV8872_Reverse(void)
{
    //Please refer DRV8872 Spec Table1
    //  IN1   IN2  OUT1    OUT2     State
    //   0     0   HighZ   HighZ    Coast(滑行)
    //   0     1    L       H       Reverse(反轉)
    //   1     0    H       L       Forward(正轉)
    //   1     1    L       L       Brake(暫停)
    
    
    SetMOTOPWM1(DISABLE);
    SetMOTOPWM1(ENABLE);
}

void DRV8872_Forward(void)
{
    //Please refer DRV8872 Spec Table1
    //  IN1   IN2  OUT1    OUT2     State
    //   0     0   HighZ   HighZ    Coast(滑行)
    //   0     1    L       H       Reverse(反轉)
    //   1     0    H       L       Forward(正轉)
    //   1     1    L       L       Brake(暫停)
    
    SetMOTOPWM1(ENABLE);
    SetMOTOPWM1(DISABLE);
}

void DRV8872_Coast(void)
{
       //Please refer DRV8872 Spec Table1
    //  IN1   IN2  OUT1    OUT2     State
    //   0     0   HighZ   HighZ    Coast(滑行)
    //   0     1    L       H       Reverse(反轉)
    //   1     0    H       L       Forward(正轉)
    //   1     1    L       L       Brake(暫停)
    
    SetMOTOPWM1(ENABLE);
    SetMOTOPWM1(ENABLE); 
}


void DRV8872_Brake(void)
{
       //Please refer DRV8872 Spec Table1
    //  IN1   IN2  OUT1    OUT2     State
    //   0     0   HighZ   HighZ    Coast(滑行)
    //   0     1    L       H       Reverse(反轉)
    //   1     0    H       L       Forward(正轉)
    //   1     1    L       L       Brake(暫停)
    
    SetMOTOPWM1(DISABLE);
    SetMOTOPWM1(DISABLE); 
}
