#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "config.h"
#include "global.h"
#include "hef.h"


/*************************************************
* 功能：单字读取函数
* 说明: 按字读取闪存（读取1个16位数据）
* 参数: FlashAddr 需要读取的字的地址
* 返回: PMDAT 读取到的数据
*************************************************/
uint16_t FlashReadWord(uint16_t FlashAddr)
{
    if(FlashAddr >= FLASHSPACE) return (0);
    
    PMCON1bits.CFGS=0;
    PMADR = FlashAddr;
    PMCON1bits.RD=1;
    NOP();
    NOP();
    return PMDAT;
}
/**************************************************
* 功能：多字读取函数
* 说明: 从FLASH中读取多个字到指定数组
* 参数: FlashAddr 要读取的起始地址
*      *DataStr 指向存储数组的指针
*       Length 需要读取的内容长度
* 返回: 无
**************************************************/
void FlashReadWords(uint16_t FlashAddr , uint16_t *DataStr,uint8_t Length)
{
    for(uint8_t i=0;i<Length;i++)
    {
        DataStr[i]=FlashReadWord(FlashAddr);
        FlashAddr++;
    }
}
/**************************************************
* 功能：Bytes读取函数（取程序存储器低8位）
* 说明: 从FLASH中读取多个UINT8数据到指定数组
* 参数: FlashAddr 要读取的起始地址
*      *DataStr 指向存储数组的指针
*       Length 需要读取的内容长度
* 返回: 无
**************************************************/
void FlashReadBytes(uint16_t FlashAddr , uint8_t *DataStr,uint8_t Length)
{
    for(uint8_t i=0;i<Length;i++)
    {
        DataStr[i] = 0xff & FlashReadWord(FlashAddr);
        FlashAddr++;
    }
}

