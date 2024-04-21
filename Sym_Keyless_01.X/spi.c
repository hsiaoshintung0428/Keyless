

/* 
 * File:   spi.c
 * Author: 
 *
 * Created on 
 * SPI mode Mode 3?
 * 修改SPI
 * 
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
    SSP1ADD = 1 ;
    // this setting selects master mode with frequency fosc/64
    //32MHz/64=500KHz
    SSP1CON1bits.SSPM = 0b0010;
    
    
    //32MHz/(4*(SSP1ADD+1))=250KHz
//    SSP1ADD = 31 ;
//    SSP1CON1bits.SSPM=0b1010;
    // Enable SPI Port
    
    SSP1CON1bits.SSPEN = 1;
    // Configure The Clock Polarity & Phase
    // SPI waveform 
    SSP1CON1bits.CKP = 0;
    
    SSP1STATbits.CKE = 1;
    SSP1STATbits.SMP = 1;

    SSP1CON1bits.WCOL = 0;
    
    LATDbits.LATD3 = 1;
    TRISDbits.TRISD3 = 0; // CS  (ATA5781 PB5) -> Output(RD3)
    
    
    //  Slew rate control enabled for High Speed mode
    SSPSTATbits.SMP = 0;
   // Set SPI pins as digital I/O
    TRISCbits.TRISC3 = 0; // CLK (ATA5781 PB1) -> Output
    LATCbits.LATC3 = 1;
    
    TRISCbits.TRISC5 = 0; // MOSI(ATA5781 PB2) -> Output
    LATCbits.LATC5 = 1;
    
    TRISCbits.TRISC4 = 1; // MISO(ATA5781 PB3) -> Input
    LATCbits.LATC4 = 0;
  


    //Uncommnent this line, if you want to send send over interrupt
    // SSPIE = 1; PEIE = 1; GIE = 1;
}

//Get SPI data
unsigned char at_rx_spi(unsigned char data)
{
    uint8_t count = 0;
    
    if(SSP1CON1bits.SSPOV)
    {
        count = SSP1BUF ;
    }
    
    SSP1BUF = data;
    
    while(SSP1STATbits.BF)
    {
    }
     _delay1uS(50);
  
     return SSP1BUF;
}


void at_tx_spi(unsigned char data)
{
    uint8_t count = 0;
    SSP1BUF = data;
   
    while(SSP1STATbits.BF)
    {
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


void rf_reset_spi(void)
{
    //Config SPI Lines and handshake lines for ATA5291 & ATtiny261
//	SPI_SCK_IO_OUT	= GPIO_SET_AS_PULL_UP; // set pull-up on PB1 (SCLK)
//	SPI_MOSI_IO_OUT	= GPIO_SET_AS_PULL_UP; // set pull-up on PB2 (MOSI)
//	SPI_MISO_IO_OUT	= GPIO_SET_AS_PULL_UP; // set pull-up on PB3 (MISO)
//
//	RF_IRQ_IO_OUT	= GPIO_SET_AS_PULL_UP; //PORTE |=  ( 1 << 4 ); // set pull-up on PE4 (IRQ  -> IRQ1)
//
//	SPI_SCK_IO_DIR	= GPIO_SET_AS_INPUT;  //SCLK = PB1 input
//	SPI_MOSI_IO_DIR	= GPIO_SET_AS_INPUT;  //MOSI = PB2 input
//	SPI_MISO_IO_DIR	= GPIO_SET_AS_INPUT;  //MISO = PB3 input
//
//	RF_IRQ_IO_DIR	= GPIO_SET_AS_INPUT; //DDRE &= ~( 1 << 4 );  //IRQ  = PE4 input

}