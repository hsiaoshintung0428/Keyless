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
#define Set_INTE(n)   INTCONbits.INTE = n
#define Read_INTF()   INTCONbits.INTF
#define CLS_INTF()   INTCONbits.INTF = 0    
  //--GPIO change Interrupt--//
#define Set_IOCIE(n)   INTCONbits.IOCIE = n
#define Read_IOCIF()   INTCONbits.IOCIF
#define CLS_IOCIF()   INTCONbits.IOCIF = 0
 
extern void Init_Interttup(void);   
//extern void __interrupt() ISR(void)

#endif	/* INTERRUPT_H */

