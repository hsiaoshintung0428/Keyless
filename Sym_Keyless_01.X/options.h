/* 
 * File:   options.h
 * Author: Varcolac_MV_SKU36
 *
 * Created on 2023年10月24日, 下午 10:46
 */

#ifndef OPTIONS_H
#define	OPTIONS_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	__cplusplus
}
#endif

//--stand by 
#define PWR_PressTime_Limit     300     //Press power button time more than 300ms to recognized 
#define PWR_Failure_WaitTime    720     //Press power button small than PWR_PressTime_Limit wait 720 ms into Sleep mode 
#define PWR_MaxFailure_Count    8       //Press power button more than 8 times suspend search key...
#define PWR_SusoendTime         Second2minscond(10)     //Suspend search key 10 seconds 
#define Key_Search_Count        16      //Press PWR once search key 16 times
#define Key_Moto_activetime     40      //If ID match unlock moto time
#define LED_BlinkTime           500     //Direction LED blink time 
#define LED_BreathingTime       Second2minscond(1) //Breathing time 1 second

//--wake up 
#define ResponseTimeOut        Second2minscond(10) //
#define LED_SleepTime          Second2minscond(1)  

//--search mode
#define Search_HornTime        500

//Seat mode (reserver)

//Learn mode 
#define Learn_PWRTime   Second2minscond(3) //
#define Learn_WaitBlinkTime 300
#define Learn_BlinkTime     100


//debug mode 
#define DBG_Token      1


#endif	/* OPTIONS_H */

