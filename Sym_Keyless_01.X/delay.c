#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "config.h"
#include "global.h"



void _delay1uS(uint8_t n);
//---------------------------//
// 功能:延遲1uS              //
//---------------------------//
void _delay1uS(uint8_t n)
{
    do
    {
#if(mFOSC== 4000000UL)
         n /= (U8)(1.0*4.0); // n /= (U8)(1*(1+3)); // based: 4uS
         do { NOP(); } while( --n );
#elif(mFOSC== 8000000UL)
        n /= (U8)(0.5*4.0); // n /= (U8)(0.5*(1+3)); // based: 2uS
        do { NOP(); } while( --n );
#elif(mFOSC== 16000000UL)
        n /= (U8)(0.25*4.0); // n /= (U8)(0.25*(1+3)); // based: 1uS
        do { NOP(); } while( --n );    
#else
        n /= (uint8_t)(0.125*8.0); // n /= (U8)(0.125*(5+4)); // based: 1uS
        do { NOP();} while( --n );    
#endif
    }while(n--);
}

void _delay1mS(uint8_t n)
{
    do
    {
#if(mFOSC== 4000000UL)
        uint8_t tmp;
        do { tmp=665/(1*4); do { NOP(); } while( --tmp ); } while( --n );
#elif(mFOSC== 8000000UL)
        uint8_t tmp;
        do { tmp=3320/(5*4); do { NOP(); } while( --tmp );
        tmp=3320/(5*4); do { NOP(); } while( --tmp ); } while( --n );
#elif(mFOSC== 16000000UL)
        uint8_t tmp,cnt;
        do { cnt=4; do { tmp=1650/(U8)(2.5*4); do { NOP(); } while( --tmp ); } while( --cnt ); } while( --n );   
#else
       uint8_t tmp,cnt;
        do { cnt=8; do { tmp=130/(U8)(0.125*8); do { NOP(); } while( --tmp ); } while( --cnt ); } while( --n );   
#endif
    }while(n--);
}

void _delay1S(uint8_t n)
{
    {
        _delay1mS(250); _delay1mS(250);
         _delay1mS(250); _delay1mS(250);
    }while(n--);
}

