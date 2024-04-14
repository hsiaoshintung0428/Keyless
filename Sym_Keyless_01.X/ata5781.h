/* 
 * File:   ata5781.h
 * Author: Varcolac_MV_SKU36
 *
 * Created on 2024年4月11日, 下午 10:02
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
extern unsigned char rf_ata5781_read_version( void );

#ifdef	__cplusplus
}
#endif

#endif	/* ATA5781_H */

