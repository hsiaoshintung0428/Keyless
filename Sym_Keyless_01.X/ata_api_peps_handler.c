#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "global.h"
#include "ioports.h"
#include "TMR.h"
#include "spi.h"
#include "delay.h"
#include "ata5781.h"
#include "uart.h"
#include "ata_api_aes.h"
#include "ata_api_crc.h"
#include "ata_api_peps_handler.h"

unsigned char aesKey[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char cryptoBlock[16];

void CheckRFmessage(void)
{
	unsigned char i;
	unsigned int sum, j, u16CRC;
	union valunion val;	
	unsigned char index;
	unsigned char Match;
	unsigned char cbuf[20];

	// check of RF reply message event and read RF buffers
	// check for IRQ signal (RF Event)
	if (RF_IRQ_IO_IN == GPIO_INPUT_LOW_LEVEL)
	{
		Match = 0; 
		//rf_set_spi();
		// read RF event bytes and clear RF event
		rf_ata5781_get_events( rf.events );//0x04[Get Event Bytes ]]
		// read RX buffer level
		rf.rxlvl = rf_ata5781_read_rx_level();//0x01[Read Fill Level Rx FIFO ]
		// read RX buffer
		rf_ata5781_read_rx_buf( rf.rxbuf, rf.rxlvl );//0x06[Read Rx FIFO]]
		// read rssi buffer level
		rf.rssilvl = rf_ata5781_read_rssi_level();//0x03[Read Fill Level RSSI FIFO]]
		// read rssi buffer
		rf_ata5781_read_rssi_buf( rf.rssibuf, rf.rssilvl );//0x05[Read RSSI FIFO]

		// report received values if ID ok
		if(rf.rxbuf[0] == 0x39)
		{
			sum = 0;
			for(i=0; i<rf.rssilvl; i++)
			{
				sum += rf.rssibuf[i];
			}
			sum /= rf.rssilvl;
            
			Putdata("0_RF reply received (RF rssi):0x");
            USART1_HEX(sum);
            Putdata("\n");
            
			if(rf.rxbuf[24] == 0x18)	// LF rssi data received; index old was 7
			{
				// start RF RX mode for second data frame
				rf.mode = 0x00;
				rf.channel = 0x00;
				rf_ata5781_set_mode( rf.mode, rf.channel );
				rf.mode = 0x22;
				rf.channel = 0x40;
				rf_ata5781_set_mode( rf.mode, rf.channel );

				Putdata("\n\n");
	
				Putdata("Car Antenna 0:0x ");
				val.u8[0] = rf.rxbuf[1];
				val.u8[1] = rf.rxbuf[2];
				Putdata(" LF-Channel 1 RSSI:0x");
                USART1_HEX(val.u16>>8);
                USART1_HEX(val.u16&0xFF);
               // Putdata("\n");
                
				val.u8[0] = rf.rxbuf[3];
				val.u8[1] = rf.rxbuf[4];
				Putdata(" LF-Channel 2 RSSI:0x");
                USART1_HEX(val.u16>>8);
                USART1_HEX(val.u16&0xFF);
                
                
				val.u8[0] = rf.rxbuf[5];
				val.u8[1] = rf.rxbuf[6];
                
                //Putdata("   LF-Channel 3 RSSI: %4d\n", val.u16);
                Putdata(" LF-Channel 3 RSSI:0x");
                USART1_HEX(val.u16>>8);
                USART1_HEX(val.u16&0xFF);
                Putdata("\n");
				

				Putdata("Car Antenna 1: \n");
				val.u8[0] = rf.rxbuf[7];
				val.u8[1] = rf.rxbuf[8];
                Putdata(" LF-Channel 1 RSSI:0x");
                USART1_HEX(val.u16>>8);
                USART1_HEX(val.u16&0xFF);
      
				//Putdata("   LF-Channel 1 RSSI: %4d", val.u16);
				val.u8[0] = rf.rxbuf[9];
				val.u8[1] = rf.rxbuf[10];
                
                Putdata(" LF-Channel 2 RSSI:0x");
                USART1_HEX(val.u16>>8);
                USART1_HEX(val.u16&0xFF);
				//Putdata("   LF-Channel 2 RSSI: %4d", val.u16);
                
				val.u8[0] = rf.rxbuf[11];
				val.u8[1] = rf.rxbuf[12];
                Putdata(" LF-Channel 3 RSSI:0x");
                USART1_HEX(val.u16>>8);
                USART1_HEX(val.u16&0xFF);
                
				//Putdata("   LF-Channel 3 RSSI: %4d\n", val.u16);
				val.u8[0] = rf.rxbuf[14];
				val.u8[1] = rf.rxbuf[15];
                
                Putdata(" Message-0 Rolling Count:0x");
                USART1_HEX(val.u16>>8);
                USART1_HEX(val.u16&0xFF);
                Putdata("\n");
				//Putdata("   Message-0 Rolling Count: %4d\n", val.u16);
				for ( index = 0; index < 20; index++ )
				{
					cbuf[index] = rf.rxbuf[index];
				}
				for(j=0;j<60000;j++) 
				{
					if (RF_IRQ_IO_IN == GPIO_INPUT_LOW_LEVEL)
					{
						j=61000;
						// read RF event bytes and clear RF event
						rf_ata5781_get_events( rf.events );
						// read RX buffer level
						rf.rxlvl = rf_ata5781_read_rx_level();
						// read RX buffer
						rf_ata5781_read_rx_buf( rf.rxbuf, rf.rxlvl );
						// read rssi buffer level
						rf.rssilvl = rf_ata5781_read_rssi_level();
						// read rssi buffer
						rf_ata5781_read_rssi_buf( rf.rssibuf, rf.rssilvl );

						// report received values if ID ok
						if(rf.rxbuf[0] == 0x39)
						{
							sum = 0;
							for(i=0; i<rf.rssilvl; i++)
							{
								sum += rf.rssibuf[i];
							}
							sum /= rf.rssilvl;
							//Putdata("Second RF frame received (RF rssi: %d):\n", sum);
							if(rf.rxbuf[24] == 0x19)	// LF rssi data 2nd frame is received; index old was 7
							{
								Putdata("Car Antenna 2: \n");
								val.u8[0] = rf.rxbuf[1];
								val.u8[1] = rf.rxbuf[2];
                                Putdata(" LF-Channel 1 RSSI:0x");
                                USART1_HEX(val.u16>>8);
                                USART1_HEX(val.u16&0xFF);
				//				Putdata("   LF-Channel 1 RSSI: %4d ", val.u16);

								val.u8[0] = rf.rxbuf[3];
								val.u8[1] = rf.rxbuf[4];
                                Putdata(" LF-Channel 2 RSSI:0x");
                                USART1_HEX(val.u16>>8);
                                USART1_HEX(val.u16&0xFF);
				//				Putdata("   LF-Channel 2 RSSI: %4d ", val.u16);
								val.u8[0] = rf.rxbuf[5];
								val.u8[1] = rf.rxbuf[6];
                                Putdata(" LF-Channel 3 RSSI:0x");
                                USART1_HEX(val.u16>>8);
                                USART1_HEX(val.u16&0xFF);
                                Putdata("\n");
				//				Putdata("   LF-Channel 3 RSSI: %4d\n", val.u16);

								Putdata("Car Antenna 3: \n");
								val.u8[0] = rf.rxbuf[7];
								val.u8[1] = rf.rxbuf[8];
                                Putdata(" LF-Channel 1 RSSI:0x");
                                USART1_HEX(val.u16>>8);
                                USART1_HEX(val.u16&0xFF);                                
				//				Putdata("   LF-Channel 1 RSSI: %4d", val.u16);
								val.u8[0] = rf.rxbuf[9];
								val.u8[1] = rf.rxbuf[10];
                                Putdata(" LF-Channel 2 RSSI:0x");
                                USART1_HEX(val.u16>>8);
                                USART1_HEX(val.u16&0xFF);                                  
				//				Putdata("   LF-Channel 2 RSSI: %4d", val.u16);
								val.u8[0] = rf.rxbuf[11];
								val.u8[1] = rf.rxbuf[12];
                                Putdata(" LF-Channel 3 RSSI:0x");
                                USART1_HEX(val.u16>>8);
                                USART1_HEX(val.u16&0xFF);  
				//				Putdata("   LF-Channel 3 RSSI: %4d\n", val.u16);
								val.u8[0] = rf.rxbuf[14];
								val.u8[1] = rf.rxbuf[15];
                                Putdata(" Message-1 Rolling Count=0x");
                                USART1_HEX(val.u16>>8);
                                USART1_HEX(val.u16&0xFF);  
                                Putdata(" \n");
				//				Putdata("   Message-1 Rolling Count: %4d\n", val.u16);

								for ( index = 0; index < 16; index++ )
								{
									cryptoBlock[index] = cbuf[index];
								}	
								cipher ( cryptoBlock, scheduleBuffer, aesKey );
								
								if((cbuf[16]==cryptoBlock[0]) && (cbuf[17]==cryptoBlock[1])
									&&(cbuf[18]==cryptoBlock[2])&&(cbuf[19]==cryptoBlock[3]))
                                {
                                    Match = 1;
                                }
								else
								{
									Match = 0;
                                    Putdata("   (Received Message-0 MAC:");
                                    USART1_HEX(cbuf[16]);USART1_HEX(cbuf[17]);
                                    USART1_HEX(cbuf[18]);USART1_HEX(cbuf[19]);
                                    Putdata("   \n)");
				//					Putdata("   Received Message-0 MAC: 0x%02x 0x%02x 0x%02x 0x%02x\n", cbuf[16],cbuf[17],
				//					cbuf[18],cbuf[19]);
                                    Putdata("   (Expected MAC-0 should be: ");
                                    USART1_HEX(cryptoBlock[0]);USART1_HEX(cryptoBlock[1]);
                                    USART1_HEX(cryptoBlock[2]);USART1_HEX(cryptoBlock[3]);
                                    Putdata("   )\n)");
				//					Putdata("   Expected MAC-0 should be: 0x%02x 0x%02x 0x%02x 0x%02x\n", cryptoBlock[0], cryptoBlock[1],
				//					cryptoBlock[2], cryptoBlock[3] );
								}
							
								for ( index = 0; index < 16; index++ )
								{
									cryptoBlock[index] = rf.rxbuf[index];
								}	
								cipher ( cryptoBlock, scheduleBuffer, aesKey );
								if((rf.rxbuf[16]==cryptoBlock[0]) && (rf.rxbuf[17]==cryptoBlock[1])
									&&(rf.rxbuf[18]==cryptoBlock[2])&&(rf.rxbuf[19]==cryptoBlock[3]))
                                {
                                    Match = 1;
                                }
								else
								{
									Match = 0;
                                    Putdata("   (Received Message-1 MAC:");
                                    USART1_HEX(rf.rxbuf[16]);USART1_HEX(rf.rxbuf[17]);
                                    USART1_HEX(rf.rxbuf[18]);USART1_HEX(rf.rxbuf[19]);
                                    Putdata("   \n)");
				//					Putdata("   Received Message-1 MAC: 0x%02x 0x%02x 0x%02x 0x%02x\n", rf.rxbuf[16],rf.rxbuf[17],
				//					rf.rxbuf[18],rf.rxbuf[19]);
                                    Putdata("   (Expected MAC-1 should be:");
                                    USART1_HEX(cryptoBlock[0]);USART1_HEX(cryptoBlock[1]);
                                    USART1_HEX(cryptoBlock[2]);USART1_HEX(cryptoBlock[3]);
                                    Putdata("   \n)");                                    
				//					Putdata("   Expected MAC-1 should be: 0x%02x 0x%02x 0x%02x 0x%02x\n", cryptoBlock[0], cryptoBlock[1],
				//					cryptoBlock[2], cryptoBlock[3] );
								}
								if (Match) 
                                    Putdata(" Key ID Matched\n");
								else 
                                    Putdata(" Did Not Match !\n");
							}
							else if(rf.rxbuf[24] == 0x80)	// Low battery voltage
							{
								Putdata("   ! Low battery voltage !\n\n");
							}
						}
					}
				}
			}//-Read Rx FIFO byte[0]= 0x39
            
			else if(rf.rxbuf[24] == 0x40)	// No valid data received
			{
				Putdata("   ERR: no valid LF data received !\n\n");
			}
			else if(rf.rxbuf[24] == 0x80)	// Low battery voltage
			{
				Putdata("   ! Low battery voltage !\n\n");
			}
			else if(rf.rxbuf[24] == 0x01)	// button S1 pressed
			{
				Putdata("  KeyFob button S1 pressed\n");

				for ( index = 0; index < 16; index++ )
				{
					cryptoBlock[index] = rf.rxbuf[index];
				}
				cipher ( cryptoBlock, scheduleBuffer, aesKey );
                
				if((rf.rxbuf[16]==cryptoBlock[0]) && (rf.rxbuf[17]==cryptoBlock[1])
					&&(rf.rxbuf[18]==cryptoBlock[2])&&(rf.rxbuf[19]==cryptoBlock[3]))
                    {
                        Match=1;
                    }
				else 
                    {
                        Match =0;
                    }

				if (Match)
                    {
                        Putdata("    MAC is correct\n");
                    }
				else
                    {
                        Putdata("    MAC is NOT correct !!\n");

                        Putdata("   (Received RKE Message MAC:");
                        USART1_HEX(cbuf[16]);USART1_HEX(cbuf[17]);
                        USART1_HEX(cbuf[18]);USART1_HEX(cbuf[19]);
                        Putdata("   \n)");                    
    //					Putdata("       Received RKE Message MAC: 0x%02x 0x%02x 0x%02x 0x%02x\n", rf.rxbuf[16],rf.rxbuf[17],
                        //rf.rxbuf[18],rf.rxbuf[19]);

                        Putdata("   (Expected MAC-0 should be: ");
                        USART1_HEX(cryptoBlock[0]);USART1_HEX(cryptoBlock[1]);
                        USART1_HEX(cryptoBlock[2]);USART1_HEX(cryptoBlock[3]);
                        Putdata("   )\n)");      

    //					Putdata("       Expected MAC should be: 0x%02x 0x%02x 0x%02x 0x%02x\n", cryptoBlock[0], cryptoBlock[1],
                    //	cryptoBlock[2], cryptoBlock[3] );
                    }
				CreateTable(0x07);
				u16CRC=0;
				u16CRC = ComputeCRC_8(u16CRC,&rf.rxbuf[0],25);
				if(rf.rxbuf[25] == u16CRC) 
                    {
                        Putdata("    CRC is correct\n\n");
                    }
				else
                    {
                        Putdata("    CRC is NOT correct !\n");
                        Putdata("   (Received Message CRC:0x");
                        USART1_HEX(rf.rxbuf[25]);
                        Putdata(" \n");
                        //Putdata("       Received Message CRC: 0x%02X\n",rf.rxbuf[25]);
                        Putdata("   (Expected CRC should be:0x");
                        USART1_HEX(u16CRC);
                        Putdata(" \n");
                        //Putdata("       Expected CRC should be: 0x%02X\n\n",u16CRC);
                    }
			}
			else if(rf.rxbuf[24] == 0x02)	// button S2 pressed
			{
				Putdata("  KeyFob button S2 pressed\n");
				for ( index = 0; index < 16; index++ )
                    {
                        cryptoBlock[index] = rf.rxbuf[index];
                    }
				cipher ( cryptoBlock, scheduleBuffer, aesKey );
                
				if((rf.rxbuf[16]==cryptoBlock[0]) && (rf.rxbuf[17]==cryptoBlock[1])
				&&(rf.rxbuf[18]==cryptoBlock[2])&&(rf.rxbuf[19]==cryptoBlock[3]))
                {
                    Match=1;
                }
				else 
                {
                    Match =0;
                }
				if (Match) 
                    Putdata("    MAC is correct \n");
				else
				{
					Putdata("    MAC is NOT correct !\n");
                    Putdata("   (Received Message-0 MAC:");
                    USART1_HEX(cbuf[16]);USART1_HEX(cbuf[17]);
                    USART1_HEX(cbuf[18]);USART1_HEX(cbuf[19]);
                    Putdata("   \n)");                    
					//Putdata("       Received RKE Message MAC: 0x%02x 0x%02x 0x%02x 0x%02x\n", rf.rxbuf[16],rf.rxbuf[17],
					//rf.rxbuf[18],rf.rxbuf[19]);
                    Putdata("   (Expected MAC-0 should be: ");
                    USART1_HEX(cryptoBlock[0]);USART1_HEX(cryptoBlock[1]);
                    USART1_HEX(cryptoBlock[2]);USART1_HEX(cryptoBlock[3]);
                    Putdata("   )\n)");                    
					//Putdata("       Expected MAC should be: 0x%02x 0x%02x 0x%2x 0x%02x\n", cryptoBlock[0], cryptoBlock[1],
					//cryptoBlock[2], cryptoBlock[3] );
				}
				CreateTable(0x07);
				u16CRC=0;
//				u16CRC = ComputeCRC_8(u16CRC,&rf.rxbuf[0],25);
				if(rf.rxbuf[25] == u16CRC) 
                {
                    Putdata("    CRC is correct\n\n");
                }
				else
				{
					Putdata("    CRC is NOT correct !\n");
                    Putdata("   Received Message CRC : 0x");
                    USART1_HEX(rf.rxbuf[25]);
                    Putdata(" \n");
					//Putdata("       Received Message CRC: 0x%02X\n",rf.rxbuf[25]);
                    Putdata("   Expected CRC should be: 0x");
                    USART1_HEX(u16CRC);
                    Putdata(" \n");
					//Putdata("       Expected CRC should be: 0x%02X\n\n",u16CRC);
				}
			}
			else if(rf.rxbuf[24] == 0x04)	// button S3 pressed
			{
				Putdata("  KeyFob button S3 pressed\n");
				for ( index = 0; index < 16; index++ )
				{
					//cryptoBlock[index] = rf.rxbuf[index];
				}
				cipher ( cryptoBlock, scheduleBuffer, aesKey );
				if((rf.rxbuf[16]==cryptoBlock[0]) && (rf.rxbuf[17]==cryptoBlock[1])
				&&(rf.rxbuf[18]==cryptoBlock[2])&&(rf.rxbuf[19]==cryptoBlock[3]))Match=1;
				else Match =0;
				if (Match) 
                {
                    Putdata("    MAC is correct\n");
                }
				else
				{
					Putdata("    MAC is NOT correct !\n");
                    Putdata("   (Received RKE Message MAC:");
                    USART1_HEX(rf.rxbuf[16]);USART1_HEX(rf.rxbuf[17]);
                    USART1_HEX(rf.rxbuf[18]);USART1_HEX(rf.rxbuf[19]);
                    Putdata("   \n)");	    
					//Putdata("       Received RKE Message MAC: 0x%02x 0x%02x 0x%02x 0x%02x\n", rf.rxbuf[16],rf.rxbuf[17],
					//rf.rxbuf[18],rf.rxbuf[19]);
                    Putdata("   (Expected MAC should be: ");
                    USART1_HEX(cryptoBlock[0]);USART1_HEX(cryptoBlock[1]);
                    USART1_HEX(cryptoBlock[2]);USART1_HEX(cryptoBlock[3]);
                    Putdata("   \n)");	  
					//Putdata("       Expected MAC should be: 0x%02x 0x%02x 0x%02x 0x%02x\n", cryptoBlock[0], cryptoBlock[1],
					//cryptoBlock[2], cryptoBlock[3] );
				}
				CreateTable(0x07);
				u16CRC=0;
				u16CRC = ComputeCRC_8(u16CRC,&rf.rxbuf[0],25);
				if(rf.rxbuf[25] == u16CRC)
                {
                    Putdata("    CRC is correct\n\n");
                }
				else
				{
					Putdata("    CRC is NOT correct !\n");
                    Putdata("   Received Message CRC : 0x");
                    USART1_HEX(rf.rxbuf[25]);
                    Putdata(" \n");
					//Putdata("       Received Message CRC: 0x%02X\n",rf.rxbuf[25]);
                    Putdata("   Expected CRC should be: 0x");
                    USART1_HEX(u16CRC);
                    Putdata(" \n");                    
					//Putdata("       Expected CRC should be: 0x%02X\n\n",u16CRC);
				}
			}
			else
			{
				for(i=0; i<rf.rxlvl; i++)
				{
					//Putdata(" 0x%X",rf.rxbuf[i]);
				}
			}
		}
		else
		{
			sum = 0;
			for(i=0; i<rf.rssilvl; i++)
			{
				sum += rf.rssibuf[i];
			}
			sum /= rf.rssilvl;
            Putdata("1_RF reply received (RF rssi: %d):RF buf:0x ");
            USART1_HEX(sum);
            Putdata("\n");
			//Putdata("RF reply received (RF rssi: %d):\nRF buf: ", sum);
			for(i=0; i<rf.rxlvl; i++)
			{
				Putdata(" 0x%");
                USART1_HEX(rf.rxbuf[i]);
			}
			Putdata("\n\n");
		}

		// start RF polling mode again
		rf.mode = 0x00;
		rf.channel = 0x00;
		rf_ata5781_set_mode( rf.mode, rf.channel );
		_delay_us(50);
		rf.mode = 0x23;
		rf.channel = 0x00;
		rf_ata5781_set_mode( rf.mode, rf.channel );
		_delay_us(50);

		rf_reset_spi();
	}
	else
	{
		//Putdata("... no RF reply received --> continue ...\n");
	}
	
}

