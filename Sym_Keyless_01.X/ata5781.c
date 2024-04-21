#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "global.h"
#include "ioports.h"
#include "TMR.h"
#include "spi.h"
#include "delay.h"
#include "ata5781.h"
/*
 * // Function      MCU         ATA5781 
 * //    CS         RD3(PIN41)  RB5
 * //    CLK        RC3(PIN37)  PB1                     
 * //    MISO       RD4(PIN42)  PB3
 * //    MOSI       RD5(PIN43)  PB2
 * //    nREST      RA4(PIN18)  PC0
 * //    Event      RD5(pin3)   PB6
 */

void rf_ata5831_rd_err_buf (void);

struct rfstruct  rf;

void Init_ATA5781(void)
{
   unsigned char i; 
   //Setup structure
	rf.rom = 0;
	rf.rxlvl = 0;
	rf.rssilvl = 0;
	rf.mode = 0;
	rf.channel = 0;
	rf.events[0] = 0;
	rf.events[1] = 0;
	rf.events[2] = 0;
	rf.events[3] = 0;
	for(i=0; i<32; i++)
	{
		rf.rxbuf[i] = 0;
	    rf.rssibuf[i] = 0;
		rf.txbuf[i] = 0;
	}
    
    LATDbits.LATD3	= 1; // set High on RD3 (NSS)
    LATAbits.LATA4  = 0; // release reset (NRES)
    _delay_ms(2); 
    LATAbits.LATA4 = 1; // release reset (NRES)
    _delay_ms(5);  
 
    {
        rf.rom = rf_ata5781_read_version();
        rf_ata5781_get_events( rf.events ); 
        rf.mode = 0x23;
        rf.channel = 0x00;
        rf_ata5781_set_mode( rf.mode, rf.channel );
  
    }
    
//    TRISBbits.TRISB0 = 0;
//    LATBbits.LATB0 = 1;
//    
//    TRISBbits.TRISB1 = 0; //PWM10 125K?
//    LATBbits.LATB1 = 0;
}
void rf_init_spi(void)
{
    //CS PULL UP
    
}

void rf_set_spi(void)
{
	//Config SPI Lines and handshake lines for ATA5781
	 LATCbits.LATC3 = 1;  // set high on PB1 (SCLK)
	 LATCbits.LATC5	= 1;  // set high on PB2 (MOSI)
	 LATCbits.LATC4= 1;  // set pull-up on PB3 (MISO)
    
	TRISCbits.TRISC3	= 0;   // SCLK = PB1 output
	TRISCbits.TRISC5	= 0;   // MOSI = PB2 output
	TRISCbits.TRISC4	= 1;   // MISO = PB3 input

	_delay_ms( 1 );
}



unsigned char rf_ata5781_read_version( void )
{
unsigned char rtn = 0;

	// activate slave select for ATA5781
  
	//TRISDbits.TRISD3	= 0;	// NSS = RD3 output
	LATDbits.LATD3	= 0;	    // set low on RD3 (NSS)
	_delay1uS(100);
		
	at_rx_spi( 0x13 );	// events.system
 
    at_rx_spi( 0x00 );	// events.events

	rtn = at_rx_spi( 0x00 );	// ROM version
   
	at_rx_spi( 0x00 );	// Flash version high
   
	at_rx_spi( 0x00 );	// flash version low
    
	at_rx_spi( 0x00 );	// customer version
    
		
	// release NSS line for ATA5781
	_delay1uS(50);
	LATDbits.LATD3	= 1;	// set High RD3 (NSS)
    LATDbits.LATD5 = 1;
	_delay1uS(50);
	
	return rtn;
}

void rf_ata5781_get_events( unsigned char buf[] )
{
	// activate slave select for ATA5781
	LATDbits.LATD3	= 0;	    // set low on RD3 (NSS)
	_delay1uS(100);
		
	buf[0] = at_rx_spi( 0x04 );	// events.system
	buf[1] = at_rx_spi( 0x00 );	// events.events
	buf[2] = at_rx_spi( 0x00 );	// events.power
	buf[3] = at_rx_spi( 0x00 );	// events.config
	

	_delay1uS(50);
	LATDbits.LATD3	= 1;	// set High on RD3 (NSS)
    LATDbits.LATD5 = 1;
	_delay1uS(50);
	
	//return;
}

void rf_ata5781_set_mode( unsigned char mode, unsigned char channel )
{
	// activate slave select for ATA5781

	LATDbits.LATD3	= 0;	// set pull-up on RD3 (NSS)
	_delay1uS(100);
	
	at_rx_spi( 0x0D );	// events.system
	at_rx_spi( mode );	// events.events
	at_rx_spi( channel );	// dummy
	
	// release NSS line for ATA5781
	_delay1uS(50);
	LATDbits.LATD3	= 1;	// set High on RD3 (NSS)
    LATDbits.LATD5 = 1;
	_delay1uS(50);
	
	return;
}

