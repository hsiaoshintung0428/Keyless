// This file has been prepared for Doxygen automatic documentation generation.
/*! \file ********************************************************************
*
* \brief  Header file for CRC public functions.
*
* This file contains the function prototypes for the CRC
* algorithm. 
*
* - File:              ata_api_crc.h
*
* \author              Atmel Corporation: http://www.atmel.com \n
*                      Support email: automotive@atmel.com
*
* $Name:  $
* $Revision: 446429 $
* $Date: 2017-02-07 20:09:50 +0800 (Tue, 07 Feb 2017) $
*/
/***********************************************************************************************************************
* Copyright (c) 2012 Atmel Corporation. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
* following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following
*    disclaimer.
*
* 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
*    following disclaimer in the documentation and/or other materials provided with the distribution.
*
* 3. The name of Atmel may not be used to endorse or promote products derived from this software without specific
*    prior written permission.
*
* 4. This software may only be redistributed and used in connection with an Atmel microcontroller product.
*
* THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
* THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE EXPRESSLY AND
* SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
* OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
* EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
***********************************************************************************************************************/
#ifndef CRC_H
#define CRC_H



void CreateTable ( uint8_t  polynomial );
uint8_t ComputeCRC_8 ( uint8_t initialValue, uint8_t* bytes, uint8_t length );



#endif

