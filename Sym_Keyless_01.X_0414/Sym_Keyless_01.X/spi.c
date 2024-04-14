
/* 
 * File:   spi.c
 * Author: Norton.Hsioa
 *
 * Created on October 8, 2023, 10:28 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "global.h"
#include "ioports.h"
#include "TMR.h"
#include "spi.h"
#include "delay.h"

void Init_SPI(void)
{

    
    // this setting selects master mode with frequency fosc/64
    SSP1CON1bits.SSPM0 = 1;
    SSP1CON1bits.SSPM1 = 0;
    SSP1CON1bits.SSPM2 = 0;
    SSP1CON1bits.SSPM3 = 0;
    // Enable SPI Port
    SSP1CON1bits.SSPEN = 1;
    // Configure The Clock Polarity & Phase
    SSP1CON1bits.CKP = 0;
    
    SSPSTATbits.CKE = 0;
    //  Slew rate control enabled for High Speed mode
    SSPSTATbits.SMP = 0;
   // Set SPI pins as digital I/O
    TRISC5 = 0; // SDO -> Output
    TRISC4 = 1; // SDI -> Input
    TRISC3 = 0; // SCK -> Output
    //Uncommnent this line, if you want to send send over interrupt
    // SSPIE = 1; PEIE = 1; GIE = 1;
}

//Get SPI data
unsigned char at_rx_spi(unsigned char data)
{
    uint8_t count = 0;
    SSP1BUF = data;
   
    while(SSP1STATbits.BF)
    {
        count++;
       _delay1uS(125);
    }
    return SSP1BUF;
}

void at_tx_spi(unsigned char data)
{
    uint8_t count = 0;
    SSP1BUF = data;
   
    while(SSP1STATbits.BF)
    {
        count++;
       _delay1uS(125);
    }
}

void at_readspi(unsigned char *DataPtr,unsigned char length, unsigned char out_byte)
{
          unsigned char i;
        
	for(i=0; i<length; i++){
		*DataPtr++ = at_rx_spi(out_byte);
        }  
}

void at_writespi(unsigned char *DataPtr, unsigned char length)
{
         unsigned char i;
        //SPI_PORT &= ~(1<<SPI_SS);  // Set select line low
        for (i=0;i<length;i++){
		at_tx_spi(*DataPtr);
		DataPtr++;
        }   
}
