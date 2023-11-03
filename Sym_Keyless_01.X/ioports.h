/* 
 * File:   ioports.h
 * Author: Varcolac_MV_SKU36
 *
 * Created on 2023年10月31日, 下午 9:49
 */

#ifndef IOPORTS_H
#define	IOPORTS_H

#ifdef	__cplusplus
extern "C" {
#endif
#ifdef	__cplusplus
  
}
#endif

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//For TRISxbits.TRISxN use
#define GPIO_DIR_INPUT  1 //Pin functions as an input
#define GPIO_DIR_OUTPUT 0 //Pin functions as an output
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define ptRPMDET    PORTA   //R.A0 = I/P(Digit)
#define piRPMDET    PORTA   //Input register
#define pdPRMDET    TRISA   //Direction register 
#define pbnRPMDET   0
#define pbmRPMDET   BITn(pbnRPMDET)

#define ISRPMDET()   ((piRPMDET&pbmRPMDET)==pbmRPMDET)
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define ptSEATON    PORTA   //R.A2 = O/P(Digit) 
#define piSEATON    PORTA   //Input register
#define pdSEATON    TRISA   //Direction register 
#define poSEATON    LATA    //Output register 
#define pbnSEATON   2
#define pbmSEATON   BITn(pbnSEATON)

#define SetSEATON(a) { if(a)  (poSEATON|pbmSEATON)  \
                      else   (poSEATON&(~pbmSEATON))}

#define ISSEATON()   ((piSEATON&pbmSEATON)==pbmSEATON)
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define ptIGNTON   PORTA   //R.A3 = O/P(Digit)
#define piIGNON    PORTA
#define pdIGNON    TRISA
#define poIGNON    LATA
#define pbnIGNON   3
#define pbmIGNON    BITn(pbnIGNON)

#define SetIGNON(a) { if(a)  (poIGNON|pbmIGNON)  \
                      else   (poIGNON&(~pbmIGNON))}

#define ISIGNON()   ((piIGNON&pbmIGNON)==pbmIGNON)

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define ptRFRESET    PORTA   //R.A4 = O/P(Digit)
#define piRFRESET    PORTA
#define pdRFRESET    TRISA
#define poRFRESET    LATA
#define pbnRFRESET   4
#define pbmRFRESET    BITn(pbnRFRESET)

#define SetRFRESET(a)  {if(a)  (poRFRESET|pbmRFRESET);  \
                        else   (poRFRESET&(~pbmRFRESET));}

#define ISRFRESET()   ((piRFRESET&pbmRFRESET)==pbmRFRESET)
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define ptP_1    PORTA   //R.A5 = I/P(Digit)
#define piP_1    PORTA
#define pdP_1    TRISA
#define poP_1    LATA
#define pbnP_1   5
#define pbmP_1   BITn(pbnRFRESET)

#define SetP_1(a) { if(a)  (poP_1|pbmP_1);  \
                    else   (poP_1&(~pbmP_1));}

#define ISP_1()   ((piP_1&pbmP_1)==pbmP_1)
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#define def_PORTA_DIR           ((uint8_t)0xFF & ~(pbmRPMDET|pbmP_1))  //TRISA 
#define def_PORTA_INITIAL       ((uint8_t)0x00)                        //LATA   
#define def_PORTA_ANALOG        (uint8_t)0x00                          //ANSELA
#define def_PORTA_PULLUP        (uint8_t)0xFF                          //WPUA
#define def_PORTA_OPENDRAIN     (uint8_t)0x00                          //ODCONA
#define def_PORTA_PWMSlewRate   (uint8_t)0xFF                          //SLRCONA
#define def_PORTA_InputLevel    (uint8_t)0xFF                          //INLVLA               
#define def_PORTA_Current       (uint8_t)0x00                          //HIDRVA
#define def_PORTA_Int_PEDGE     (uint8_t)0x00                          //IOCAP 
#define def_PORTA_Int_NEDGE     (uint8_t)0x00                          //IOCAN 
#define def_PORTA_Int_FLAG      (uint8_t)0x00                          //IOCAF

