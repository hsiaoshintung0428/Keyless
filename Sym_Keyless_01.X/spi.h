/* 
 * File:   spi.h
 * Author: 
 *
 * Created on 
 */

#ifndef SPI_H
#define	SPI_H

#ifdef	__cplusplus
extern "C" {
#endif

extern void Init_SPI(void);
extern unsigned char at_rx_spi(unsigned char data);

extern void at_tx_spi(unsigned char data);
extern void at_readspi(unsigned char *DataPtr,unsigned char length, unsigned char out_byte);
extern void at_writespi(unsigned char *DataPtr, unsigned char length);

#ifdef	__cplusplus
}
#endif

#endif	/* SPI_H */

