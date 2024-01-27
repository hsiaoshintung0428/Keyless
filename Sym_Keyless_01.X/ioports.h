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
//For LATxbits.LATxN use
#define GPIO_OUTPUT_HIGH 1  // Set output high
#define GPIO_OUTPUT_LOW 0   // Set output low
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//For ANSELxbits.ANSxN use
#define GPIO_TYPE_Analog    1   //Set Analog input
#define GPIO_TYPE_Digital   0   //Set Digital I/O
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//For WPUxbits.WPUxN use
#define GPIO_PUPD_PULLUP  1 //Internal pull-down resistor enabled
#define GPIO_PUPD_NONE    0 //Internal pull-up disabled
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//For ODCONxbits.ODxN use
#define GPIO_OUTBUF_OPEN_DRAIN    1 // Set open-drain drive
#define GPIO_OUTBUF_PUSH_PULL     0 // Set  push-pull drive 
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//For SLRCONxbits.SLRxN use
#define GPIO_NormalSlewRate 1   // Set slew rate is limited
#define GPIO_MaxSlewRate    0   //Set slews at maximum rate
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//For INLVLxbits.INLVLxN use
#define GPIO_InputLevel_ST  1   // Set digital input operates with ST thresholds
#define GPIO_InputLevel_TTL 0   // Set digital input operates with TTL thresholds
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//For  HIDRVxbits.HIDxN use
#define GPIO_HighCurrent_Out    1 //Set High current source and sink enabled(100mA)
#define GPIO_LowCurrent_Out     0 //Set Standard current source and sink(50mA)
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

#define ptRPMDET    PORTA   //R.A0 = I/P(Digit) ccp or timer input??
#define piRPMDET    PORTA   //Input register
#define pdPRMDET    TRISA   //Direction register 
#define pbnRPMDET   0
#define pbmRPMDET   MASK(pbnRPMDET)

#define ISRPMDET()   ((piRPMDET&pbmRPMDET)==pbmRPMDET)
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define ptSEATON    PORTA   //R.A2 = O/P(Digit) 
#define piSEATON    PORTA   //Input register
#define pdSEATON    TRISA   //Direction register 
#define poSEATON    LATA    //Output register 
#define pbnSEATON   2
#define pbmSEATON   MASK(pbnSEATON)

#define SetSEATON(a) { if(a)  ( set(poSEATON,MASK(pbnSEATON)) ) ; \
                      else    ( clr(poSEATON,MASK(pbnSEATON)) ) ;}

#define ISSEATON()   ((piSEATON&pbmSEATON)==pbmSEATON)
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define ptIGNTON   PORTA   //R.A3 = O/P(Digit)
#define piIGNON    PORTA
#define pdIGNON    TRISA
#define poIGNON    LATA
#define pbnIGNON   3
#define pbmIGNON   MASK(pbnIGNON)

#define SetIGNON(a) { if(a)  (set(poIGNON,MASK(pbnIGNON)));  \
                      else    clr(poIGNON,MASK(pbnIGNON)))

#define ISIGNON()   ((piIGNON&pbmIGNON)==pbmIGNON)

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define ptRFRESET    PORTA   //R.A4 = O/P(Digit)
#define piRFRESET    PORTA
#define pdRFRESET    TRISA
#define poRFRESET    LATA
#define pbnRFRESET   4
#define pbmRFRESET    MASK(pbnRFRESET)

#define SetRFRESET(a)  {if(a)  (set(poRFRESET,MASK(pbnRFRESET)));   \
                        else   (clr(poRFRESET,MASK(pbnRFRESET))); }

#define ISRFRESET()   ((piRFRESET&pbmRFRESET)==pbmRFRESET)
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define ptP_1    PORTA   //R.A5 = I/P(Digit)
#define piP_1    PORTA
#define pdP_1    TRISA
#define poP_1    LATA
#define pbnP_1   5
#define pbmP_1   MASK(pbnRFRESET)

#define SetP_1(a) { if(a)  (set(poP_1,MASK(pbnP_1)));  \
                    else   (set(poP_1,MASK(pbnP_1)));}

