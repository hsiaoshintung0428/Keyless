/* 
 * File:   spi.h
 * Author: Varcolac_MV_SKU36
 *
 * Created on 2024年4月11日, 下午 10:00
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

