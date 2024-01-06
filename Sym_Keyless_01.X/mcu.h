/* 
 * File:   mcu.h
 * Author: Varcolac_MV_SKU36
 *
 * Created on 2023年10月24日, 下午 10:46
 */

#ifndef MCU_H
#define	MCU_H

#ifdef	__cplusplus
extern "C" {
#endif


#define _PIC16_ 1
#define _PIC18_ 2
#define _PIC24_ 3
#define _DSPIC_ 4
#define _PIC32_ 5

#define MCUFAMILY _PIC16_
#define EnablePLL	1
#if(EnablePLL)
	#define FOSC	(4*8000000)h
#else
	#define FOSC	8000000h
#endif

#if( (MCUFAMILY == _PIC18_ )|| (MCUFAMILY == _PIC16_))
	#define FSYS	(FOSC/4)
#elif( (MCUFAMILY == _PIC24_ )|| (MCUFAMILY == _DSPIC_))
	#define FSYS	(FOSC/2)
#elif(MCUFAMILY == _PIC32_ )
	#define FSYS	(FOSC/1)
#else
 #error MCU not correctly defined
#endif

    
#ifdef _PIC16_
    #define _PIC16F1779_ 1
    #define _PIC16F1778_ 2

    #define _INTERRUPT  __interrupt()
#endif

#define __MCU__     (_PIC16F1779_)

#ifdef	__cplusplus
}
#endif

#endif	/* MCU_H */