#define ISP_1()   ((piP_1&pbmP_1)==pbmP_1)
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//PortA
#define def_PORTA_DIR           ((uint8_t)0xFF & ~(pbmRPMDET|pbmP_1))  //TRISA 
#define def_PORTA_INITIAL       ((uint8_t)(0x00))                    //LATA   
#define def_PORTA_ANALOG        ((uint8_t)(0x00))                    //ANSELA
#define def_PORTA_PULLUP        ((uint8_t)(0x00))                    //WPUA
#define def_PORTA_OPENDRAIN     ((uint8_t)(0x00))                    //ODCONA
#define def_PORTA_PWMSlewRate   ((uint8_t)(0x00))                    //SLRCONA
#define def_PORTA_InputLevel    ((uint8_t)(0x00))                    //INLVLA               
#define def_PORTA_Current       ((uint8_t)(0x00))                    //HIDRVA
#define def_PORTA_Int_PEDGE     ((uint8_t)(0x00))                    //IOCAP 
#define def_PORTA_Int_NEDGE     ((uint8_t)(0x00))                    //IOCAN 
#define def_PORTA_Int_FLAG      ((uint8_t)(0x00))                    //IOCAF
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define ptIMMO      PORTB   //R.B0 = O/P(Digit) PWM ??
#define piIMMO      PORTB
#define pdIMMO      TRISB
#define poIMMO      LATB
#define pbnIMM0     0
#define pbmIMMO     MASK(pbnIMM0)


#define SetIMMOON(a) { if(a)  (set(poIMMO,MASK(pbnIMM0)));\
                        else  (clr(poIMMO,MASK(pbnIMM0)));}

#define ISIMMOON()   ((piIMMO&pbmIMMO)==pbmIMMO)
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define ptN125K      PORTB   //R.B1 = O/P(Digit)  PWM mode??
#define piN125K      PORTB
#define pdN125K      TRISB
#define poN125K      LATB
#define pbnN125K     1
#define pbmN125K     MASK(pbnN125K)


#define SetN125K(a) { if(a)   (set(poN125K,MASK(pbnN125K))); \
                      else    (clr(poN125Ks,MASK(pbnN125K)));)}

#define ISN125K()   ((piN125K&pbmN125K)==pbmN125K)
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define ptSEATDET      PORTB   //R.B2 = i/P(Digit)
#define piSEATDET      PORTB
#define pdSEATDET      TRISB
#define poSEATDET      LATB
#define pbnSEATDET     2
#define pbmSEATDET     MASK(pbnSEATDET)
#define paSEATDET      

#define SetSEATDET(a) { if(a)  (set(poSEATDET,MASK(pbnSEATDET))); \
                        else   (clr(poSEATDET,MASK(pbnSEATDET)));;}

#define ISSEATDET()   ((piSEATDET&pbmSEATDET)==pbmSEATDET)
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define ptPWRADC      PORTB   //R.B3 = i/P(analog)
#define piPWRADC      PORTB
#define pdPWRADC      TRISB
#define poPWRADC      LATB
#define pbnPWRADC     3
#define pbmPWRADC     BITn(pbnSEATDET)
#define adPWRADC      9  

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define ptUART       PORTB   
#define piUART       PORTB
#define pdUART       TRISB
#define poUART       LATB
#define pbnUART_RX      4               // PB.4 I/P UART.RX
#define pbnUART_TX      5               // PB.5 O/P UART.TX
#define pbmUART        (BITn(pbnUART_TX))

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//PortB
#define def_PORTB_DIR           ((uint8_t)0xFF & ~(pbmIMMO|pbmN125K|pbmUART))   
#define def_PORTB_INITIAL       ((uint8_t)(0x00))                      
#define def_PORTB_ANALOG        ((uint8_t)(0x00))                    
#define def_PORTB_PULLUP        ((uint8_t)(0x00))                   
#define def_PORTB_OPENDRAIN     ((uint8_t)(0x00))           
#define def_PORTB_PWMSlewRate   ((uint8_t)(0x00))              
#define def_PORTB_InputLevel    ((uint8_t)(0x00))                              
#define def_PORTB_Current       ((uint8_t)(0x00))                 
#define def_PORTB_Int_PEDGE     ((uint8_t)(0x00))                  
#define def_PORTB_Int_NEDGE     ((uint8_t)(0x00))                 
#define def_PORTB_Int_FLAG      ((uint8_t)(0x00))                   
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define ptLAMP            PORTC   //RC[0.7] = O/P
#define piLAMP            PORTC
#define pdLAMP            TRISC
#define poLAMP            LATC
#define pbnLAMP_Right     0
#define pbnLAMP_Left      7
#define pbmLAMP_Right     BITn(pbnLAMP_Right)
#define pbmLAMP_Left      BITn(pbnLAMP_Left)

