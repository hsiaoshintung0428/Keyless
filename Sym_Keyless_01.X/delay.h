/* 
 * File:   delay.h
 * Author: 
 *
 * Created on 
 */

#ifndef DELAY_H
#define	DELAY_H

#ifdef	__cplusplus
extern "C" {
#endif


void _delay1mS(uint8_t n);
void _delay1uS(uint8_t n);
void _delay1S(uint8_t n);

#define _delay_us(n)  _delay1uS(n)
#define _delay_ms(n)  _delay1mS(n)

#ifdef	__cplusplus
}
#endif

#endif	/* DELAY_H */