#define def_PORTB_DIR
#define def_PORTC_DIR
#define def_PORTD_DIR
#define def_PORTE_DIR
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//For LATxbits.LATxN use
#define GPIO_OUTPUT_HIGH 1  // Set output high
#define GPIO_OUTPUT_LOW 0   // Set output low


#define def_PORTB_INITIAL
#define def_PORTC_INITIAL
#define def_PORTD_INITIAL
#define def_PORTE_INITIAL
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//For ANSELxbits.ANSxN use
#define GPIO_TYPE_Analog    1   //Set Analog input
#define GPIO_TYPE_Digital   0   //Set Digital I/O


#define def_PORTB_ANALOG
#define def_PORTC_ANALOG
#define def_PORTD_ANALOG
#define def_PORTE_ANALOG
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//For WPUxbits.WPUxN use
#define GPIO_PUPD_PULLUP  1 //Internal pull-down resistor enabled
#define GPIO_PUPD_NONE    0 //Internal pull-up disabled


#define def_PORTB_PULLUP
#define def_PORTC_PULLUP
#define def_PORTD_PULLUP
#define def_PORTE_PULLUP
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//For ODCONxbits.ODxN use
#define GPIO_OUTBUF_OPEN_DRAIN    1 // Set open-drain drive
#define GPIO_OUTBUF_PUSH_PULL     0 // Set  push-pull drive


#define def_PORTB_OPENDRAIN
#define def_PORTC_OPENDRAIN
#define def_PORTD_OPENDRAIN
#define def_PORTE_OPENDRAIN      
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//For SLRCONxbits.SLRxN use
#define GPIO_NormalSlewRate 1   // Set slew rate is limited
#define GPIO_MaxSlewRate    0   //Set slews at maximum rate

   
#define def_PORTB_PWMSlewRate 
#define def_PORTC_PWMSlewRate 
#define def_PORTD_PWMSlewRate 
#define def_PORTE_PWMSlewRate 
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//For INLVLxbits.INLVLxN use
#define GPIO_InputLevel_ST  1   // Set digital input operates with ST thresholds
#define GPIO_InputLevel_TTL 0   // Set digital input operates with TTL thresholds


#define def_PORTB_InputLevel 
#define def_PORTC_InputLevel 
#define def_PORTD_InputLevel 
#define def_PORTE_InputLevel 
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//For  HIDRVxbits.HIDxN use
#define GPIO_HighCurrent_Out    1 //Set High current source and sink enabled(100mA)
#define GPIO_LowCurrent_Out     0 //Set Standard current source and sink(50mA)

#define def_PORTA_Current   
#define def_PORTB_Current
#define def_PORTC_Current
#define def_PORTD_Current
#define def_PORTE_Current
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//For  IOCxPbits.IOCxPn use
#define GPIO_INTR_RISING_EDGE  1 //Positive edge
#define GPIO_INTR_NRISING_EDGE 0 //disabled associated
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//For  IOCxNbits.IOCxNn use
#define GPIO_INTR_FALLING_EDGE  1 //Negative edge
#define GPIO_INTR_NFALLING_EDGE 0 //disabled associated
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//For  IOCxFbits.IOCxFN use
#define GPIO_INTR_FLAG_CLS      0 //Clear interrupt flags
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//For PPS unlock sequence... 
/*PPS Unlock Sequence (C language)
//INTCON0bits.GIE = 0;         //Suspend interrupts
//PPSLOCK = 0x55;              //Required sequence
//PPSLOCK = 0xAA;              //Required sequence
//PPSLOCKbits.PPSLOCKED = 0;   //Clear PPSLOCKED bit 
//INTCON0bits.GIE = 1;         //Restore interrupts
*/
#define UnlockIO() {INTCONbits.GIE = 0;\  
                    PPSLOCK = 0x55;\
                    PPSLOCK = 0xAA;\
                    PPSLOCKbits.PPSLOCKED = 0;\
                    INTCONbits.GIE = 1;}
                    
 /*PPS Lock Sequence (C language)
//INTCON0bits.GIE = 0;         //Suspend interrupts
//PPSLOCK = 0x55;              //Required sequence
//PPSLOCK = 0xAA;              //Required sequence
//PPSLOCKbits.PPSLOCKED = 1;   //Set PPSLOCKED bit 
//INTCON0bits.GIE = 1;         //Restore interrupts
 */
