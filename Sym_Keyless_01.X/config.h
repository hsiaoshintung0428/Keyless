/* 
 * File:   config.h
 * Author: Varcolac_MV_SKU36
 *
 * Created on 2024年1月7日, 下午 11:26
 */

#ifndef CONFIG_H
#define	CONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif

//IDLOC
//-#pragam config IDLOC1 = 1, IDLOC2 = 2, IDLOC3= 3, IDLOC4 = 4;
#pragma config IDLOC0 = 0
#pragma config IDLOC1 = 1
#pragma config IDLOC2 = 2
#pragma config IDLOC3 = 3

//CONFIG1
#pragma config FOSC = INTOSC  // Oscillator Selection->HS Oscillator, High-speed crystal/resonator connected between OSC1 and OSC2 pins
#pragma config WDTE = OFF    // Watchdog Timer Enable->WDT disabled
#pragma config PWRTE = OFF    // Power-up Timer Enable->PWRT enabled
#pragma config MCLRE = ON    // MCLR Pin Function Select->MCLR/VPP pin function is MCLR
#pragma config CP = ON    // Flash Program Memory Code Protection->Program memory code protection is enabled
#pragma config BOREN = ON    // Brown-out Reset Enable->Brown-out Reset enabled
#pragma config CLKOUTEN = OFF    // Clock Out Enable->CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin
#pragma config IESO = ON    // Internal/External Switchover->Internal/External Switchover Mode is enabled
#pragma config FCMEN = ON    // Fail-Safe Clock Monitor Enable->Fail-Safe Clock Monitor is enabled

//CONFIG2
//#pragma config DEBUG = OFF      // In-Circuit Debugger Mode->In-Circuit Debugger disabled, ICSPCLK and ICSPDAT are general purpose I/O pins    
#pragma config WRT = OFF    // Flash Memory Self-Write Protection->Write protection off
#pragma config PLLEN = ON    // PLL Enable->4x PLL is enabled
#pragma config STVREN = ON    // Stack Overflow/Underflow Reset Enable->Stack Overflow or Underflow will cause a Reset
#pragma config BORV = LO    // Brown-out Reset Voltage Selection->Brown-out Reset Voltage (Vbor), low trip point selected.
#pragma config LVP = ON    // Low-Voltage Programming Enable->Low-voltage programming enabled
#pragma config LPBOR = ON    // Low-Power Brown-out Reset Enable Bit->Low-Power BOR is enabled
#pragma config PPS1WAY = OFF    // Peripheral Pin Select one-way control->The PPSLOCK bit can be set and cleared repeatedly by software
#pragma config ZCD = OFF         // Zero-cross detect disable->ZCD disabled. ZCD can be enabled by setting the ZCDSEN bit of ZCDCON

   // CONFIG1
//#pragma config FOSC = INTOSC    // Oscillator Selection Bits->INTOSC oscillator: I/O function on CLKIN pin
//#pragma config WDTE = OFF    // Watchdog Timer Enable->WDT disabled
//#pragma config PWRTE = OFF    // Power-up Timer Enable->PWRT disabled
//#pragma config MCLRE = ON    // MCLR Pin Function Select->MCLR/VPP pin function is MCLR
//#pragma config CP = OFF    // Flash Program Memory Code Protection->Program memory code protection is disabled
//#pragma config BOREN = ON    // Brown-out Reset Enable->Brown-out Reset enabled
//#pragma config CLKOUTEN = OFF    // Clock Out Enable->CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin
//#pragma config IESO = ON    // Internal/External Switchover Mode->Internal/External Switchover Mode is enabled
//#pragma config FCMEN = ON    // Fail-Safe Clock Monitor Enable->Fail-Safe Clock Monitor is enabled
//
//// CONFIG2
//#pragma config WRT = OFF    // Flash Memory Self-Write Protection->Write protection off
//#pragma config PPS1WAY = ON    // Peripheral Pin Select one-way control->The PPSLOCK bit cannot be cleared once it is set by software
//#pragma config ZCD = OFF    // Zero-cross detect disable->Zero-cross detect circuit is disabled at POR
//#pragma config PLLEN = ON    // Phase Lock Loop enable->4x PLL is always enabled
//#pragma config STVREN = ON    // Stack Overflow/Underflow Reset Enable->Stack Overflow or Underflow will cause a Reset
//#pragma config BORV = LO    // Brown-out Reset Voltage Selection->Brown-out Reset Voltage (Vbor), low trip point selected.
//#pragma config LPBOR = OFF    // Low-Power Brown Out Reset->Low-Power BOR is disabled
//#pragma config LVP = ON    // Low-Voltage Programming Enable->Low-voltage programming enabled
//    


#ifdef	__cplusplus
}
#endif

#endif	/* CONFIG_H */

