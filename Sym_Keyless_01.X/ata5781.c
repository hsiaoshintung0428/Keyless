#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "global.h"
#include "ioports.h"
#include "TMR.h"
#include "spi.h"
#include "delay.h"
#include "ata5781.h"


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
}



unsigned char rf_ata5781_read_version( void )
{
unsigned char rtn;

	// activate slave select for ATA5781
	TRISAbits.TRISA4	= 0;	// NSS = PA4 output
	LATAbits.LATA4	= 0;	// set low on PA4 (NSS)
	_delay1uS(47);
		
	at_rx_spi( 0x13 );	// events.system
	at_rx_spi( 0x00 );	// events.events
	rtn = at_rx_spi( 0x00 );	// ROM version
	at_rx_spi( 0x00 );	// Flash version high
	at_rx_spi( 0x00 );	// flash version low
	at_rx_spi( 0x00 );	// customer version
		
	// release NSS line for ATA5781
	_delay1uS(36);
	LATAbits.LATA4	= 1;	// set pull-up on PA4 (NSS)
	TRISAbits.TRISA4 = 1;	// NSS  = PA4 input
	_delay1uS(17);
	
	return rtn;
}