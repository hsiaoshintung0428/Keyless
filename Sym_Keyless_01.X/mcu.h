/* 
 * File:   mcu.h
 * Author: 
 *
 * Created on 
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
	#define mFOSC	(4*8000000uL)
#else
	#define mFOSC	8000000h
#endif

#if( (MCUFAMILY == _PIC18_ )|| (MCUFAMILY == _PIC16_))
	#define FSYS	(mFOSC/4)
    #define INTLFOSC    31000 //LFINTOSC almost equal 31Khz
#elif( (MCUFAMILY == _PIC24_ )|| (MCUFAMILY == _DSPIC_))
	#define FSYS	(mFOSC/2)
#elif(MCUFAMILY == _PIC32_ )
	#define FSYS	(mFOSC/1)
#else
 #error MCU not correctly defined
#endif

    
#ifdef _PIC16_
    #define _PIC16F1779_ 1
    #define _PIC16F1778_ 2

    #define _INTERRUPT  __interrupt()
#endif

#define __MCU__     (_PIC16F1779_)
    
#if(__MCU__ == _PIC16F1779_) 
    
    #define FlashMaxSize 0x4000
    #define HEFSpace 0x3F80 //0x3F80~0x3FFF (Spec table3-1)
    #define RowWrite 32 //Spec table 10-1 one word 
    #define MAXHEFblock ((0x4000-0x3F80)/RowWrite) //4 block~

#endif    
    
#ifdef	__cplusplus
}
#endif

#endif	/* MCU_H */

