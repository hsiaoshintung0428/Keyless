#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "global.h"
#include "ioports.h"
#include "TMR.h"

#define _Internal_ADC_ON(n)         (ADCON0bits.ADON = n )
#define _Internal_ADC_GO(n)         (ADCON0bits.GO  = n)
#define _Internal_ADC_DONE()        (ADCON0bits.GO )
#define _INternal_ADC_Channel(n)    (ADCON0bits.CHS = n)   
typedef enum{
    Channel_AN0 =0  ,
    Channel_AN1     ,
    Channel_AN2     ,  
    Channel_AN3     ,  
    Channel_AN4     ,
    Channel_AN5     ,  
    Channel_AN6     ,
    Channel_AN7     ,  
    Channel_AN8     ,
    Channel_AN9     ,
    Channel_AN10     ,  
    Channel_AN11     ,  
    Channel_AN12     ,
    Channel_AN13     ,  
    Channel_AN14     ,
    Channel_AN15     ,  
    Channel_AN16     ,
    Channel_AN17     ,
    Channel_AN18     ,  
    Channel_AN19     ,  
    Channel_AN20     ,
    Channel_AN21     ,  
    Channel_AN22     ,
    Channel_AN23     ,  
    Channel_AN24     , 
    Channel_AN25     ,
    Channel_AN26     ,  
    Channel_AN27     ,              
    }PIC_ADC_Channel;

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
    
    
    
void Init_ADC(void)
{
    ADC_Right_justified();
    ADC_CLOCK_FOSC16();
    ADC_nREF_VSS();
    ADC_pREF_VDD();
    ADCON2  = 0; //Disable Auto trigger 
    
}


void Trigger_ADC(uint8_t channel)
{
    _Internal_ADC_ON(ENABLE);
    
}

uint16_t Get_ADC_Result(void)
{
    uint16_t ADC_Temp;
    
    _Internal_ADC_GO(0);
    ADC_Temp = ADRESH;
    ADC_Temp = (ADC_Temp <<8 )+ ADRESL;
    
    return ADC_Temp;
            
}