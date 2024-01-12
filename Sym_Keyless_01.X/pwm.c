/* 
 * File:   pwm.c
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



void Init_PWM(void)
{
    //Plz follow below step to setting 10 bits PWM module.. 
    //10bits PWM module
    //Remap  PWM4 to RD2(Handle blue led)
    //Disable TRISD bit2 
    //Write TMR2 register to set freq..
    //Write PR2 register to set duty cycle..
    //Enable TMR2 & PWM  module 
    
    
}