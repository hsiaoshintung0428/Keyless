/* 
 * File:   main.c
 * Author: Norton.Hsioa
 *
 * Created on October 8, 2023, 10:28 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "global.h"
#include "ioports.h"
//#include "TMR.h"




void Init_ExtOsc(void);

/*
 * 
 */
int main(int argc, char** argv) {
    
    Init_ExtOsc();
//    Init_TMR0();
//    Init_GPIO();
    TRISA   = 0x00;
    while(1)
    {
        
    }

    return (EXIT_SUCCESS);
}

/*
 * Function: Initialization Extern Oscillator
 * Input:None
 * Output:None
 * Modify History:
 */

void Init_ExtOsc(void)
{
    OSCCONbits.SPLLEN = ENABLE; 
    OSCCONbits.IRCF =   ExtOSC_8MHz;
    OSCCONbits.SCS   = 0;        
}


