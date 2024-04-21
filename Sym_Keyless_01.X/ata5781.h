/* 
 * File:   ata5781.h
 * Author: 
 *
 * Created on 
 */

#ifndef ATA5781_H
#define	ATA5781_H

#ifdef	__cplusplus
extern "C" {
#endif


struct rfstruct 
{
	unsigned char rom;
	unsigned char rxlvl;
	unsigned char rssilvl;
	unsigned char events[4];
	unsigned char rxbuf[32];
	unsigned char rssibuf[32];
	unsigned char mode;
	unsigned char channel;
	unsigned char txbuf[32];
};

union valunion
{
	unsigned char u8[2];
	unsigned int  u16;
};

extern struct rfstruct  rf;


extern void Init_ATA5781(void);
extern void rf_set_spi(void);

extern unsigned char rf_ata5781_read_version( void );//o
extern void rf_ata5781_get_events( unsigned char buf[] );//o
extern void rf_ata5781_set_mode( unsigned char mode, unsigned char channel );//o

//Read Fill Level Rx FIFO
extern unsigned char rf_ata5781_read_rx_level( void );//o
extern void rf_ata5781_read_rx_buf( unsigned char buf[], unsigned char len );//o
//Read Fill Level RSSI FIFO
extern unsigned char rf_ata5781_read_rssi_level( void );//o
extern void rf_ata5781_read_rssi_buf( unsigned char buf[], unsigned char len );//o
extern void rf_ata5831_wr_tx_buf( unsigned char length, unsigned char buf[]  );
//


#define BLOCK_SIZE 16
extern unsigned char cryptoBlock[ BLOCK_SIZE ];

#ifdef	__cplusplus
}
#endif

#endif	/* ATA5781_H */

