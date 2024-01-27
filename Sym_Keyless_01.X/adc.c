#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "global.h"
#include "ioports.h"
#include "TMR.h"

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
    ANSELC = 0;
    ADC_Right_justified();
    ADC_CLOCK_FOSC16();
    ADC_nREF_VSS();
    ADC_pREF_VDD();
    ADCON2  = 0; //Disable Auto trigger 
    _Internal_ADC_ON(ENABLE);//Enable ADC module ~~ 
}


void Trigger_ADC(uint8_t channel)
{
    ADCON0 = channel ;
    _Internal_ADC_ON(ENABLE);
    
}

uint16_t Get_ADC_Result(void)
{
     union{
     struct {
                uint8_t LSB :8;//bit0-bit3
                uint8_t MSB :8;//bit4-bit7
        }byte;
        uint16_t All;
    }_ADCResult;
    
      while(_Internal_ADC_DONE());//wait ADC converter done...
      
    _Internal_ADC_GO(0);
    _ADCResult.byte.MSB = ADRESH ;
    _ADCResult.byte.LSB = ADRESL ;

    return _ADCResult.All;
            
}

uint16_t Internal_ADC_Conversion (uint8_t channel, uint8_t Active )
{
    uint16_t date =0;
    
    if(Active == ENABLE)
    {
        Trigger_ADC(channel);
        date    =   Get_ADC_Result();
    }
            
    return date;
}
  