/* 
 * File:   pwm.c
 * Author: 
 *
 * Created on 
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "global.h"
#include "mcu.h"
#include "ioports.h"
#include "TMR.h"
#include "pwm.h"


#define SetPWM4(n)  PWM4CONbits.EN = n
#define SetPWM9(n)  PWM9CONbits.EN = n

typedef enum{
    PWMSourceTMR2 = 0,
    PWMSourceTMR4 = 1,
    PWMSourceTMR6 = 2,
    PWMSourceTMR8 = 3,
}_PWMClockSource;



void Init_PWM4(void);
void Init_PWM9(void);
void Set_PWM_Duty(uint8_t channel, uint32_t duty);

void Init_PWM(void)
{
    //Set PWM clock source 
        //CCPTMRS1 = 0x00;
        CCPTMRS2bits.P4TSEL = PWMSourceTMR2; //TMR2
        CCPTMRS2bits.P9TSEL = PWMSourceTMR6; //TMR6
    //Plz follow below step to setting 10 bits PWM module.. 
    //10bits PWM module
    //Remap  PWM4 to RD2(Handle blue led)
    //Disable TRISD bit2 
    //Write TMR2 register to set freq..
    //Write PR2 register to set duty cycle..
    //Enable TMR2 & PWM  module 
    Init_PWM4();
    Init_PWM9();
    
}

void Init_PWM4(void)
{
    //TMR2
    //500 Hz??
    TRISDbits.TRISD2 = 0;
    PWM4CON = 0x80;
    Set_PWM_Duty(PWM_Channel_4,75);
    T2RST = 0x00;
    PWM4CONbits.EN = 1;
    
}


void Init_PWM9(void)
{
    //TMR6
    //125KHz
    TRISBbits.TRISB1 = 0;
    PWM9CON = 0x80;
    Set_PWM_Duty(PWM_Channel_9,50);
    T6PR = 0x10;
    T6RST = 0x00;
    PWM9CONbits.EN = 1;
    T6CON = 0x80;
}


void Set_PWM_Duty(uint8_t channel, uint32_t duty)
{
    union{
     struct {
                uint8_t LSB :8;//bit0-bit3
                uint8_t MSB :8;//bit4-bit7
        }byte;
        uint16_t All;
    }_DutyCount;
    
    
    if(duty >100)
    {
        duty =100 ;
    }
    if((channel == PWM_Channel_3) || (channel ==PWM_Channel_4) ||\
       (channel ==PWM_Channel_9) || (channel ==PWM_Channel_10))
    {
        duty= (1023*duty)/100;
        _DutyCount.byte.MSB = (uint8_t) ((duty & 0x03FCu) >> 2);
        _DutyCount.byte.LSB = (uint8_t) ((duty & 0x0003u) << 6); 
    }
    
    switch(channel)
    {
         //======10 bit PWM======//   
        case PWM_Channel_3:
            PWM3DCH =_DutyCount.byte.MSB;
            PWM3DCLbits.DC = _DutyCount.byte.LSB;
            break;
        case PWM_Channel_4:
            PWM4DCH =_DutyCount.byte.MSB;
            PWM4DCLbits.DC = _DutyCount.byte.LSB;            
            break;
        case PWM_Channel_9:
            PWM9DCH =_DutyCount.byte.MSB;
            PWM9DCLbits.DC = _DutyCount.byte.LSB;            
             break;
        case PWM_Channel_10:
            PWM10DCH =_DutyCount.byte.MSB;
            PWM10DCLbits.DC = _DutyCount.byte.LSB;            
             break;  
        //======16 bit PWM======//       
        case PWM_Channel_5:
             break;          
        case PWM_Channel_6:
             break;    
        case PWM_Channel_11:
             break;    
        case PWM_Channel_12:
             break;                 
    }//switch
    
//     //======10 bit PWM======//   
//    if(channel == 3)
//    {
//     PWM3DCH =_DutyCount.byte.MSB;
//     PWM3DCLbits.DC = _DutyCount.byte.LSB;      
//    }
//    
//    if(channel == 4)
//    {
//     PWM4DCH =_DutyCount.byte.MSB;
//     PWM4DCLbits.DC = _DutyCount.byte.LSB;      
//    }
//    
//    if(channel == 9)
//    {
//     PWM9DCH =_DutyCount.byte.MSB;
//     PWM9DCLbits.DC = _DutyCount.byte.LSB;      
//    }
//    
//    if(channel == 10)
//    {
//     PWM10DCH =_DutyCount.byte.MSB;
//     PWM10DCLbits.DC = _DutyCount.byte.LSB;      
//    }
     //======16 bit PWM======//  
//    if(channel == 5)
//    {
//     PWM5DCH =_DutyCount.byte.MSB;
//     PWM5DCLbits.DC = _DutyCount.byte.LSB;      
//    }
//    if(channel == 6)
//    {
//     PWM6DCH =_DutyCount.byte.MSB;
//     PWM6DCLbits.DC = _DutyCount.byte.LSB;      
//    }
//    if(channel == 11)
//    {
//     PWM11DCH =_DutyCount.byte.MSB;
//     PWM11DCLbits.DC = _DutyCount.byte.LSB;      
//    }
//    if(channel == 12)
//    {
//     PWM12DCH =_DutyCount.byte.MSB;
//     PWM12DCLbits.DC = _DutyCount.byte.LSB;      
//    }

    
}


