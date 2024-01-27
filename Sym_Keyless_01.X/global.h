/* 
 * File:   global.h
 * Author: HSIAO HSIN-TUNG at CHELIC CO.,Ltd.
 *
 * Created on 2020年8月28日, 上午 8:00
 */

#ifndef GLOBAL_H
#define	GLOBAL_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif


#define     __I     volatile const   /*!< defines 'read only' permissions     */
#define     __O     volatile         /*!< defines 'write only' permissions    */
#define     __IO    volatile         /*!< defines 'read / write' permissions  */
	
	/*!< Signed integer types  */
	typedef   signed char     int8_t;
	typedef   signed short    int16_t;
	typedef   signed long     int32_t;

	typedef   signed char     S8;
	typedef   signed short    S16;
	typedef   signed long     S32;

	typedef int32_t  s32;
	typedef int16_t  s16; 
	typedef int8_t   s8;
    
    typedef int32_t  INT32_t;
	typedef int16_t  INT16_t;
	typedef int8_t   INT8_t;
	
	/*!< Unsigned integer types  */
	typedef unsigned char     uint8_t;
	typedef unsigned short    uint16_t;
	typedef unsigned long     uint32_t;
		
    
	typedef unsigned char     U8;
	typedef unsigned short    U16;
	typedef unsigned long     U32;
		
	typedef uint32_t  u32;
	typedef uint16_t  u16;
	typedef uint8_t   u8;
	
    typedef uint32_t  UINT32_t;
	typedef uint16_t  UINT16_t;
	typedef uint8_t   UINT8_t;

	
	typedef                float   FLOAT;
	typedef                double  DOUBLE;
	typedef          long  double  LDOUBLE;
	
	#define U8_MAX     (255uL)
	#define S8_MAX     (127L)
	#define S8_MIN     (-128L)
	#define U16_MAX    (65535u)
	#define S16_MAX    (32767L)
	#define S16_MIN    (-32768)
	#define U32_MAX    (4294967295uL)
	#define S32_MAX    (2147483647L)
	#define S32_MIN    (-2147483648L)
    
	#define NOP2()		NOP();NOP();
	#define NOP4()		NOP2();NOP2();
	#define NOP8()		NOP4();NOP4();
	#define NOP16()		NOP8();NOP8();
	#define NOP32()		NOP16();NOP16();
	
	enum { DISABLE=0,ENABLE=1};	
	enum { NO=0, YES=1 };
	enum { OFF=0, ON=1 };
	enum { PASS=0, BUSY=1, FAIL=1 };
    enum { RESET=0,SET};
	enum { FALSE=0,TRUE=1};

     typedef  enum {IntOSC_31KHz = 0,
                   IntOSC_31K25Hz = 2,
                   IntOSC_62K5Hz = 4,
                   IntOSC_125KHz = 5,
                   IntOSC_250KHz = 6,
                   IntOSC_500KHz = 7,
                   /*
                    * Reserver  8~10
                    */
                   IntOSC_1MHz = 11,
                   IntOSC_2MHz = 12,
                   IntOSC_4MHz = 13,
                   IntOSC_8MHz = 14,
                   IntOSC_16MHz = 15,
                  }_MCU_IntOsc;


/*=======================================================================*/
	#define U8toBCD( num )  (((((num)/10)<<4)+((num)%10)))
	#define BCDtoU8( num )  (((num)>>4)*10+((num)&0xF))
	#define ASCtoHEX( asc ) ((asc) > '9' ? (asc)-'A'+10 : (asc)-'0')
	#define HEXtoASC( hex ) ((hex) >  9  ? (hex)+'A'-10 : (hex)+'0')
	#define ASCtoDEC( asc ) ((asc)-'0')
	#define DECtoASC( dec ) ((dec)+'0')
