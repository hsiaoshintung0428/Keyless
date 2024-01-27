/* 
 * File:   pwm.h
 * Author: mWS_G9_SKU43
 *
 * Created on January 17, 2024, 1:26 PM
 */

#ifndef PWM_H
#define	PWM_H

#ifdef	__cplusplus
extern "C" {
#endif
    
typedef enum{
    PWM_Channel_3 = 0,
    PWM_Channel_4 = 1,
    PWM_Channel_5 = 2,
    PWM_Channel_6 = 3,        
    PWM_Channel_9 = 4,
    PWM_Channel_10 = 5,
    PWM_Channel_11 = 6,
    PWM_Channel_12 = 7,
}_PWMChannel;


extern void Init_PWM(void);
extern void Set_PWM_Duty(uint8_t channel, uint32_t duty);

#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */

