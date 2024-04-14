/* 
 * File:   hef.h
 * Author: Varcolac_MV_SKU36
 *
 * Created on 2024年1月23日, 下午 10:36
 */

#ifndef HEF_H
#define	HEF_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#define FLASHSPACE  0x4000      //单片机的FlashROM大小(Flash Size 28KB)
#define ROWLENGTH   32          //Flash的擦写块大小
#define HEFSPACE	0x3F80      //0x3F80~0x3FFF (Spec table3-1)


extern uint16_t FlashReadWord(uint16_t FlashAddr);
extern  void FlashReadWords(uint16_t FlashAddr , uint16_t *DataStr,uint8_t Length);
extern void FlashReadBytes(uint16_t FlashAddr , uint8_t *DataStr,uint8_t Length);
extern void FlashUnlock(void);
extern void FlashErase(uint16_t FlashAddr);
extern void FlashWriteRow(uint16_t FlashAddr,uint16_t *DataStr,uint8_t Length);
extern void FlashWriteWord(uint16_t FlashAddr,uint16_t data);
extern void FlashWriteByte(uint16_t FlashAddr,uint8_t data);
extern void FlashWriteWords(uint16_t FlashAddr , uint16_t *DataStr,uint8_t Length);
extern void FlashWriteBytes(uint16_t FlashAddr , uint8_t *DataStr,uint8_t Length);






#ifdef	__cplusplus
}
#endif

#endif	/* HEF_H */