#define LockIO(){INTCONbits.GIE = 0;\
                 PPSLOCK = 0x55;\
                 PPSLOCK = 0xAA;\
                 PPSLOCKbits.PPSLOCKED = 1;\
                 INTCONbits.GIE = 1;}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//For PPS remap internal source 
#define _ppsPORTA_  0
#define _ppsPORTB_  1
#define _ppsPORTC_  2
#define _ppsPORTD_  3
#define _ppsPORTE_  4

#define _ppsPIN0_   0
#define _ppsPIN1_   1
#define _ppsPIN2_   2
#define _ppsPIN3_   3
#define _ppsPIN4_   4
#define _ppsPIN5_   5
#define _ppsPIN6_   6
#define _ppsPIN7_   7
//PPS remap output 
#define ppsOutmap(x,y) ((x<<3)|(y))    //x=PORTx,Y=GPIOn 

//PPS remap external source 
typedef enum
{
    _pps_Out_LC1_ =1, //PortA,PortC
    _pps_Out_LC2_ =2, //PortA,PortC
    _pps_Out_LC3_ =3, //PortB,PortD
    _pps_Out_LC4_ =4, //PortB,PortD
    
    _pps_Out_COG1A_ =5,//PortB,PortC
    _pps_Out_COG1B_ =6,//PortB,PortD
    _pps_Out_COG1C_ =7,//PortB,PortD
    _pps_Out_COG1D_ =8,//PortB,PortD
    
    _pps_Out_COG2A_ =9,//PortB,PortC
    _pps_Out_COG2B_ =10,//PortB,PortD
    _pps_Out_COG2C_ =11,//PortB,PortD
    _pps_Out_COG2D_ =12,//PortB,PortD
    
    _pps_Out_COG3A_,//PortB,PortC
    _pps_Out_COG3B_,//PortA,PortE
    _pps_Out_COG3C_,//PortA,PortD
    _pps_Out_COG3D_,//PortA,PortD

    _pps_Out_COG4A_,//PortB,PortC
    _pps_Out_COG4B_,//PortA,PortE
    _pps_Out_COG4C_,//PortA,PortD
    _pps_Out_COG4D_,//PortA,PortD

    _pps_Out_CCP1_,//PortB,PortC
    _pps_Out_CCP2_,//PortB,PortC
    _pps_Out_CCP7_,//PortB,PortD
    _pps_Out_CCP8_,//PortB,PortD

    _pps_Out_PWM3_,//PortE
    _pps_Out_PWM4_,//PortD
    _pps_Out_PWM9_,//PortB
    _pps_Out_PWM10_,//PortB
    
    _pps_Out_PWM5_,//PortD
    _pps_Out_PWM6_,//PortD
    _pps_Out_PWM11_,//PortA,PortD
    _pps_Out_PWM12_,//PortA,PortD
    
    _pps_Out_SCK_,//PortB,PortC
    _pps_Out_SDA_,//PortB,PortC
    _pps_Out_SD0_,//PortB,PortC

    _pps_Out_TX_,//PortB,PortC
    _pps_Out_DT_,//PortB,PortC

    _pps_Out_C1_,//PortA,PortD
    _pps_Out_C2_,//PortA,PortE
    _pps_Out_C3_,//PortB,PortD
    _pps_Out_C4_,//PortB,PortD
    _pps_Out_C5_,//PortA,PortD
    _pps_Out_C6_,//PortA,PortE
    _pps_Out_C7_,//PortB,PortD
    _pps_Out_C8_,//PortB,PortD

    _pps_Out_MD1Out_,//PortA,PortD
    _pps_Out_MD2Out_,//PortA,PortD
    _pps_Out_MD3Out_,//PortB,PortD
    _pps_Out_MD4Out_ = 49 ,//PortB,PortD
}PPS_Output_PERIPHERAL;



//**********EXTERN API******************//

extern void Init_GPIO(void);


#endif	/* IOPORTS_H */