//#define SetLAMP_Right(a) { if(a)  (poLAMP|pbmLAMP_Right);  \
//                           else   (poLAMP&(~pbmLAMP_Right));}
//
//#define SetLAMP_Left(a) { if(a)  (poLAMP|pbmLAMP_Left) ; \
//                          else   (poLAMP&(~pbmLAMP_Left));}

//#define SetLAMP_Right(a)  LATCbits.LATC0 = a           
//#define SetLAMP_Left(a)   LATCbits.LATC7 = a  

#define SetLAMP_Right(a)   if(a) set(poLAMP,MASK(pbnLAMP_Right));\
                           else  clr(poLAMP,MASK(pbnLAMP_Right)) ;

#define SetLAMP_Left(a)   if(a) set(poLAMP,MASK(pbnLAMP_Left));\
                          else  clr(poLAMP,MASK(pbnLAMP_Left)) ;
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define ptBuzCon            PORTC   //RC.1 = O/P
#define piBuzCon            PORTC
#define pdBuzCon            TRISC
#define poBuzCon            LATC
#define pbnBuzCon            1
#define pbmBuzCon           BITn(pbnBuzCon)


#define SetBuzCon(a) { if(a) ((set(poBuzCon,MASK(pbnBuzCon))); \
                      else   (clr(poBuzCon,MASK(pbnBuzCon)));}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define ptOCPADC            PORTC   //RC.2 = I/P(Analog)
#define piOCPADC            PORTC
#define pdOCPADC            TRISC
#define poOCPADC            LATC
#define pbnOCPADC            2
#define pbmOCPADC           BITn(pbnOCPADC)
#define adOCPADC              14    //AN14 

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define ptRFSPI             PORTC   //RC[3.4.5] = O/P MSSP module ??
#define piRFSPI             PORTC
#define pdRFSPI             TRISC
#define poRFSPI             LATC
#define pbnRFSPICLK         3     // O/P
#define pbnRFSPIMISO        4   // I/P
#define pbnRFSPIMOSI        5   //O/P
#define pbmRFSPICLK         BITn(pbnRFSPICLK)
#define pbmRFSPIMISO        BITn(pbnRFSPIMOSI)
#define pbmRFSPIMOSI        BITn(pbnRFSPIMOSI)

#define SetRFSPICLK(a) { if(a) (set(poRFSPI,MASK(pbnRFSPICLK))); \
                         else  (clr(poRFSPI,MASK(pbnRFSPICLK)));}

#define SetRFSPIMOSI(a) { if(a) (set(poRFSPI,MASK(pbnRFSPIMOSI))); \
                          else  (clr(poRFSPI,MASK(pbnRFSPIMOSI)));}    

 #define ISRFSPIMISO()   ((piRFSPI&pbmRFSPIMISO)==pbmRFSPIMISO)        
 /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define ptLearnMode           PORTC   //RC.6 = I/P(Digitai) need interrupt??
#define piLearnMode           PORTC
#define pdLearnMode           TRISC
#define poLearnMode           LATC
#define pbnLearnMode            6
#define pbmLearnMode           BITn(pbnLearnMode)


 #define ISLearnMode()   ((piLearnMode&pbmLearnMode)==pbmLearnMode)  
 
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//PortC
#define def_PORTC_DIR           ((uint8_t)0xFF & ~(pbmLAMP_Right|pbmLAMP_Left|pbmBuzCon|pbmRFSPICLK|pbmRFSPIMOSI))  
#define def_PORTC_INITIAL       ((uint8_t)0x00)                           
#define def_PORTC_ANALOG        ((uint8_t)0x00 & ~(pbmOCPADC))          
#define def_PORTC_PULLUP        (uint8_t)0x00

#define def_PORTC_OPENDRAIN     (uint8_t)0x00                          
#define def_PORTC_PWMSlewRate   (uint8_t)0xFF                          
#define def_PORTC_InputLevel    (uint8_t)0xFF                                        
#define def_PORTC_Current       (uint8_t)0x00                          
#define def_PORTC_Int_PEDGE     (uint8_t)0x00                         
#define def_PORTC_Int_NEDGE     (uint8_t)0x00                          
#define def_PORTC_Int_FLAG      (uint8_t)0x00                          
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#define ptBlueLed            PORTD   //RD.2 = I/P
#define piBlueLed            PORTD
#define pdBlueLed            TRISD
#define poBlueLed            LATD
#define pbnBlueLed           2
#define pbmBlueLed           BITn(pbnBlueLed)


#define SetBlueLed(a)       { if(a) (set(poBlueLed,MASK(pbnBlueLed)));  \
                              else   (clr(poBlueLed,MASK(pbnBlueLed)));}                            
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define ptRFSPICS            PORTD   //RD.3 = O/P
#define piRFSPICS            PORTD
#define pdRFSPICS            TRISD
#define poRFSPICS            LATD
#define pbnRFSPICS             3
#define pbmRFSPICS          BITn(pbnRFSPICS)


#define SetRFSPICS(a)       { if(a) (set(poRFSPICS,MASK(pbnRFSPICS)));  \
                              else  (clr(poRFSPICS,MASK(pbnRFSPICS)));}                            
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define ptVINADC           PORTD   //RD.4 = I/P(Analog)
#define piVINADC           PORTD
#define pdVINADC           TRISD
#define poVINADC           LATD
#define pbnVINADC            4
#define pbmVINADC          BITn(pbnVINADC)
#define adVINADC             24    //AN24 
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define ptRFPB6           PORTD   //RD.5 = I/P(Digitai) need interrupt??
#define piRFPB6           PORTD
#define pdRFPB6           TRISD
#define poRFPB6           LATD
#define pbnRFPB6          5
#define pbmRFPB6          BITn(pbnRFPB6)


 #define ISRFPB6()   ((poRFPB6&pbmRFPB6)==pbmRFPB6)  
 /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define ptIGNADC           PORTD   //RD.6 = I/P(Analog)
#define piIGNADC           PORTD
#define pdIGNADC           TRISD
#define poIGNADC           LATD
#define pbnIGNADC          6
#define pbmIGNADC          BITn(pbnIGNADC)
#define adIGNADC           26    //AN24 
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//PortD
#define def_PORTD_DIR           ((uint8_t)0xFF & ~(pbmRFSPICS))  //TRISA 
#define def_PORTD_INITIAL       ((uint8_t)0x00)                        //LATA   
#define def_PORTD_ANALOG        ((uint8_t)0x00|(pbmVINADC|pbmIGNADC))  //ANSELA
#define def_PORTD_PULLUP        (uint8_t)0x00                          //WPUA
#define def_PORTD_OPENDRAIN     (uint8_t)0x00                          //ODCONA
#define def_PORTD_PWMSlewRate   (uint8_t)0xFF                          //SLRCONA
#define def_PORTD_InputLevel    (uint8_t)0xFF                          //INLVLA               
#define def_PORTD_Current       (uint8_t)0x00                          //HIDRVA
#define def_PORTD_Int_PEDGE     (uint8_t)0x00                          //IOCAP 
#define def_PORTD_Int_NEDGE     (uint8_t)0x00                          //IOCAN 
#define def_PORTD_Int_FLAG      (uint8_t)0x00                          //IOCAF
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#define ptMOTOPWM           PORTE   //PE[1.2] = O/P PWM
#define piMOTOPWM           PORTE
#define pdMOTOPWM           TRISE
#define poMOTOPWM           LATE
#define pbnMOTOPWM1         1
#define pbnMOTOPWm2         2
#define pbmMOTOPWM1         BITn(pbnMOTOPWM1)
#define pbmMOTOPWM2         BITn(pbnMOTOPWm2)

#define SetMOTOPWM1(a) { if(a) (set(poMOTOPWM,MASK(pbnMOTOPWM1))); \
                         else  (clr(poMOTOPWM,MASK(pbnMOTOPWM1)));}  

