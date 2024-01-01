/* 
 * File:   ioport_core.c
 * Author: Norton.Hsioa
 *
 * Created on October 8, 2023, 10:28 PM
 */

//*****************************//
// PIC16F1779 GPIO initially
//*****************************//
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "mcu.h"
#include "global.h"
#include "ioports.h"

// GPIO Control Register Fields
void Init_GPIO(void)
{
    #if (__MCU__    ==  _PIC16F1779_)
    /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
        TRISA   =   def_PORTA_DIR;          //GPIO direction  
        ANSELA  =   def_PORTA_ANALOG;       //GPIO  analog input 
        WPUA    =   def_PORTA_PULLUP;       //GPIO internal Pullup regsister 
        ODCONA  =   def_PORTA_OPENDRAIN;    //GPIO output type 
        SLRCONA =   def_PORTA_PWMSlewRate;  //GPIO pwm slew rate 
        INLVLA  =   def_PORTA_InputLevel;   //GPIO input volterge level
        #if 0
        HIDRVA  =   def_PORTA_Current;      //16f1779 no use
        #endif
        IOCAP   =   def_PORTA_Int_PEDGE;    //interrupt wareform rising edge 
        IOCAN   =   def_PORTA_Int_NEDGE;    //interrupt wareform falling edge 
        IOCAF   =   def_PORTA_Int_FLAG;     //interrupt flag must clear by software.
     /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/   
        TRISB   =   def_PORTB_DIR;          //GPIO direction  
        ANSELB  =   def_PORTB_ANALOG;       //GPIO  analog input 
        WPUB    =   def_PORTB_PULLUP;       //GPIO internal Pullup regsister 
        ODCONB  =   def_PORTB_OPENDRAIN;    //GPIO output type 
        SLRCONB =   def_PORTB_PWMSlewRate;  //GPIO pwm slew rate 
        INLVLB  =   def_PORTB_InputLevel;   //GPIO input volterge level
        #if 1
        HIDRVB  =   def_PORTA_Current;      //16f1779 no use
        #endif
        IOCBP   =   def_PORTB_Int_PEDGE;    //interrupt wareform rising edge 
        IOCBN   =   def_PORTB_Int_NEDGE;    //interrupt wareform falling edge 
        IOCBF   =   def_PORTB_Int_FLAG;     //interrupt flag must clear by software. 
    /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
        TRISC   =   def_PORTC_DIR;          //GPIO direction  
        ANSELC  =   def_PORTC_ANALOG;       //GPIO  analog input 
        WPUC    =   def_PORTC_PULLUP;       //GPIO internal Pullup regsister 
        ODCONC  =   def_PORTC_OPENDRAIN;    //GPIO output type 
        SLRCONC =   def_PORTC_PWMSlewRate;  //GPIO pwm slew rate 
        INLVLC  =   def_PORTC_InputLevel;   //GPIO input volterge level
        #if 0
        HIDRVC  =   def_PORTC_Current;      //16f1779 no use
        #endif
        IOCCP   =   def_PORTC_Int_PEDGE;    //interrupt wareform rising edge 
        IOCCN   =   def_PORTC_Int_NEDGE;    //interrupt wareform falling edge 
        IOCCF   =   def_PORTC_Int_FLAG;     //interrupt flag must clear by software. 
    /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
        TRISD   =   def_PORTD_DIR;          //GPIO direction  
        ANSELD  =   def_PORTD_ANALOG;       //GPIO  analog input 
        WPUD    =   def_PORTD_PULLUP;       //GPIO internal Pullup regsister 
        ODCOND  =   def_PORTD_OPENDRAIN;    //GPIO output type 
        SLRCOND =   def_PORTD_PWMSlewRate;  //GPIO pwm slew rate 
        INLVLD  =   def_PORTD_InputLevel;   //GPIO input volterge level
        #if 0
        HIDRVD  =   def_PORTD_Current;      //16f1779 no use
        #endif
        #if 0
        IOCDP   =   def_PORTD_Int_PEDGE;    //interrupt wareform rising edge 
        IOCDN   =   def_PORTD_Int_NEDGE;    //interrupt wareform falling edge 
        IOCDF   =   def_PORTD_Int_FLAG;     //interrupt flag must clear by software. 
        #endif
    /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
        TRISE   =   def_PORTE_DIR;          //GPIO direction  
        ANSELE  =   def_PORTE_ANALOG;       //GPIO  analog input 
        WPUE    =   def_PORTE_PULLUP;       //GPIO internal Pullup regsister 
        ODCONE  =   def_PORTE_OPENDRAIN;    //GPIO output type 
        SLRCONE =   def_PORTE_PWMSlewRate;  //GPIO pwm slew rate 
        INLVLE  =   def_PORTE_InputLevel;   //GPIO input volterge level
        #if 0
        HIDRVE  =   def_PORTE_Current;      //16f1779 no use
        #endif
        IOCEP   =   def_PORTE_Int_PEDGE;    //interrupt wareform rising edge 
        IOCEN   =   def_PORTE_Int_NEDGE;    //interrupt wareform falling edge 
        IOCEF   =   def_PORTE_Int_FLAG;     //interrupt flag must clear by software. 
    /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    #endif
}
