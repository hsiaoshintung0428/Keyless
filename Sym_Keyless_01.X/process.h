/* 
 * File:   process.h
 * Author: Varcolac_MV_SKU36
 *
 * Created on 2024年1月6日, 下午 8:27
 */

#ifndef PROCESS_H
#define	PROCESS_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

typedef enum{
    PS_ON       = 0,
    PS_Idle     = 1,
    PS_Sleep    = 2,
    PS_Off      = 3,   
    PS_G3       = 0xFF //global reset        
}_MCUPowerState;

extern uint8_t PowerState;

#endif	/* PROCESS_H */