#define SetMOTOPWM2(a) { if(a) (set(poMOTOPWM,MASK(pbnMOTOPWm2)));  \
                         else   (clr(poMOTOPWM,MASK(pbnMOTOPWm2)));}                            

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

//PortE
#define def_PORTE_DIR           ((uint8_t)0xFF & ~(pbmMOTOPWM1|pbmMOTOPWM2))  //TRISA 
#define def_PORTE_INITIAL       ((uint8_t)0x00)                        //LATA   
#define def_PORTE_ANALOG        (uint8_t)0x00                          //ANSELA
#define def_PORTE_PULLUP        (uint8_t)0xFF                          //WPUA
#define def_PORTE_OPENDRAIN     (uint8_t)0x00                          //ODCONA
#define def_PORTE_PWMSlewRate   (uint8_t)0xFF                          //SLRCONA
#define def_PORTE_InputLevel    (uint8_t)0xFF                          //INLVLA               
#define def_PORTE_Current       (uint8_t)0x00                          //HIDRVA
#define def_PORTE_Int_PEDGE     (uint8_t)0x00                          //IOCAP 
#define def_PORTE_Int_NEDGE     (uint8_t)0x00                          //IOCAN 
#define def_PORTE_Int_FLAG      (uint8_t)0x00                          //IOCAF
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
//For PPS remap internal source [Spec:xxxPPS: PERIPHERAL xxx INPUT SELECTION]
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

//PPS remap external source [Spec:AVAILABLE PORTS FOR OUTPUT BY PERIPHERAL]
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
    
    _pps_Out_COG3A_ =13,//PortB,PortC
    _pps_Out_COG3B_ =14,//PortA,PortE
    _pps_Out_COG3C_ =15,//PortA,PortD
    _pps_Out_COG3D_ =16,//PortA,PortD

    _pps_Out_COG4A_ =17,//PortB,PortC
    _pps_Out_COG4B_ =18,//PortA,PortE
    _pps_Out_COG4C_ =19,//PortA,PortD
    _pps_Out_COG4D_ =20,//PortA,PortD

    _pps_Out_CCP1_ =21,//PortB,PortC
    _pps_Out_CCP2_ =22,//PortB,PortC
    _pps_Out_CCP7_ =23,//PortB,PortD
    _pps_Out_CCP8_ =24,//PortB,PortD

    _pps_Out_PWM3_ =25,//PortE
    _pps_Out_PWM4_ =26,//PortD
    _pps_Out_PWM9_ =27,//PortB
    _pps_Out_PWM10_ =28,//PortB
    
    _pps_Out_PWM5_ =29,//PortD
    _pps_Out_PWM6_ =30,//PortD
    _pps_Out_PWM11_ =31,//PortA,PortD
    _pps_Out_PWM12_ =32,//PortA,PortD
    
    _pps_Out_SCK_ =33,//PortB,PortC
    _pps_Out_SDA_ =34,//PortB,PortC
    _pps_Out_SD0_ =35,//PortB,PortC

    _pps_Out_TX_ =36,//PortB,PortC
    _pps_Out_DT_ =37,//PortB,PortC

    _pps_Out_C1_ =38,//PortA,PortD
    _pps_Out_C2_ =39,//PortA,PortE
    _pps_Out_C3_ =40,//PortB,PortD
    _pps_Out_C4_ =41,//PortB,PortD
    _pps_Out_C5_ =42,//PortA,PortD
    _pps_Out_C6_ =43,//PortA,PortE
    _pps_Out_C7_ =44,//PortB,PortD
    _pps_Out_C8_ =45,//PortB,PortD

    _pps_Out_MD1Out_ =46,//PortA,PortD
    _pps_Out_MD2Out_ =47,//PortA,PortD
    _pps_Out_MD3Out_ =48,//PortB,PortD
    _pps_Out_MD4Out_ = 49//PortB,PortD
}PPS_Output_PERIPHERAL;




//**********EXTERN API******************//

extern void Init_GPIO(void);
extern void Init_Sleep_GPIO(void);
extern void Remap_GPIO(void);


#endif	/* IOPORTS_H */

