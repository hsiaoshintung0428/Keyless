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

#define Enable_Globa_Interrupt(n)   (INTCONbits.GIE = n)
#define Enable_Extern_Interrupt(n)  (INTCONbits.PEIE = n)

 //---TMR0 interrupt--//
#define Enable_TMR0IE   (INTCONbits.T0IE = n)
#define Read_TMR0IF()   (INTCONbits.TMR0IF)
#define Set_TMR0IF(n)   (INTCONbits.TMR0IF = n) 
 //--Extern modle Interrupt--//
#define Enable_INTE   (INTCONbits.INTE = n)
#define Read_INTF()   (INTCONbits.INTF)
#define Set_INTF(n)   (INTCONbits.INTF = n)    
  //--GPIO change Interrupt--//
#define Enable_IOCIE   (INTCONbits.IOCIE = n)
#define Read_IOCIF()   (INTCONbits.IOCIF)
 
extern void Init_Interttup(void);   
//extern void __interrupt() ISR(void)

#endif	/* INTERRUPT_H */