//Read Fill Level Rx FIFO 
unsigned char rf_ata5781_read_rx_level( void )
{
unsigned char rtn;

	// activate slave select for ATA5781
	LATDbits.LATD3	= 0;	    // set low on RD3 (NSS)
	_delay1uS(100);
	
	at_rx_spi( 0x01 );	// events.system
	at_rx_spi( 0x00 );	// events.events
	rtn = at_rx_spi( 0x00 );	// bytes

	// release NSS line for ATA5781
	_delay1uS(50);
	LATDbits.LATD3	= 1;	// set High on RD3 (NSS)
    LATDbits.LATD5= 1;
	_delay1uS(50);
	
	return rtn;
}

//Read Rx FIFO
void rf_ata5781_read_rx_buf( unsigned char buf[], unsigned char len )
{
unsigned char i;

	// activate slave select for ATA5781
	LATDbits.LATD3	= 0;	    // set low on RD3 (NSS)
	_delay1uS(100);;
	
	at_rx_spi( 0x06 );	// events.system
	at_rx_spi( len );	// events.events
	at_rx_spi( 0x00 );	// dummy

    if(len>0)
    {
        for(i=0; i<len; i++)
        {
            buf[i] = at_rx_spi( 0x00 );
        }
	}
    
	// release NSS line for ATA5781
    _delay1uS(50);
	LATDbits.LATD3	= 1;	    // set High on RD3 (NSS)
    LATDbits.LATD5 = 1;
	_delay1uS(50);
	
	return;
}


unsigned char rf_ata5781_read_rssi_level( void )
{
unsigned char rtn;

	// activate slave select for ATA5781
    _delay1uS(50);
	LATDbits.LATD3	= 0;	    // set low on RD3 (NSS)
	_delay1uS(50);
	
	at_rx_spi( 0x03 );	// events.system
	at_rx_spi( 0x00 );	// events.events
	rtn = at_rx_spi( 0x00 );	// bytes

	// release NSS line for ATA5781
    _delay1uS(50);
	LATDbits.LATD3	= 1;	    // set High RD3 (NSS)
    LATDbits.LATD5 = 1;
	_delay1uS(50);
	
	return rtn;
}


void rf_ata5781_read_rssi_buf( unsigned char buf[], unsigned char len )
{
unsigned char i;

	// activate slave select for ATA5781
    _delay1uS(50);
	LATDbits.LATD3	= 0;	    // set low on RD3 (NSS)
	_delay1uS(50);
	
	at_rx_spi( 0x05 );	// events.system
	at_rx_spi( len );	// events.events
	at_rx_spi( 0x00 );	// dummy

    if(len)
    {
        for(i=0; i<len; i++)
        {
            buf[i] = at_rx_spi( 0x00 );
        }
    }


	// release NSS line for ATA5781
    _delay1uS(50);
	LATDbits.LATD3	= 1;	    // set High RD3 (NSS)
    LATDbits.LATD5 = 1;
	_delay1uS(50);
	
	return;
}

void rf_ata5831_wr_tx_buf( unsigned char length, unsigned char buf[])
{
	unsigned char i;
	

	LATDbits.LATD3	= 0;	    // set low on RD3 (NSS)
	_delay1uS(100);
	
	at_rx_spi( 0x0B );	// events.system
	at_rx_spi( length );	// events.events
	if(length)
    {
        for(i=0; i<length; i++)
        {
            at_rx_spi( buf[i] );
        }
	}
	
	// release NSS line for ATA5831
    _delay1uS(50);
	LATDbits.LATD3	= 1;	    // set High RD3 (NSS)
    LATDbits.LATD5 = 1;
	_delay1uS(50);
	
	return;
}

void rf_ata5831_rd_err_buf (void)
{
	//unsigned char i;
	

	LATDbits.LATD3	= 0;	    // set low on RD3 (NSS)
	_delay1uS(100);
	
	at_rx_spi( 0x08 );	// events.system
	at_rx_spi( 0x02 );	// events.len
    at_rx_spi( 0x30 );	// events.events
    at_rx_spi( 0x00 );	// events.events
    at_rx_spi( 0x00 );	// events.events
    at_rx_spi( 0x00 );	// events.events
	
	// release NSS line for ATA5831
    _delay1uS(50);
	LATDbits.LATD3	= 1;	    // set High RD3 (NSS)
    LATDbits.LATD5 = 1;
	_delay1uS(50);
    
    _delay1mS(5);
    LATDbits.LATD3	= 0;	    // set low on RD3 (NSS)
	_delay1uS(100);
	
	at_rx_spi( 0x08 );	// events.system
	at_rx_spi( 0x02 );	// events.len
    at_rx_spi( 0x30 );	// events.events
    at_rx_spi( 0x01 );	// events.events
    at_rx_spi( 0x00 );	// events.events
    at_rx_spi( 0x00 );	// events.events
	
	// release NSS line for ATA5831
    _delay1uS(50);
	LATDbits.LATD3	= 1;	    // set High RD3 (NSS)
    LATDbits.LATD5 = 1;
	_delay1uS(50);
    
    
	
	return;
}