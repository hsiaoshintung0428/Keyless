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
#include "interrupt.h"



void Init_TMR0(void);
void Init_TMR1(void);
void Set_TMR1(uint16_t value);


//
void Init_TMR(void)
{
    //Init_TMR0();
    Init_TMR1();
    Init_TMR2();
}

void Init_TMR0(void)
{
    OPTION_REGbits.PS   = Timer0PS;
    OPTION_REGbits.PSA = 0;
    OPTION_REGbits.T0CS = 0;
}

void RestoreTMR0(uint8_t value , uint8_t EN)
{
    Init_TMR0();
    Set_TMR0IE(DISABLE);//停用TMR0 中斷
    CLS_TMR0IF();//清除TMR0中斷旗標
    TMR0 = value; //設定TMR0 計數
    Set_TMR0IE(EN);//啟用TMR0 中斷
}

void Init_TMR1(void)
{
    Set_TMR1Source(TMR1_Source_InterLF);
    Set_TMR1Externalcircuit(DISABLE);
    Set_TMR1ScaleOSC(TMR1Rate1);
    Set_TMR1SYNCFOSC(DISABLE);
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

void Run_TMR1(uint16_t count,uint8_t EN)
{
    Set_TMR1(count);
    Set_TMR1ON(EN);
}




void Init_TMR2(void)
{
//    T2CLKCONbits.CS = 0x01; //FSYS
    
    T2CLKCON = 0x01;
    T2HLT = 0x80;
    T2RST = 0;
    PIR1bits.TMR2IF = 0;
    T2PR = 0xfa;
    T2TMR = 0x00;
    //T2CON = 0x80;
    
    T2CONbits.CKPS = 0x07;//1:128
    T2CONbits.OUTPS =0x00;//1:1     
    T2CONbits.ON =1;

    
}

void SetTMR2(uint8_t value)
{
    T2PR=value;
    TMR2 =0;
    
}

void Run_TMR2(uint8_t count,uint8_t EN)
{
    SetTMR2(count);
    T2CONbits.ON = EN;
}