/* 
 * File:   ata_api_peps_handler.h
 * 
 * Author: mWS_G9_SKU43
 *
 * Created on April 18, 2024, 4:42 PM
 */

#ifndef ATA_API_PEPS_HANDLER_H
#define	ATA_API_PEPS_HANDLER_H

#ifdef	__cplusplus
extern "C" {
#endif
    
unsigned char aesKey[16];   

void AtaInitPepsBuff( void );
void SelectAntDriver( uint8_t driver );
void SafeEnterPEPS( void );
void CheckRFmessage(void);



#ifdef	__cplusplus
}
#endif

#endif	/* ATA_API_PEPS_HANDLER_H */

