/* 
 * File:   interrupt.h
 * Author: Varcolac_MV_SKU36
 *
 * Created on 2023年12月6日, 下午 10:25
 */

#ifndef INTERRUPT_H
#define	INTERRUPT_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#ifdef	__cplusplus
}
#endif

#define Set_Globa_Interrupt(n)   INTCONbits.GIE = n
#define Set_Extern_Interrupt(n)  INTCONbits.PEIE = n

 //---TMR0 interrupt--//
#define Set_TMR0IE(n)   INTCONbits.T0IE = n
#define Read_TMR0IF()   INTCONbits.TMR0IF
#define CLS_TMR0IF()   INTCONbits.TMR0IF = 0 

//--TMR1 interrupt--11
#define Set_TMR1IE(n)   PIE1bits.TMR1IE = n
#define Read_TMR1IF()   PIR1bits.TMR1IF
#define CLS_TMR1IF()    PIR1bits.TMR1IF = 0 

 //--Extern modle Interrupt--//
#define Set_INTIE(n)   INTCONbits.INTE = n
#define Read_INTIF()   INTCONbits.INTF
#define CLS_INTIF()   INTCONbits.INTF = 0    
  //--GPIO change Interrupt--//
#define Set_IOCIE(n)   INTCONbits.IOCIE = n
#define Read_IOCIF()   INTCONbits.IOCIF
#define CLS_IOCIF()   INTCONbits.IOCIF = 0
 

//typedef struct{
//        uint8_t GPIO:1;
//        uint8_t TMR1:1;
//    }strFLAG;
//    
//typedef union{
//
//    uint16_t All;
//    strFLAG _bits;
//}_myInterruptFlag;


    typedef struct{
        uint8_t _GPIO:1;
        uint8_t _TMR1:1;
        uint8_t _RFINT:1;
        uint8_t D3:1;
        
        uint8_t D4:1;
        uint8_t D5:1;
        uint8_t D6:1;
        uint8_t D7:1; 
        
        uint8_t D8:1;
        uint8_t D9:1; 
        uint8_t D10:1;
        uint8_t D11:1;
        
        uint8_t D12:1; 
        uint8_t D13:1; 
        uint8_t D14:1; 
        uint8_t D15:1;
           
    }strFLAG;
    
    typedef union{
        uint16_t all;
        strFLAG _bits;
    }uniFLAG;



////++++++++++++++++++++++++++++++++++++++++++++//
//#ifndef _INTERRUPT_C
//#define _INTERRUPT_C extern
//#endif
////++++++++++++++++++++++++++++++++++++++++++++//   
//_INTERRUPT_C near _myInterruptFlag MYINTFLAG;
uniFLAG mFLAG;

extern void Init_interrupt(void);   
//extern void __interrupt() ISR(void)

#endif	/* INTERRUPT_H */

