#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "global.h"
#include "ioports.h"
#include "delay.h"
#include "TMR.h"
#include "adc.h"


#define _Internal_ADC_ON(n)         (ADCON0bits.ADON = n )
#define _Internal_ADC_GO(n)         (ADCON0bits.GO  = n)
#define _Internal_ADC_DONE()        (!ADCON0bits.GO )
#define _INternal_ADC_Channel(n)    (ADCON0bits.CHS = n)   



#define ADC_Right_justified()   ADCON1bits.ADFM=1   //ADC result formal right
#define ADC_Left_justified()    ADCON1bits.ADFM=0
#define ADC_CLOCK_FOSC2()       ADCON1bits.ADCS=0
#define ADC_CLOCK_FOSC4()       ADCON1bits.ADCS=4
#define ADC_CLOCK_FOSC8()       ADCON1bits.ADCS=1
#define ADC_CLOCK_FOSC32()      ADCON1bits.ADCS=2
#define ADC_CLOCK_FRC()         ADCON1bits.ADCS=3
#define ADC_CLOCK_FOSC16()      ADCON1bits.ADCS=5
#define ADC_CLOCK_FOSC64()      ADCON1bits.ADCS=6
#define ADC_nREF_VSS()          ADCON1bits.ADNREF=0
#define ADC_nREF_ExREF()        ADCON1bits.ADNREF=1
#define ADC_pREF_VDD()          ADCON1bits.ADPREF=0
#define ADC_pREF_ExREF()        ADCON1bits.ADPREF=2
#define ADC_pREF_InREF()        ADCON1bits.ADPREF=3   
    
    
 void Trigger_ADC(uint8_t channel);
 uint16_t Get_ADC_Result(void);
    
void Init_ADC(void)
{
    ADCON1 = 0b11110000;
    ADCON2 = 0;
    ANSELC = 0;
    ANSELA = 0;
    ANSELB = 0;
    ANSELC = 0;
    ANSELD = 0;
//    TRISBbits.TRISB3 = 1;
//    ANSELBbits.ANSB3 = 1;

   _Internal_ADC_ON(ENABLE);//Enable ADC module ~~ 
}


void Trigger_ADC(uint8_t channel)
{
    if(channel == ADC_PWR )
        ANSELBbits.ANSB3 = 1;
    
    ADCON0bits.CHS = channel ;
    _delay1uS(250);
    _Internal_ADC_GO(1);
    
}

uint16_t Get_ADC_Result(void)
{
  
     union{
     struct {
                uint8_t LSB :8;//bit0-bit7
                uint8_t MSB :8;//bit8-bit15
        }byte;
        uint16_t All;
    }_ADCResult;
    
    _ADCResult.All = 0 ;
  
    while(_Internal_ADC_DONE());//wait ADC converter done...
    
   _ADCResult.byte.MSB = ADRESH ;
   _ADCResult.byte.LSB = ADRESL ;
   // _Internal_ADC_ON(!ENABLE);

   return _ADCResult.All;
            
}

uint16_t Internal_ADC_Conversion (uint8_t CH, uint8_t EN )
{
    uint16_t date =0;
    
    if(EN == ENABLE)
    {
        Trigger_ADC(CH);
        date =  Get_ADC_Result();
    }
    else
        date = -1 ;
    
    if(CH == ADC_PWR )
        ANSELBbits.ANSB3 = 0; 
    
    return date;
}
  