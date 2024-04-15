/* 
 * File:   adc.h
 * Author: 
 *
 * Created on 
 */

#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

typedef enum{
    Channel_AN0 =0  ,
    Channel_AN1=1     ,
    Channel_AN2=2     ,  
    Channel_AN3=3     ,  
    Channel_AN4     ,
    Channel_AN5     ,  
    Channel_AN6     ,
    Channel_AN7     ,  
    Channel_AN8     ,
    Channel_AN9  =9   ,
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

    
#define ADC_PWR     Channel_AN9
#define ADC_Seat    Channel_AN8
#define ADC_OCP     Channel_AN14
#define ADC_Vin     Channel_AN24
#define ADC_IGN     Channel_AN26
    
extern void Init_ADC(void);
void Trigger_ADC(uint8_t channel);
uint16_t Internal_ADC_Conversion (uint8_t CH, uint8_t EN );

#endif	/* ADC_H */

