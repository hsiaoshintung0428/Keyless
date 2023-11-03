/* 
 * File:   ioport_core.c
 * Author: Norton.Hsioa
 *
 * Created on October 8, 2023, 10:28 PM
 */

//*****************************//
// PIC16F1779 GPIO initially
//*****************************//
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "global.h"
#include "ioports.h"

// GPIO Control Register Fields




void Init_GPIO(void)
{
//    _unLockPPS_();
//    _LockPPS_(); 
   pbmRFRESET;
   SetRFRESET(TRUE);
    UnlockIO();
    LockIO();
    
}
