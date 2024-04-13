#ifndef _uart_h
#define _uart_h

void Init_uart(void);
void PutChar(unsigned char data);
void Putdata (const unsigned char *data);
void CLS (void);
unsigned char GetChat (void);
void DumpintDec (unsigned int val);
void PutNext (void);

#endif