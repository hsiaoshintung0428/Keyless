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


#define PollingTime 10 //mS 
#define PollingTimeToFeq    (1000uL/PollingTime)
#define TMR1PS      TMR1Rate1
#define FillTMR1    (uint16_t) (0xFFFF-((INTLFOSC>>TMR1PS)/PollingTimeToFeq))


#define TMR2INPS 128 //1,4,16,64
#define TMR2OUTPS  1  //1~16

#define TMR2Freq  125 //Hz
#define TMR2Reg   0xFF-(((FSYS/(TMR2INPS*TMR2OUTPS))/TMR2Freq)-1)


//#define Timer0PS    TMR0Rate256
//#define Timer0Rate  (Timer0PS+1)
//#define FillTMR0    ((uint16_t) 256-(((FSYS/PollingTimeToFeq)<<Timer0Rate)))
//#define FillTMR0    (256-157)
//OPTION_REG = 0x87;
//TMR0 = 256- FillTMR0;
//
// 
//CPS	 = (8000000/200)/256 =157  

typedef enum{
    TMR1Rate1 = 0,  //1:1
    TMR1Rate2 = 1,  //1:2    
    TMR1Rate4= 2,   //1:4  
    TMR1Rate8 =3,   //1:8  
}_TMR1CKPS; 

typedef enum{
    TMR1_Source_InterLF = 3,//internal Low power 31kHz 
    TMR1_Source_ExterLF  = 2,//External Low power 32kHz   
    TMR1_Source_SysOSC= 1,  //FOSC
    TMR1_Source_CoreOSC =0, //FOSC/4  
}_TMR1Source; 

//--- TMR0 ----//
#define Set_TMR1Source(n)   T1CONbits.CS =n 
#define Set_TMR1ScaleOSC(n) T1CONbits.CKPS =n
#define Set_TMR1Externalcircuit(n)  T1CONbits.OSCEN =n
#define Set_TMR1ON(n)   T1CONbits.ON = n
#define Set_TMR1SYNCFOSC(n) T1CONbits.SYNC =n

#define Set_TMR1LPOSC(n)    T1CONbits.OSCEN =n







extern void Init_TMR(void);
extern void Init_TMR0(void);
extern void RestoreTMR0(uint8_t value);
extern void Init_TMR2(void);

//---extern API---//
extern void Run_TMR1(uint8_t value ,uint16_t count);
extern void Run_TMR2(uint8_t value ,uint8_t count);

#ifdef	__cplusplus
}
#endif

#endif	/* TMR_H */