/*-----------------------------------------------------------------------*/	
/*=======================================================================*/
#define BITn( b )       MASK(b)      /* note: force to U8/U16/U32 to get better optimization */
#define BIT0            ((U8)BITn(0))
#define BIT1            ((U8)BITn(1))
#define BIT2            ((U8)BITn(2))
#define BIT3            ((U8)BITn(3))
#define BIT4            ((U8)BITn(4))
#define BIT5            ((U8)BITn(5))
#define BIT6            ((U8)BITn(6))
#define BIT7            ((U8)BITn(7))
#define BIT8            ((U16)BITn(8))
#define BIT9            ((U16)BITn(9))
#define BIT10           ((U16)BITn(10))
#define BIT11           ((U16)BITn(11))
#define BIT12           ((U16)BITn(12))
#define BIT13           ((U16)BITn(13))
#define BIT14           ((U16)BITn(14))
#define BIT15           ((U16)BITn(15))
#define BIT16           ((U32)BITn(16))
#define BIT17           ((U32)BITn(17))
#define BIT18           ((U32)BITn(18))
#define BIT19           ((U32)BITn(19))
#define BIT20           ((U32)BITn(20))
#define BIT21           ((U32)BITn(21))
#define BIT22           ((U32)BITn(22))
#define BIT23           ((U32)BITn(23))
#define BIT24           ((U32)BITn(24))
#define BIT25           ((U32)BITn(25))
#define BIT26           ((U32)BITn(26))
#define BIT27           ((U32)BITn(27))
#define BIT28           ((U32)BITn(28))
#define BIT29           ((U32)BITn(29))
#define BIT30           ((U32)BITn(30))
#define BIT31           ((U32)BITn(31))
#define BITMASK( b )    (BITn(b)-1)    /* note: force to U8/U16/U32 to get better optimization */
                                       /* 1: 0x1, 2: 0x3, 3: 0x7 4: 0xF .... */
#define BITtoU8( b7,b6,b5,b4,b3,b2,b1,b0 )    ((U8)((b7)*0x80+(b6)*0x40+(b5)*0x20+(b4)*0x10+(b3)*0x08+(b2)*0x04+(b1)*0x02+(b0)*0x01))
/*-----------------------------------------------------------------------*/
	
	#define		_HiISR_		interrupt
	//-#define		_LoISR_		interrupt low_priority
	
	#define		BitSet(var,bitno)	((var)|=1UL<<(bitno))
	#define		BitClr(var,bitno)	((var)&=~(1UL<<bitno))
	#define	    BitChg(var,Place)   ( (var) ^= (uint8_t)((uint8_t)1<<(uint8_t)(Place)) )

/*-----------------------------------------------------------------------*/
#define MASK(bitpos) (1 << (bitpos))        // Create mask for selected bit
#define CAST(t,x)    (*((t *)&(x)))         // Cast x into type t
#define UCHAR(x)     (CAST(UINT8,(x)))      // Cast structure x into unsigned char
#define UINT(x)      (CAST(UINT16,(x)))       // Cast structure x into unsigned integer
#define CTEST(x,y)   (CAST(UINT8,(x)) & (y))// Test bit in UINT8 with mask y (x may be an 8-bit structure)
#define ITEST(x,y)   (CAST(UINT16,(x)) & (y)) // Test bit in uint with mask y (x may be a 16-bit structure)
#define IsBitSet(x,y) ((x) & (y))           // Test bit in UINT8/uint with mask y
#define IsBitClr(x,y) (!((x) & (y)))        // Test bit is 0
#define ToBool(x)    ((UINT8)((x)?1:0))     // Convert bit test to UINT8 0 or 1
#define set(a,b) ((a) |=  (b))              // Apply (OR) mask b to UINT8 a
#define clr(a,b) ((a) &= ~(b))              // Apply (AND) mask ~b to UINT8 a
#define min(a,b) (((a) < (b)) ? (a) : (b))  // Minimum
#define max(a,b) (((a) > (b)) ? (a) : (b))  // Maximum
//#define ABS(a)   ((a < 0) ? (-(a)) : (a))   // Absolute value
#define HIGHBYTE(x)  (*( ((UINT8 *)&(x))+1   )) // For assigning a value to MSB of 16-bit word
#define LOWBYTE(x)   (*( ((UINT8 *)&(x)) )) // For assigning a value to LSB of 16-bit word
#define HHBYTE(x)    (*( ((UINT8 *)&(x))+3   )) // For assigning a value to MSB of 32-bit word
#define HMBYTE(x)    (*( ((UINT8 *)&(x))+2 )) // For assigning a value to 2nd MSB of 32-bit word
#define LMBYTE(x)    (*( ((UINT8 *)&(x))+1 )) // For assigning a value to 2nd LSB of 32-bit word
#define LLBYTE(x)    (*( ((UINT8 *)&(x)) )) // For assigning a value to LSB of 32-bit word

#endif	/* GLOBAL_H */

