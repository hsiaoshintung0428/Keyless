/* 
 * File:   process.h
 * Author: 
 *
 * Created on 
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

typedef enum{
    DirectionRight =0,
    DirectionLeft =1,
    DirectionAll  =2,
}_DirectionLamp;
extern uint8_t PowerState;


//typedef enum { ndtYear, ndtMonth, ndtDay, ndtHour, ndtMinute, ndtSecond, MAXndtDATE } seqDATE;
//typedef union  {
//                          U8 n[MAXndtDATE];
//                          struct {
//                                    U8 year;   // 0..99 for 2000..2099
//                                    U8 month;  // 1..12
//                                    U8 day;    // 1..31
//                                    U8 hour;   // 0..23
//                                    U8 minute; // 0..59
//                                    U8 second; // 0..59
//                                 } dt;
//                       } stuDATE  ,mDate;       
//typedef enum { ntkTEMP, ntkRH, ntkCO2, MAXntkTHCMLKIND } seqTHCMLKIND;                       
//typedef union  {
//                          S16 va[MAXntkTHCMLKIND];
//                          struct {
//                                    S16 TEMP;
//                                    U16 RH;
//                                    U16 CO2;
//                                 } kd;
//                       } stuValueTHCML;
//typedef struct {
//                         stuValueTHCML value;
//                               stuDATE date;
//                       } stuTHCML;

extern void Unlock_Handle(void);
extern void Lock_Handle(void);
extern void DRV8872_Sleep(void);
extern void Set_TurnSignal(uint8_t Dir, uint8_t control);
#endif	/* PROCESS_H */

