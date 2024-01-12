/* 
 * File:   TMR.h
 * Author: Varcolac_MV_SKU36
 *
 * Created on 2023年11月26日, 下午 5:42
 */

#ifndef TMR_H
#define	TMR_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef enum{
    TMR0Rate2 = 0,
    TMR0Rate4 = 1,    
    TMR0Rate8 = 2,  
    TMR0Rate16 =3,  
    TMR0Rate32 =4 ,  
    TMR0Rate64 = 5,
    TMR0Rate128 =6,
    TMR0Rate256 = 7,
}_TMR0Rate; 


#define PollingTime 5 //mS 
#define PollingTimeToFeq    (1000uL/PollingTime)
#define Timer0PS    TMR0Rate256
#define Timer0Rate  (Timer0PS+1)
#define FillTMR0    ((uint16_t) 256-(((FSYS/PollingTimeToFeq)<<Timer0Rate)))
//#define FillTMR0    (256-157)
//OPTION_REG = 0x87;
//TMR0 = 256- FillTMR0;
//
// 
//CPS	 = (8000000/200)/256 =157  



extern void Init_TMR0(void);
extern void RestoreTMR0(uint8_t value);
extern void Init_TMR2(void);


#ifdef	__cplusplus
}
#endif

#endif	/* TMR_H */

