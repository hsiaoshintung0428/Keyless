#ifndef _uart_h
#define _uart_h

void Init_uart(void);
void PutChar(uint8_t data);
void Putdata (uint8_t *data);
void CLS (void);
void PutNext (void);
unsigned char GetChat (void);
void DumpintDec (uint32_t data); 
void USART1_HEX(uint8_t data);


#endif