/***************************************************
* 功能：FLASH解锁函数
* 说明: FLASH只有在解锁后才能执块擦除和写入操作
* 参数: 无
* 返回: 无
***************************************************/
void FlashUnlock(void)
{
    PMCON2=0x55;
    PMCON2=0xAA;
    PMCON1bits.WR=1;
    NOP();
    NOP();
}
/***************************************************
* 功能：FLASH按块擦除函数（只能整块擦除ROWLENGTHByte）
* 说明: Flash块擦除（0x0000~0x001F/0x0010~0x002F/..）
* 参数: FlashAddr 被擦除块的首地址
* 返回: 无
***************************************************/
void FlashErase(uint16_t FlashAddr)
{
    INTCONbits.GIE=0;
    PMCON1bits.CFGS=0;
    PMADR = FlashAddr & 0x7fff;
    PMCON1bits.FREE=1;
    PMCON1bits.WREN=1;
    FlashUnlock();
    PMCON1bits.WREN=0;
    INTCONbits.GIE=1;
}
/***************************************************
* 功能：FLASH按块写数据函数
* 说明：FLASH块写入(块长度为32)
* 参数：FlashAddr 块首地址
*      *DataStr 数组指针（单个数据不得大于0x3fff）
*       Length 要写的数据长度（不能超过 ROWLENGTH 个）
* 返回：无
* 重要：按块写入数据不能跨越某些边界(0x0100/0x0200/..)
***************************************************/
void FlashWriteRow(uint16_t FlashAddr,uint16_t *DataStr,uint8_t Length)//必须块地址
{
    uint8_t i=0;
    INTCONbits.GIE=0;
    PMADR = FlashAddr & 0x7fff;
    PMCON1bits.FREE=0;
    PMCON1bits.CFGS=0;
    PMCON1bits.WREN=1;
    PMCON1bits.LWLO=1;
    while(1)
    {
        PMDAT = 0x3fff & DataStr[i];
        i++;
        if(i>=Length) break;
        FlashUnlock();
        PMADRL++;//锁存器地址+1
    }
    PMCON1bits.LWLO=0;
    FlashUnlock();
    PMCON1bits.WREN=0;
    INTCONbits.GIE=1;
}
/***************************************************
* 功能：FLASH按字写函数(写入一个UINT16数据)
* 说明: 任意地址任意字，只写该字，自动原数据重写
* 参数: FlashAddr 写入地址
*       data 写入的内容
* 返回: 无
***************************************************/
void FlashWriteWord(uint16_t FlashAddr,uint16_t data)
{
    uint16_t tmpdata[ROWLENGTH];
    uint16_t rowFlashAddr = FlashAddr & 0xfff0;
    uint8_t wordFlashAddr=FlashAddr & 0x000f;
    if((rowFlashAddr%0x20) > 0)                         //写入地址块对齐
    {
        rowFlashAddr = rowFlashAddr - 0x10;
        wordFlashAddr = wordFlashAddr + 0x10;
    }
    FlashReadWords(rowFlashAddr,tmpdata,ROWLENGTH);              //整块读出数据
    tmpdata[wordFlashAddr] = data;                      //要写入的数据
    FlashErase(rowFlashAddr);                           //擦除整块
    FlashWriteRow(rowFlashAddr,tmpdata,ROWLENGTH);             //整块写入数据
}
/***************************************************
* 功能：FLASH按Byte写函数(写入程序存储器低8位)
* 说明: 任意地址任意Byte，只写该Byte，自动原数据重写
* 参数: FlashAddr 写入地址
*       data 写入的内容
* 返回: 无
***************************************************/
void FlashWriteByte(uint16_t FlashAddr,uint8_t data)
{
    uint16_t tmpdata[ROWLENGTH];
    uint16_t rowFlashAddr = FlashAddr & 0xfff0;
    uint8_t wordFlashAddr=FlashAddr & 0x000f;
    
    if((rowFlashAddr%0x20) > 0)                         //写入地址块对齐
    {
        rowFlashAddr = rowFlashAddr - 0x10;
        wordFlashAddr = wordFlashAddr + 0x10;
    }
    FlashReadWords(rowFlashAddr,tmpdata,ROWLENGTH);               //整块读出数据
    tmpdata[wordFlashAddr] = ((tmpdata[wordFlashAddr]&0xff00)|data);//要写入的数据
    FlashErase(rowFlashAddr);                                   //擦除整块
    FlashWriteRow(rowFlashAddr,tmpdata,ROWLENGTH);              //整块写入数据
}
/***************************************************
* 功能：FLASH写任意长度UINT16函数
* 说明：在任意地址写入任意长度的数据
* 参数：FlashAddr 要写入内容的首地址
*      *DataStr 要写入的数组指针
*       Length 要写入的数组长度
* 返回：无
***************************************************/
void FlashWriteWords(uint16_t FlashAddr , uint16_t *DataStr,uint8_t Length)
{
    uint16_t tmpdata[ROWLENGTH];
    uint8_t tmpLength = 0;
    uint16_t rowFlashAddr = FlashAddr & 0xfff0;
    uint8_t wordFlashAddr=FlashAddr & 0x000f;
    if((rowFlashAddr%0x20) > 0)                                 //写入地址块对齐
    {
        rowFlashAddr = rowFlashAddr - 0x10;
        wordFlashAddr = wordFlashAddr + 0x10;
    }
    while(1)
    {
        FlashReadWords(rowFlashAddr,tmpdata,ROWLENGTH);                  //整块读出数据
        for(uint16_t i=0;i<ROWLENGTH;i++)
        {
            if(i>=wordFlashAddr)
            {
                tmpdata[i] = DataStr[tmpLength];                //要写入的数据
                tmpLength++;
            }
            if(tmpLength>=Length) break;
        }
        FlashErase(rowFlashAddr);                               //擦除整块
        FlashWriteRow(rowFlashAddr,tmpdata,ROWLENGTH);                 //整块写入数据
        rowFlashAddr = rowFlashAddr + 0x20;                     //块地址+1
        wordFlashAddr= 0;
        if(tmpLength>=Length) break;
    }

}
/***************************************************
* 功能：FLASH写任意长度UINT8函数（写入程序存储器低8位）
* 说明：在任意地址写入任意长度的数据
* 参数：FlashAddr 要写入内容的首地址
*      *DataStr 要写入的数组指针
*       Length 要写入的数组长度
* 返回：无
***************************************************/
void FlashWriteBytes(uint16_t FlashAddr , uint8_t *DataStr,uint8_t Length)
{
    uint16_t tmpdata[ROWLENGTH];
    uint8_t tmpLength = 0;
    uint16_t rowFlashAddr = FlashAddr & 0xfff0;
    uint8_t wordFlashAddr=FlashAddr & 0x000f;
    
    if((rowFlashAddr%0x20) > 0)                                     //写入地址块对齐
    {
        rowFlashAddr = rowFlashAddr - 0x10;
        wordFlashAddr = wordFlashAddr + 0x10;
    }
    while(1)
    {
        FlashReadWords(rowFlashAddr,tmpdata,ROWLENGTH);               //整块读出数据
        for(uint16_t i=0;i<ROWLENGTH;i++)
        {
            if(i>=wordFlashAddr)
            {
                tmpdata[i] = ((tmpdata[i]&0xff00)|DataStr[tmpLength]);  //要写入的数据
                tmpLength++;
            }
            if(tmpLength>=Length) break;
        }
        FlashErase(rowFlashAddr);                                   //擦除整块
        FlashWriteRow(rowFlashAddr,tmpdata,ROWLENGTH);              //整块写入数据
        rowFlashAddr = rowFlashAddr + 0x20;                         //块地址+1
        wordFlashAddr= 0;
        if(tmpLength>=Length) break;
    }
}